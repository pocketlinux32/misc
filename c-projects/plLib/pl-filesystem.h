/************************************\
* PocketLinux32's Simple Library     *
* (c)2021 pocketlinux32, under GPLv3 *
* Version 1.0, Filesystem header     *
\************************************/

#include <pl-standard.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// plDir: Directory structure
struct plDir {
	char* dirPath; // directory path
	char** dirEntries; // memory-allocated listing of directory
	size_t amtEntries; // amount of entries
}

// plFile: File/Stringstream structure
struct plFile {
	char** buffer; // data buffer
	size_t bufferSize; // data buffer size
	FILE* fileObject; // Stream object
}

// plDeallocDirObj(): Deallocates the plDir structure
void plDeallocDirObj(struct plDir* dirInfo){
	dirInfo.dirPath = NULL;
	dirInfo.amtEntries = NULL;
	free(dirInfo.dirEntries);
}

// plCreateDirObj(): Creates a plDir structure containing a directory listing
struct plDir* plCreateDirObj(const char* path){
	DIR* tempDir = opendir(path);
	static char** list;
	size_t amount = 0;
	int i = 0;
	static struct plDir returnStruct;
	struct dirent* tempFileStruct;

	while(tempFileStruct = readdir(tempDir)){
		amount++;
	}

	list = calloc(amount, sizeof(char*));
	rewinddir(tempDir);

	while(tempFileStruct = readdir(tempDir)){
		list[i] = tempFileStruct->d_name;
		i++;
	}

	closedir(tempDir);

	returnStruct.dirPath = path;
	returnStruct.dirEntries = list;
	returnStruct.amtEntries = amount;

	return returnStruct*;
}

// plCreateFileStream(): Creates a plFile object containing the contents of a file, or a stringstream
struct plFile* plCreateFileStream(const char* buf, size_t bufSize, bool isStringStream, const char* path){
	FILE* tempFile;
	static struct plFile returnStruct;
	if(isStringStream){
		tempFile = open_memstream(buf*, bufSize*);
	}else{
		tempFile = fopen(path);
	}
}
