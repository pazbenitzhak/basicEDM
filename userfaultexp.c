/* this file is based on the following blog post: https://blog.lizzie.io/using-userfaultfd.html */ 

#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/userfaultfd.h>

#define PAGESIZE 4096

int userfauldfd(int flags) {
    /* seems like an extension of syscall that creates a fd for userfaultfd object */
    return syscall(SYS_userfaultfd, flags); /*SYS_userfault fd to be included with linux file */
}

void* print_virtual_memory(void* memory) {
    /* a function created only to cause page faults */
    fprintf(stderr, "%s", (char*) memory);
    fprintf(stderr, "%s", &((char*) memory)[PAGESIZE]);
    return NULL; /* doesn't seem necessary in my view */
}

int func(int a, char** b) { /* could be **main** function */
    int return_code; /* initiated as 0 */
    int fd; /* 0 as well */
    if ((fd = userfault(O_NONBLOCK))==-1) {
        fprintf(stderr, "++ userfaultfd failed: %m\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }
    /* need to enable the userfaultfd, invoking UDDFIO_API ioctl specifying a udffdio_api.api value set to UFFD_API*/
    struct uffdio_api api = { .api = UFFD_API};
    /* now invoking the UFFDIO_API ioctl */
    if (ioctl(fd, UFFDIO_API, &api)) {
        fprintf(stderr, "++ ioctl(fd, UFFDIO_API, &api) failed: %m\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }
    /* make sure assignment was executed properly */
    if (api.apip!=UFFD_API) {
        fprintf(stderr, "++ unexpected UFFD api version.\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }

    /* now we want to mmap some pages and set them ipp with the userfaultfd */
    void* pages = NULL; /* initiate */
    if ((pages = mmap(NULL, PAGESIZE*2, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0))==MAP_FAILED) {
        fprintf(stderr, "++ mmap failed: %m\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }

    /* now we should invoke the UFFDIO_REGISTER ioctl to register a memory range in the userfaultfd be setting the uddfio_register structure accordingly */
    struct uffdio_register reg = {
        .mode = UFFDIO_REGISTER_MODE_MISSING, /* means that it would track missing pages */
        .range = {
            .start = (long) pages,
            .len = PAGESIZE*2
        }
    }

    /* comment: so from what I understand until now, we should know the memory range in advance and refer to it */


    /* now the ioctl */
    if (ioctl(fd, UFFDIO_REGISTER, &reg)) {
        fprintf(stderr, "++ ioctl(fd, UFFDIO_REGISTER, &reg) failed: %m\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }

    if (reg.ioctls!=UFFD_API_RANGE_IOCTLS) {
        fprintf(stderr, "++ unexpected UFFD ioctls.\n");
        return_code = 1;
        if (fd) {
            close(fd);
        }
        return return_code;
    }
}