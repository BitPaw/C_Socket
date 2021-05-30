

#include "FileManagerErrorCodes.h"

const char* FileManagerErrorCodeToString(FileManagerErrorCode state)
{
    switch (state)
    {
    default:
    case FileManager_NoError:
        return "NoErrors";

        
    case FileManager_FolderNotFound:
        return "FolderNotFound";
    case FileManager_FileNotFound:
        return "FileNotFound";
    	

    case FileManager_NoFileExtension:
        return "NoFileExtension";

    case FileManager_ExtensionToShort:
        return "ExtensionToShort";

    case FileManager_ContentIsNull:
        return "ContentCanNotBeNull";
        
    }
}