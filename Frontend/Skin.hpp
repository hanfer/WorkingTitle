#pragma once

#include "Window.hpp"

#include <string>
#include <list>
#include <unordered_map>


class Skin
{
public:
	struct Entry
	{
		struct Layer
		{
			std::string texture;
			float opacity;
		};
		typedef std::list<Layer> LayerList;

		std::string name;
		LayerList layers;
	};
	typedef std::unordered_map<std::string, Entry> EntryMap;

	Skin(const std::string pFilename);
	~Skin();

	void load();
	void draw(const std::string name, const Window *window);

private:
	const std::string	filename;
	EntryMap			entryMap;
};

