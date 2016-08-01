#ifndef GOBHEADER_H
#define GOBHEADER_H

#include <istream>
#include <vector>

#include "ChunkHeader.h"
#include "FileEntry.h"

class GobHeader
{
public:
	GobHeader();
	~GobHeader();

	static GobHeader FromStream(std::istream in);
private:
	uint32_t dataFileSize;
	std::vector<ChunkHeader> chunkHeaders;
	std::vector<FileEntry> fileEntries;
};

#endif
