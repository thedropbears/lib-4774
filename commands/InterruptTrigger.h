#ifndef INTERRUPTTRIGGER
#define INTERRUPTTRIGGER

#include <WPILib.h>

class InterruptTrigger: public Trigger {
public:
    InterruptTrigger(DigitalInput*);
    bool Get();
private:
    DigitalInput* di;
};

#endif
