# Pympq
Implementation of the [StormLib](http://www.zezula.net/en/mpq/stormlib.html) API in python

## Installation
```
pip install pympq
```

## API Implementation Coverage
✔️ SFileOpenArchive  
✔️ SFileCreateArchive  
❌ SFileCreateArchive2  
❌ SFileAddListFile  
❌ SFileSetLocale  
❌ SFileGetLocale  
❌ SFileFlushArchive  
✔️ SFileCloseArchive  
❌ SFileSetMaxFileCount  
❌ SFileSignArchive **Bugged**  
✔️ SFileCompactArchive  
❌ SFileSetCompactCallback  

❌ SFileOpenPatchArchive  
❌ SFileIsPatchedArchive  

✔️ SFileOpenFileEx  
❌ SFileGetFileSize  
❌ SFileSetFilePointer  
❌ SFileReadFile  
✔️ SFileCloseFile  
✔️ SFileHasFile  
✔️ SFileGetFileName  
❌ SFileGetFileInfo  
✔️ SFileVerifyFile  
❌ SFileVerifyArchive  
✔️ SFileExtractFile  

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
❌ SFileAddWave  
✔️ SFileRemoveFile  
✔️ SFileRenameFile  
❌ SFileSetFileLocale  
❌ SFileSetAddFileCallback  

❌ SCompImplode  
❌ SCompExplode  
❌ SCompCompress  
❌ SCompDecompress  

## Examples

#### Create new mpq and add file to it
```python
import pympq

with open("test.txt", "w") as f:
    f.write("hello world")

mpq_flags = [pympq.MPQ_CREATE_LISTFILE, pympq.MPQ_CREATE_ARCHIVE_V1]

with pympq.create_archive("test.mpq", mpq_flags, 128) as mpq:
    compress_flags = []
    file_flags = [pympq.MPQ_FILE_IMPLODE, pympq.MPQ_FILE_REPLACEEXISTING]
    mpq.add_file("test.txt", "path/in/mpq/test.txt", file_flags, compress_flags, [pympq.MPQ_COMPRESSION_NEXT_SAME])
    mpq.compact()
```
