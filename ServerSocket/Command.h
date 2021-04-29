typedef enum Command_
{
    Invalid,

    Put,
    Get,
    Delete,

    LockFile,
    UnlockFile,

    Publish,
    Subscribe,

    OpenProgram,

    Quit
}Command;
