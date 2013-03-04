#include <unistd.h>
#include "../zlib/zlib.h"
#include "unzip.h"
#include "crypt.h"

#define FILENAME "./zipfile.zip"


int main(int argc, char *argv[])
{
    unzFile myZip = NULL;
    myZip = unzOpen(FILENAME);
    unz_global_info zip_global_info;
    unz_file_info zip_file_info;
    char filename[256];
    int ret;
    
    if (myZip == NULL)
    {
        printf("Unable to open zip file.\n");
	exit(-1);
    }
    else
    {
        printf("File found.\n");
    }
    
    ret = unzGetGlobalInfo(myZip, &zip_global_info);
    if (ret == UNZ_OK)
    {
	printf("Found %d files in archive.\n", zip_global_info.number_entry);
	printf("Comment length is %d bytes.\n", zip_global_info.size_comment);    
    }
    else
    {
	printf("unzGetGlobalInfo() call failed.\n");    
	exit(-1);
    }

    ret = unzGoToFirstFile(myZip);
    if (ret != UNZ_OK)
    {
	printf("unzGoToFirstFile() call failed.\n");    
	exit(-1);
    }
    
    ret = unzGetCurrentFileInfo(myZip, &zip_file_info, 
    				filename, 256,
				NULL,0, NULL, 0);
    if (ret == UNZ_OK)
    {
        printf("Filename is %s.\n",filename);
        printf("Uncompressed size is %d bytes.\n",zip_file_info.uncompressed_size);
    }
    
    // If file is a .sms:
    ret = unzOpenCurrentFile(myZip);
    if (ret != UNZ_OK)
    {
	printf("Unable to open file from zip archive.\n");        
	exit(-1);
    }
    
    return 0;
}
 
