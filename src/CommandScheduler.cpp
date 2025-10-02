#include <CommandScheduler.h>

namespace CmdBased {
    void CommandScheduler::periodic() {
        /* run subsystems' periodic procedures */
        for (size_t i = 0; i < kSubsystemsLen; i++)
            kSubsystems[i]->periodic();

        // TODO: triggers
        
        /* iterate through scheduled commands */
        CommandBase *command = m_scheduledHead.m_nextScheduled;
        while (command) {
            command->run();
            CommandBase *nextCommand = command->m_nextScheduled;
            if (command->isFinished()) cancel(command, false); // finished
            command = nextCommand;
        }

        /* schedule default command of unoccupied subsystems */
        for (size_t i = 0; i < kSubsystemsLen; i++) {
            SubsystemBase *sub = kSubsystems[i];
            if (sub->m_defaultCommand && !sub->m_command)
                schedule(sub->m_defaultCommand);
            // NOTE: This will silently fail if the default command requires a
            //       subsystem already claimed by an uninterruptible command.
        }
    }

    bool CommandScheduler::schedule(CommandBase *command) {
        if (command->m_scheduled) return false; // command is already scheduled

        /* check requirements */
        bool cancelReqs = false; // set if cancellation is needed
        for (size_t i = 0; i < command->kRequirementsLen; i++) {
            SubsystemBase *req = command->kRequirements[i];
            if (req->m_command) {
                if (!req->m_command->kInterruptible) return false;
                    // uninterruptible command encountered
                else cancelReqs = true;
            }
        }
        
        if (cancelReqs) {
            /* iterate through reqs again and clear deps */
            for (size_t i = 0; i < command->kRequirementsLen; i++) {
                SubsystemBase *req = command->kRequirements[i];
                if (req->m_command) cancel(req->m_command, true);
            }
        }

        /* put command into scheduling queue */
        command->m_prevScheduled = &m_scheduledHead;
        command->m_nextScheduled = m_scheduledHead.m_nextScheduled;
        if (command->m_nextScheduled)
            command->m_nextScheduled->m_prevScheduled = command;
        m_scheduledHead.m_nextScheduled = command;

        command->initialise(); // initialise command
        return true;
    }

    bool CommandScheduler::cancel(CommandBase *command, bool interrupt) {
        if (!command->m_scheduled) return false; // command isn't scheduled
        if (interrupt && !command->kInterruptible)
            return false; // attempting to interrupt uninterruptible cmd

        command->end(interrupt); // run command's end stage

        for (size_t i = 0; i < command->kRequirementsLen; i++)
            command->kRequirements[i]->m_command = nullptr; // clear occupancy
        
        /* reset */
        command->m_scheduled = false;
        command->m_prevScheduled->m_nextScheduled = command->m_nextScheduled;
        if (command->m_nextScheduled)
            command->m_nextScheduled->m_prevScheduled = 
                command->m_prevScheduled;
        command->m_prevScheduled = command->m_nextScheduled = nullptr;
        
        return true;
    }
};