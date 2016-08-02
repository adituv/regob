#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

#include "GobHeader.h"

void unpackGob(std::string gobpath, std::string headerpath, std::string outputpath) {
	std::ifstream headerFile(headerpath, std::ifstream::binary);

	std::unique_ptr<GobHeader> header(GobHeader::FromStream(headerFile));
	headerFile.close();

	std::ifstream dataFile(gobpath, std::ifstream::binary);

	std::for_each(header->fileEntries.cbegin(), header->fileEntries.cend(), [&dataFile, &header, &outputpath](FileEntry file) {
		auto chunks = header->GetFileChunks(file);
		std::ostringstream filename;
		filename << outputpath << std::hex << std::setw(8) << std::setfill('0') << file.nameChecksum;
	
		std::ofstream outFile(filename.str(), std::ofstream::binary);

		std::for_each(chunks.cbegin(), chunks.cend(), [&dataFile, &outFile](ChunkHeader chunk) {
			std::vector<char> buf(chunk.chunkSize);
			
			dataFile.seekg(chunk.offset);
			dataFile.read(&buf[0], chunk.chunkSize);

			outFile << &buf[0];
		});

		outFile.close();
	});

	dataFile.close();
}