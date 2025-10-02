#pragma once

#include "base_includes.h"

namespace CmdBased {
    class CommandScheduler;
    class SubsystemBase;
    class CommandBase {
    friend class CommandScheduler;
    public:
        CommandBase(SubsystemBase **reqs, size_t reqLength, bool interruptible = true) 
            : kRequirements(reqs), kRequirementsLen(reqLength), kInterruptible(interruptible) {}
        
        virtual void initialise(); // to be executed after claiming reqs
        virtual void run(); // to be executed periodically
        virtual bool isFinished();
        virtual void end(bool interrupted);

        const bool kInterruptible; // set if this command can be interrupted
    private:
        SubsystemBase **const kRequirements; // subsystem requirements
        const size_t kRequirementsLen; // number of subsystem requirements

        CommandBase *m_prevScheduled = nullptr; // previous scheduled command
        CommandBase *m_nextScheduled = nullptr; // next scheduled command
        // NOTE: scheduled commands form a doubly linked list

        bool m_scheduled = false; // set if this command is scheduled
    };
};