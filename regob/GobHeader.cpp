#include "GobHeader.h"

#include <iostream>
#include "util.h"

using namespace std;


GobHeader::GobHeader()
{
}


GobHeader::~GobHeader()
{
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

	for (auto iter = result->chunkHeaders.begin(); iter != result->chunkHeaders.end(); iter++) {
		iter->unk001 = readTypeBE<uint32_t>(in);
	}

	for (unsigned int i = 0; i < result->fileCount; i++) {
		auto fileEntry = FileEntry();

		fileEntry.nameChecksum = readTypeBE<uint32_t>(in);
		fileEntry.fileSize = readTypeBE<uint32_t>(in);
		fileEntry.firstChunk = readTypeBE<uint32_t>(in);
	}

	return result;
}
