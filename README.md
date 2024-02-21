# Pympq
Implementation of the [StormLib](http://www.zezula.net/en/mpq/stormlib.html) API in python

## Installation
```
pip install pympq
```

## API Implementation Coverage
❌ SFileOpenArchive  
✔️ SFileCreateArchive  
❌ SFileCreateArchive2  
❌ SFileAddListFile  
❌ SFileSetLocale  
❌ SFileGetLocale  
❌ SFileFlushArchive  
✔️ SFileCloseArchive  
❌ SFileSetMaxFileCount  
❌ SFileSignArchive  
✔️ SFileCompactArchive  
❌ SFileSetCompactCallback  

❌ SFileOpenPatchArchive  
❌ SFileIsPatchedArchive  

❌ SFileOpenFileEx  
❌ SFileGetFileSize  
❌ SFileSetFilePointer  
❌ SFileReadFile  
❌ SFileCloseFile  
❌ SFileHasFile  
❌ SFileGetFileName  
❌ SFileGetFileInfo  
❌ SFileVerifyFile  
❌ SFileVerifyArchive  
❌ SFileExtractFile  

❌ SFileFindFirstFile  
❌ SFileFindNextFile  
❌ SFileFindClose  
❌ SListFileFindFirstFile  
❌ SListFileFindNextFile  
❌ SListFileFindClose  
❌ SFileEnumLocales  

❌ SFileCreateFile  
❌ SFileWriteFile  
❌ SFileFinishFile  
✔️ SFileAddFileEx  
❌ SFileAddFile  
❌ SFileAddWave  
❌ SFileRemoveFile  
❌ SFileRenameFile  
❌ SFileSetFileLocale  
❌ SFileSetDataCompression  
❌ SFileSetAddFileCallback  

❌ SCompImplode  
❌ SCompExplode  
❌ SCompCompress  
❌ SCompDecompress  
