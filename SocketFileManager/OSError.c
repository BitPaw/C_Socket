#include "OSError.h"

char* OSErrorToString(OSError state)
{
    switch (state)
    {
    case OSError_NoError:
        return "NoErrors";              
        
    case OSError_FileIsCurrentlyInUse:
        return "FileIsCurrentlyInUse";
    case OSError_DirectoryInvalid:
        return "DirectoryInvalid";
    case OSError_FileAlreadyExists:
        return "FileAlreadyExists";
    case OSError_DirectoryOrFileNotFound:
        return "DirectoryOrFileNotFound";
    case OSError_FileToBig:
        return "FileToBig";
    case OSError_FileNameToLong: 
        return "FileNameToLong";
    case OSError_FileNameInvalid: 
        return "FileNameInvalid";

    	
    case OSError_NoFileExtension:
        return "NoFileExtension";

    case OSError_DirectoryNotEmpty:
        return "DirectoryNotEmpty";
 	
    case OSError_ExtensionToShort:
        return "ExtensionToShort";

    case OSError_ContentIsNull:
        return "ContentCanNotBeNull";
    	
    case OSError_FolderAlreadyExists: 
        return "FolderAlreadyExists";
    case OSError_PathNotFound: 
        return "PathNotFound";
    case OSError_AccessDenied:
        return "FolderAccessDenied";
    case OSError_CallocWentWrong: 
        return "CallocWentWrong";
    case OSError_WrittenContentIsCorrupted:
        return "WrittenContentIsCorrupted";
    case OSError_UnknownError:
        return "UnknownError";
    case OSError_NotImplemented:
        return "NotImplemented";
    	    	
    case OSError_ParameterIsNull:
        return "ParameterIsNull";
    case OSError_ParameterInvalid:
        return "ParameterIsInvalid";

    }
    return 0;
}