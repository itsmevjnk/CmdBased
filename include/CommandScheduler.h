#pragma once

#include "base_includes.h"
#include "CommandBase.h"
#include "SubsystemBase.h"

namespace CmdBased {
    class CommandScheduler {
    public:
        CommandScheduler(const SubsystemBase *subs, size_t subLen)
            : kSubsystems(subs), kSubsystemsLen(subLen) {}
        
        void periodic();    

    private:
        const SubsystemBase *const kSubsystems;
        const size_t kSubsystemsLen;

        CommandBase *m_scheduledCommand = nullptr; // first scheduled command
    };
};