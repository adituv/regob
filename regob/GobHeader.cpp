#include "GobHeader.h"

#include <algorithm>
#include <iostream>
#include "util.h"

using namespace std;


GobHeader::GobHeader()
{
}


GobHeader::~GobHeader()
{
}

std::vector<std::vector<ChunkHeader>> GobHeader::GetFileChunks()
{
	std::vector<std::vector<ChunkHeader>> result;
	std::for_each(this->fileEntries.cbegin(), this->fileEntries.cend(), [this, &result](FileEntry entry) {
		std::vector<ChunkHeader> fileChunks;
		unsigned int nextChunk = entry.firstChunk;

		while (nextChunk != ChunkHeader::CHUNK_END) {
			auto chunk = this->chunkHeaders[nextChunk];
			nextChunk = chunk.nextChunk;
			fileChunks.push_back(chunk);
		}
		result.push_back(fileChunks);
	});
	return result;
}

GobHeader* GobHeader::FromStream(std::istream& in)
{
	auto result = new GobHeader();

	uint32_t magic;
	magic = readTypeBE<uint32_t>(in);

	if (magic != 0x00008008) {
		cerr << "Invalid header magic number!";

		// TODO: replace with exception?
		return nullptr;
	}

	result->dataFileSize = readTypeBE<uint32_t>(in);
	result->chunkCount = readTypeBE<uint32_t>(in);
	result->fileCount = readTypeBE<uint32_t>(in);

	for (unsigned int i = 0; i < result->chunkCount; i++) {
		auto chunkHeader = ChunkHeader();

		chunkHeader.chunkSize = readTypeBE<uint32_t>(in);
		chunkHeader.offset = readTypeBE<uint32_t>(in);
		chunkHeader.nextChunk = readTypeBE<uint32_t>(in);
		chunkHeader.fileTypeFlags = readTypeBE<uint32_t>(in);

		result->chunkHeaders.push_back(chunkHeader);
	}

	// Sanity check: last entry in chunkHeaders should have nextChunk = 0x7fff
	std::transform(result->chunkHeaders.begin(), result->chunkHeaders.end(), result->chunkHeaders.begin(), [&in](ChunkHeader h) {
		h.unk001 = readTypeBE<uint32_t>(in);
		return h;
	});

	for (unsigned int i = 0; i < result->fileCount; i++) {
		auto fileEntry = FileEntry();

		fileEntry.nameChecksum = readTypeBE<uint32_t>(in);
		fileEntry.fileSize = readTypeBE<uint32_t>(in);
		fileEntry.firstChunk = readTypeBE<uint32_t>(in);

		result->fileEntries.push_back(fileEntry);
	}

	return result;
}
