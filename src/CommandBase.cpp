#include <CommandBase.h>

namespace CmdBased {
    void CommandBase::initialise() {
        
    }

    void CommandBase::run() {

    }

    bool CommandBase::isFinished() {
        return true; // so an empty command won't run forever
    }

    void CommandBase::end(bool interrupted) {

    }
}

