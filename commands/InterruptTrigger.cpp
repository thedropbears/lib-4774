#include "InterruptTrigger.h"

InterruptTrigger::InterruptTrigger(DigitalInput* _di) {
    this->di = _di;
}

bool InterruptTrigger::Get() {
    return !di->Get();
}
