#ifndef FILEENTRY_H
#define FILEENTRY_H

#include <cstdint>

class FileEntry
{
public:
	FileEntry();
	~FileEntry();

	uint32_t nameChecksum;
	uint32_t fileSize;
	uint32_t firstChunk;
};

#endif
