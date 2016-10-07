#include "ZZIPLoader.h"


ZZIPLoader::ZZIPLoader(std::string  p_fileEnding) : FileLoader(p_fileEnding)
{
}

void ZZIPLoader::LoadFile(std::string p_fileName)
{
    //ZZIP_DIR* dir = zzip_dir_open("test.zip", 0);
    //if (dir) {
    //    ZZIP_DIRENT dirent;
    //    if (zzip_dir_read(dir, &dirent))
    //    {
    //        /* show info for first file */
    //        printf("%s %i/%i", dirent.d_name, dirent.d_csize, dirent.st_size);
    //    }
    //}
    //// assuming that there is a stdafx.h file in the test.zip...
    //ZZIP_FILE* fp = zzip_file_open(dir, "stdafx.h", 0);
    //if (fp) {
    //    char buf[10];
    //    zzip_ssize_t len = zzip_file_read(fp, buf, 10);
    //    if (len) {
    //        /* show head of README */
    //        write(1, buf, len);
    //    }
    //    zzip_file_close(fp);
    //    zzip_dir_close(dir);
    //}
    //return 0;
}

void ZZIPLoader::LoadResource(int p_GUID)
{
}
