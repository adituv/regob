#ifndef UTIL_H
#define UTIL_H

#include <istream>

template <typename T>
inline T readTypeBE(std::istream& in) {
	T result;
	in.read(reinterpret_cast<char*>(&result), sizeof(T));

	char* raw = reinterpret_cast<char*>(&result);

	for (int i = 0; i < sizeof(T) / 2; i++) {
		char temp = raw[i];
		raw[i] = raw[sizeof(T) - i - 1];
		raw[sizeof(T) - i - 1] = temp;
	}

	return result;
}

#endif
