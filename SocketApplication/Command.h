#ifndef CommandInclude
#define CommandInclude

typedef enum Command_
{
    CommandInvalid,

    CommandFileDataPut, // PUT
    CommandFileDataGet, // GET
    CommandFileDelete, // DEL

    CommandFileLock, // BEG
    CommandFileUnlock, // END
      
    CommandFileChangeSubscribe, // SUB
    //CommandFileChangeUnSubscribe // No requirement to imlement

    CommandOpenProgram, // OP

    CommandQuit, // QUIT

    // fun features
    CommandHTTPRequest,
    CommandMinecraftServerList
}Command;

#endif