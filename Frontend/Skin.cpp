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
	json_error_t error;
	json_t *root = json_load_file(filename.c_str(), 0, &error);

	auto getString = [root](const json_t* obj, const char* str) -> std::string
	{
		json_t *value = json_object_get(obj, str);
		if (!json_is_string(value))
			throw std::runtime_error("error: " + std::string(str) + "was expected to be a string");
		return std::string(json_string_value(value));

	};


	auto getColor = [root](const json_t* obj, const char* str) -> Color
	{
		Color result;
		json_t *value = json_object_get(obj, str);

		if (!json_is_array(value))
			throw std::runtime_error("error: " + std::string(str) + "was expected to be an arry");

		for (int i = 0; i < json_array_size(value); i++)
			result[i] = json_integer_value(json_array_get(value, i)); // this should check for error

		return result;

	};

	if (!root)
		throw std::runtime_error("error: on line " + std::to_string(error.line) + ": " + std::string(error.text));

	if (!json_is_array(root))
		throw std::runtime_error("error: root is not an array");


	for (int i = 0; i < json_array_size(root); i++)
	{
		json_t *data = json_array_get(root, i);

		if (!json_is_object(data))
			throw std::runtime_error("error: entry at " + std::to_string(i + 1) + " was expected to be a object");


		Entry entry;

		entry.name = getString(data, "name");
		entry.bgColor = getColor(data, "bgColor");
		entry.fontColor = getColor(data, "fontColor");


		/*
		json_t *layers = json_object_get(data, "layers");
		if (!json_is_array(layers))
			throw std::runtime_error("error: layers is not an array");

		for (int i = 0; i < json_array_size(layers); i++)
		{
			json_t *layer = json_array_get(layers, i);
		}
		*/
	}
}

void Skin::draw(const std::string name, const Window* window)
{
}