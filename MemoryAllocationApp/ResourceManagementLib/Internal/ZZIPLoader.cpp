#include "ZZIPLoader.h"
#include <zzip/zzip.h>
#include <zlib/zlib.h>
#include "../ParserAndContainerManager.h"
#include "../MemoryTracker.h"
#include "PrioritizationManager.h"

ZZIPLoader::ZZIPLoader(std::string  p_fileEnding) : FileLoader(p_fileEnding)
{
}

void ZZIPLoader::LoadFile(const std::string &p_fileName)
{
    ParserAndContainerManager &parAndContMan = ParserAndContainerManager::Get();
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

            LoadAndParseFile(dir, dirent);
        }
        zzip_dir_close(dir);
    }
}

void ZZIPLoader::LoadFile(const std::string &p_fileName, const std::string &p_subDirectory)
{
    ParserAndContainerManager &parAndContMan = ParserAndContainerManager::Get();
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

            std::string p_entryName = dirent.d_name;
            // When we find the directory
            // If not our name contine
            if (p_entryName.compare(0, p_subDirectory.size(), p_subDirectory) != 0)
                continue;

           
            LoadAndParseFile(dir, dirent);
        }
        zzip_dir_close(dir);
    }
}

void ZZIPLoader::LoadResource(GUID p_GUID, const std::string &p_directory)
{
    // First try to load from directory world.zip  world.zip/GUID
    ZZIP_DIR* dir = zzip_dir_open(p_directory.c_str(), 0);

    // If we could open directory
    if (dir)
    {
        std::string t_guidString = p_GUID.ToString();

        // If fail, walk through the directory to load the file world.zip/Animations/GUID
        ZZIP_DIRENT dirent;
        while (zzip_dir_read(dir, &dirent))
        {
            std::string p_entryName = dirent.d_name;

            // If not our name contine
            if (p_entryName.compare(p_entryName.size() - t_guidString.size(), t_guidString.size(), t_guidString) != 0)
                continue;

            LoadAndParseFile(dir, dirent);

            break;
        }

        zzip_dir_close(dir);
    }
}

void ZZIPLoader::LoadResource(GUID p_GUID, const std::string &p_fileEnding, const std::string & p_directory)
{
    // First try to load from directory world.zip  world.zip/GUID
    ZZIP_DIR* dir = zzip_dir_open(p_directory.c_str(), 0);

    // If we could open directory
    if (dir)
    {
        std::string t_guidString = p_GUID.ToString();

        // If fail, walk through the directory to load the file world.zip/Animations/GUID
        ZZIP_DIRENT dirent;
        while (zzip_dir_read(dir, &dirent))
        {
            std::string p_entryName = dirent.d_name;

            // If not our name contine
            if (p_entryName.compare(p_entryName.size() - t_guidString.size(), t_guidString.size(), t_guidString) != 0)
                continue;

            LoadAndParseFile(dir, dirent);

            break;
        }

        zzip_dir_close(dir);
    }
}


void ZZIPLoader::LoadAndParseFile(zzip_dir *p_dir, const zzip_dirent &p_dirent)
{
    ParserAndContainerManager &parAndContMan = ParserAndContainerManager::Get();
    ZZIP_FILE* fp = zzip_file_open(p_dir, p_dirent.d_name, 0);
    if (fp) {

		std::string t_ending;
		GUID t_guid;
		if (!ParseGUIDAndEndingFromFilePath(p_dirent.d_name, &t_ending, &t_guid))
		{
			zzip_file_close(fp);
			return;
		}

		if (!parAndContMan.ShouldLoadResource(t_ending, t_guid))
		{
			zzip_file_close(fp);
			return;
		}

		if (!MemoryTracker::Get()->CheckIfMemoryAvailable(p_dirent.st_size))
		{
			//There is no memory available. A dump has been created its time to crash!!
			throw 1337;
		}

        // Create buffer that can hold the memory
        // We only keep the memory for one resource at a time?
        char* temporaryBuffer = new char[p_dirent.st_size];

        // Read the input to the buffer
        zzip_ssize_t len = zzip_file_read(fp, temporaryBuffer, p_dirent.st_size);

        if (len) {
            // Parse for specific
            parAndContMan.ParseByEnding(temporaryBuffer, p_dirent.st_size, t_ending, t_guid);

        }
		MemoryTracker::Get()->AddMemoryUsage(-p_dirent.st_size);
		delete temporaryBuffer;
        zzip_file_close(fp);
    }
}

void ZZIPLoader::LoadAndParseFile(zzip_dir * p_dir, const std::string & p_ending, const zzip_dirent & p_dirent)
{
    ParserAndContainerManager &parAndContMan = ParserAndContainerManager::Get();
    ZZIP_FILE* fp = zzip_file_open(p_dir, p_dirent.d_name, 0);
    if (fp) {

        std::string t_ending;
        GUID t_guid;
        if (!ParseGUIDAndEndingFromFilePath(p_dirent.d_name, &t_ending, &t_guid))
        {
            zzip_file_close(fp);
            return;
        }

        if (p_ending != t_ending)
        {
            zzip_file_close(fp);
            return;
        }

        if (!parAndContMan.ShouldLoadResource(t_ending, t_guid))
        {
            zzip_file_close(fp);
            return;
        }

        if (!MemoryTracker::Get()->CheckIfMemoryAvailable(p_dirent.st_size))
        {
            //There is no memory available. A dump has been created its time to crash!!
            throw 1337;
        }

        // Create buffer that can hold the memory
        // We only keep the memory for one resource at a time?
        char* temporaryBuffer = new char[p_dirent.st_size];

        // Read the input to the buffer
        zzip_ssize_t len = zzip_file_read(fp, temporaryBuffer, p_dirent.st_size);

        if (len) {
            // Parse for specific
            parAndContMan.ParseByEnding(temporaryBuffer, p_dirent.st_size, t_ending, t_guid);

        }
        MemoryTracker::Get()->AddMemoryUsage(-p_dirent.st_size);
        delete temporaryBuffer;
        zzip_file_close(fp);
    }
}
