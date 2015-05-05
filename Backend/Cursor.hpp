#pragma once
#include <cinttypes>

class Cursor
{
public:
	Cursor();
	~Cursor();

private:
	uint64_t line;
	uint64_t column;
};

