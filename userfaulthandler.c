/* for now i'm trying to copy Elior and Itay's functions and try to edit them to fit into the redis interface*/

#include <inttypes.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/userfaultfd.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include "userfault.h"
/* TODO: erase all unnecessary includes */
#define _OPEN_SYS_ITOA_EXT


#define PAGE_SIZE 4096

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

void setUp() {
    struct uffdio_api uffdio_api;
    struct uffdio_register uffdio_register;
    long uffd;
    /*  creating and eanbling a new userfaultfd object */
    uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
    if (uffd==-1) {
        errExit("userfaultfd syscall failed\n"); /* the relevant error */
    }
    uffdio_api.api = UFFD_API;
    uffdio_api.features = 0;
    if (ioctl(uffd, UFFDIO_API, &uffdio_api)==-1) {
        errExit("UFFDIO_API ioctl failed\n");
    }

}

void listenToPageFaults() {
    static srtuct uffd_msg msg; /* Data read from userfaultfd */
    ssize_t nread;

    /* loop to handle incoming event on the userfaultfd file descriptor */
    struct pollfd pollfd;
    pollfd.fd = uffd;
    pollfd.events = POLLIN;

    /* while loop */
    while(poll(&pollfd, 1, -1)>0) {
        /* read event from userfaultfd */
        nread = read(uffd,&msg,sizeof(msg));
        if (nread==0) {
            errExit("EOF on userfaultfd\n");
        }
        if (nread==-1) {
            errExit("error with read\n");
        }
        /* successful read */

        switch (msg.event) {
            case UFFD_EVENT_PAGEFAULT: /* we've got a page fault */
                handlePageFault(&msg);
                break;
            case UFFD_EVENT_FORK:
                break;
            case UFFD_EVENT_REMAP:
                break;
            case UFFD_FEATURE_EVENT_REMOVE:
                break;
            default:
                break;

        }
    }
}

void handlePPageFault(struct uffd_msg* msg) {
    /* i think that in the future, we would like to handle this with multiple servers.
    the handling would be with a context, so we need to get the context in this function */
    unsigned long long vaddr = msg->arg.pagefault.address;
    char* vaddrStr;
    char* value;
    /* lpet - not sure if relevant */
    /* now I must use the redis interface to check if this page exists */
    vaddrStr = ultoa(vaddr);
    value = getValue(vaddrStr,context);
    /* TODO: think about where to deliver the context */
    if (strcmp(value, "(nil)")==0) { /* there is not such a value saved in the Redis server*/
        /* need to set the value into the redis server, but which one? */
        /* "copy zero page" */
        setValue(vaddrStr, context);
    }
}