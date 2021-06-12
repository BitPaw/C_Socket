#ifndef CommandErrorInclude
#define CommandErrorInclude

typedef enum CommandError_
{
    CommandErrorNotSet,

    CommandErrorSuccessful,
    CommandErrorSuccessfulSilent,

    CommandErrorFileAlreadyExists,
    CommandErrorFileDoesNotExist,
    CommandErrorAlreadyLocked,
    CommandErrorAccessLocked,

    CommandErrorUnsupportedCommand
}CommandError;

#endif