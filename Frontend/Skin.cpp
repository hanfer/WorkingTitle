#include "Skin.hpp"


#include <vector>
#include <fstream>
#include <iostream>

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
	char *endptr;

	int status = jsonParse(data.data(), &endptr, &root, allocator);

	if (status != JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - data.data());
		exit(EXIT_FAILURE);
	}

	if (root.getTag() != JSON_ARRAY)
		throw std::runtime_error("parse error");

	for (auto val : root)
		loadValue(val->value);
}

void Skin::draw(const std::string name, const Window* window)
{
}

void Skin::loadValue(JsonValue value)
{
	Entry entry;

	for (auto val : value)
	{
		if (strcmp(val->key, "name") == 0)
			entry.name = val->value.toString();

		if (strcmp(val->key, "layers") == 0)
			loadLayers(entry, val->value);
	}

	entryMap.emplace(entry.name, entry);
}

void Skin::loadLayers(Entry& entry, JsonValue value)
{
	if (value.getTag() != JSON_ARRAY)
		throw std::runtime_error("parse error");

	for (auto layer : value)
	{
		Entry::Layer layerEntry;

		if (strcmp(layer->key, "texture") == 0)
			layerEntry.texture = layer->value.toString();

		if (strcmp(layer->key, "opacity") == 0)
			layerEntry.opacity = static_cast<float>(layer->value.toNumber());

		entry.layers.push_back(layerEntry);
	}
}