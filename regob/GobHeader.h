#ifndef GOBHEADER_H
#define GOBHEADER_H

#include <cstdint>
#include <istream>
#include <vector>

#include "ChunkHeader.h"
#include "FileEntry.h"

class GobHeader
{
public:
	~GobHeader();
	std::vector<std::vector<ChunkHeader>> GetFileChunks();

	static GobHeader* FromStream(std::istream& in);
private:
	GobHeader();
	uint32_t dataFileSize;
	uint32_t chunkCount;
	uint32_t fileCount;

	std::vector<ChunkHeader> chunkHeaders;
	std::vector<FileEntry> fileEntries;
};

#endif
