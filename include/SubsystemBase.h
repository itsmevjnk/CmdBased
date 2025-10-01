#pragma once

#include "base_includes.h"

namespace CmdBased {
    class SubsystemBase {
    public:
        virtual void periodic();
    private:
        SubsystemBase *m_next; // next subsystem - used by command scheduler
    };
};