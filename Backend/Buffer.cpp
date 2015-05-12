#include "Buffer.hpp"
#include <fstream>
#include <string>


Buffer::Buffer()
{
}


Buffer::~Buffer()
{
}

Buffer* Buffer::fromFile(const std::string filename)
{
	Buffer *buffer = new Buffer();
	buffer->load(filename);
	return buffer;
}

void Buffer::load(const std::string filename)
{
	std::ifstream file(filename);
	u64			  i = 0;
	std::string   line;

	while (std::getline(file, line))
		lines[i++] = line;
}