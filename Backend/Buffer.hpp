#pragma once

#include <unordered_map>
#include <cstdint>

class Buffer
{
public:
	typedef std::unordered_map<uint64_t, std::string> LineBuffer; //todo: handle different encodings

	Buffer();
	~Buffer();

	static Buffer* fromFile(const std::string filename);

private:
	void load(const std::string filename);

	LineBuffer lines;
};