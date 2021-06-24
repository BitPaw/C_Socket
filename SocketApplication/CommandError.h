#ifndef CommandErrorInclude
#define CommandErrorInclude

typedef enum CommandError_
{
    CommandNotSet,

    CommandSuccessful,
    CommandSuccessfulSilent,

    CommandFileAlreadyExists,
    CommandFileDoesNotExist,
    CommandAlreadyLocked,
    CommandAccessLocked,

    CommandPipeCreationFailure,
    CommandFileWriteFailure,

    CommandNoFileData,
    CommandNoFilePath,

    CommandPipeClosingFailure,
    CommandPipeProgramFailed,

    CommandUnsupportedCommand
}CommandError;

#endif