#include "ZZIPLoader.h"

#include <zzip/zzip.h>
#include <zlib/zlib.h>

ZZIPLoader::ZZIPLoader(std::string  p_fileEnding) : FileLoader(p_fileEnding)
{
}

void ZZIPLoader::LoadFile(std::string p_fileName)
{
    ZZIP_DIR* dir = zzip_dir_open(p_fileName.c_str(), 0);

    // If we could open directory
    if (dir) 
    {
        // Read directory entry
        ZZIP_DIRENT dirent;
        while (zzip_dir_read(dir, &dirent))
        {
            /* show info for first file */
            printf("Reading file: %s , with compressed/normal size: %i/%i\n", dirent.d_name, dirent.d_csize, dirent.st_size);


            //assuming that there is a stdafx.h file in the test.zip...
            ZZIP_FILE* fp = zzip_file_open(dir, dirent.d_name, 0);
            if (fp) {
                char buf[10];
                zzip_ssize_t len = zzip_file_read(fp, buf, 10);
                if (len) {
                    /* show head of README */
                    _write(1, buf, len);
                }
                zzip_file_close(fp);
            }
        }

        zzip_dir_close(dir);
    }
}

void ZZIPLoader::LoadResource(int p_GUID)
{
}
