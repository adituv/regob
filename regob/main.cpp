#include <fstream>
#include <iostream>
#include <sstream>

#include "GobHeader.h"

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		std::cerr << "No file given.";
		return 1;
	}

	GobHeader* header;
	std::ifstream headerFile(argv[1], std::ifstream::binary);
	std::stringstream headerData;
	headerData << headerFile.rdbuf();
	

	header = GobHeader::FromStream(headerData);
	headerFile.close();
	return 0;
}
