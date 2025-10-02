#pragma once

#include "base_includes.h"
#include "CommandBase.h"
#include "SubsystemBase.h"

namespace CmdBased {
    class CommandScheduler {
    public:
        CommandScheduler(SubsystemBase **subs, size_t subLen)
            : kSubsystems(subs), kSubsystemsLen(subLen) {}
        
        void periodic();    
        bool schedule(CommandBase *command);
    private:
        bool cancel(CommandBase *command, bool interrupt);
        
        SubsystemBase **const kSubsystems;
        const size_t kSubsystemsLen;

        CommandBase m_scheduledHead{nullptr, 0}; // head of scheduled cmd list
        // NOTE: This head will not be executed; the first command to run is
        //       its next command in the linked list.
    };
};