

#include "FileManagerErrorCodes.h"

const char* FileManagerErrorCodeToString(FileManagerErrorCode state)
{
    switch (state)
    {
    default:
    case FileManager_NoError:
        return "NoErrors";              
        
    case FileManager_FileIsCurrentlyInUse:
        return "FileIsCurrentlyInUse";
    case FileManager_InvalidDirectory:
        return "InvalidDirectory";
    case FileManager_FileAlreadyExists:
        return "FileAlreadyExists";
    case FileManager_FileNotFound:
        return "FileNotFound";
    case FileManager_NoFileExtension:
        return "NoFileExtension";
    	
    case FileManager_FolderNotFound:
        return "FolderNotFound";
    case FileManager_DirectoryNotEmpty:
        return "DirectoryNotEmpty";
 	
    case FileManager_ExtensionToShort:
        return "ExtensionToShort";

    case FileManager_ContentIsNull:
        return "ContentCanNotBeNull";
    	
    case FileManager_FolderAlreadyExists: 
        return "FolderAlreadyExists";
    case FileManager_PathNotFound: 
        return "PathNotFound";
    case FileManager_AccessDenied:
        return "FolderAccessDenied";
    case FileManager_CallocWentWrong: 
        return "CallocWentWrong";
    case FileManager_UnknownError:
        return "UnknownError";
    case FileManager_NotImplemented:
        return "NotImplemented";

        
    }
}