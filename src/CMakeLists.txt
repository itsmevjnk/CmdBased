add_library(CmdBased STATIC
    CommandBase.cpp SubsystemBase.cpp CommandScheduler.cpp
)
target_include_directories(CmdBased PUBLIC ../include)

