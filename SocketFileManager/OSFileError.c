

#include "OSFileError.h"

const char* OSFileErrorToString(OSFileError state)
{
    switch (state)
    {
    default:
    case OSFileError_NoError:
        return "NoErrors";              
        
    case OSFileError_FileIsCurrentlyInUse:
        return "FileIsCurrentlyInUse";
    case OSFileError_InvalidDirectory:
        return "InvalidDirectory";
    case OSFileError_FileAlreadyExists:
        return "FileAlreadyExists";
    case OSFileError_FileNotFound:
        return "FileNotFound";
    case OSFileError_NoFileExtension:
        return "NoFileExtension";
    	
    case OSFileError_FolderNotFound:
        return "FolderNotFound";
    case OSFileError_DirectoryNotEmpty:
        return "DirectoryNotEmpty";
 	
    case OSFileError_ExtensionToShort:
        return "ExtensionToShort";

    case OSFileError_ContentIsNull:
        return "ContentCanNotBeNull";
    	
    case OSFileError_FolderAlreadyExists: 
        return "FolderAlreadyExists";
    case OSFileError_PathNotFound: 
        return "PathNotFound";
    case OSFileError_AccessDenied:
        return "FolderAccessDenied";
    case OSFileError_CallocWentWrong: 
        return "CallocWentWrong";
    case OSFileError_WrittenContentIsCorrupted:
        return "WrittenContentIsCorrupted";
    case OSFileError_UnknownError:
        return "UnknownError";
    case OSFileError_NotImplemented:
        return "NotImplemented";


    }
}