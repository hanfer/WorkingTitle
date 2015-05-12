#include "Skin.hpp"


#include <vector>
#include <fstream>
#include <iostream>
#include <jansson.h>

Skin::Skin(const std::string pFilename)
	: filename(pFilename)
{
}

Skin::~Skin()
{
}

void Skin::load()
{
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open())
		throw std::runtime_error("could not open file");

	std::vector<char> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	json_error_t error;
	json_t *root = json_loads(data.data(), 0, &error);
}

void Skin::draw(const std::string name, const Window* window)
{
}