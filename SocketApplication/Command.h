#pragma once

#ifndef CommandInclude
#define CommandInclude

typedef enum Command_
{
    CommandInvalid,

    CommandFileDataPut,
    CommandFileDataGet,
    CommandFileDelete,

    CommandFileLock,
    CommandFileUnlock,

    CommandFileChangePublish,
    CommandFileChangeSubscribe,

    CommandOpenProgram,

    CommandQuit,

    CommandHTTPRequest,
    CommandMinecraftServerList
}Command;

#endif