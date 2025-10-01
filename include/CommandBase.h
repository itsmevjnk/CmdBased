#pragma once

#include "base_includes.h"
#include "SubsystemBase.h"

namespace CmdBased {
    class CommandBase {
    public:
        CommandBase(const SubsystemBase *reqs, size_t reqLength) 
            : kRequirements(reqs), kRequirementsLen(reqLength) {}
        
        virtual void initialise(); // to be executed after claiming reqs
        virtual void run(); // to be executed periodically
        virtual void end(bool interrupted);

        const SubsystemBase *const kRequirements; // subsystem requirements
        const size_t kRequirementsLen; // number of subsystem requirements
        // TODO: maybe we'll want to move these to private
    private:
        CommandBase *m_nextScheduled; // next scheduled command
    };
};