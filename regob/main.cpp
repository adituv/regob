#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "GobHeader.h"

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		std::cerr << "No file given.";
		return 1;
	}

	std::ifstream headerFile(argv[1], std::ifstream::binary);
	std::stringstream headerData;
	headerData << headerFile.rdbuf();
	
	std::unique_ptr<GobHeader> header(GobHeader::FromStream(headerData));
	headerFile.close();

	auto files = header->GetFileChunks();

	std::cout << std::hex << std::setfill('0');

	std::for_each(files.cbegin(), files.cend(), [](std::vector<ChunkHeader> file) {
		std::for_each(file.cbegin(), file.cend(), [](ChunkHeader chunk) {
			std::cout << std::setw(8) << chunk.unk001 << ", ";
		});
		std::cout << std::endl << std::endl;
	});

	std::cin.get();

	return 0;
}
