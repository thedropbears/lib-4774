#include "InterruptTrigger.h"

bool InterruptTrigger::Get() {
    if(!gpio_fd) {
        gpio_fd = open(GPIO_INT_FILE, O_RDONLY | O_NONBLOCK);
        memset((void*)fdset, 0, sizeof(fdset));
        fdset[0].fd = gpio_fd;
        fdset[0].events = POLLPRI;
    }

    //poll digital io pin
    poll(fdset, 1, 0);

    if(fdset[0].revents & POLLPRI) {
        return true;
    }
    return false;
}
