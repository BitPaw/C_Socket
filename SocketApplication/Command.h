#pragma once

#ifndef CommandInclude
#define CommandInclude

typedef enum Command_
{
    CommandInvalid,

    CommandPut,
    CommandGet,
    CommandDelete,

    CommandLockFile,
    CommandUnlockFile,

    CommandPublish,
    CommandSubscribe,

    CommandOpenProgram,

    CommandQuit
}Command;

#endif