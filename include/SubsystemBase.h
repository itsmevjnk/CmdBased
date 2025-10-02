#pragma once

#include "base_includes.h"

namespace CmdBased {
    class CommandScheduler;
    class CommandBase;
    class SubsystemBase {
    friend class CommandScheduler;
    public:
        virtual void periodic();
    private:
        CommandBase *m_defaultCommand; // default command
        CommandBase *m_command; // occupying command
    };
};