#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "GobHeader.h"

int main(int argc, const char* argv[]) {
	auto args = parseArgs(argc, argv);

	if (argc < 2) {
		std::cerr << "No file given.";
		return 1;
	}

	std::ifstream headerFile(argv[1], std::ifstream::binary);
	std::stringstream headerData;
	headerData << headerFile.rdbuf();
	
	std::unique_ptr<GobHeader> header(GobHeader::FromStream(headerData));
	headerFile.close();


	return 0;
}


int parseArgs(int argc, const char* argv[]) {

}