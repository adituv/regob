#ifndef CHUNKHEADER_H
#define CHUNKHEADER_H

#include <cstdint>

class ChunkHeader
{
public:
	ChunkHeader();
	~ChunkHeader();

	uint32_t chunkSize;
	uint32_t offset;
	uint32_t nextChunk;
	uint32_t fileTypeFlags;
	uint32_t unk001;
};

#endif
