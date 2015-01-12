#ifndef INTERRUPTTRIGGER
#define INTERRUPTTRIGGER

#include <WPILib.h>

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <poll.h>

#define GPIO_INT_FILE "/sys/class/gpio/gpio14/value"

class InterruptTrigger: public Trigger {
public:
    bool Get();
private:
    int gpio_fd = 0;
    struct pollfd fdset[1];
};

#endif
