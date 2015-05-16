#pragma once

#include <string>
#include <list>
#include <unordered_map>

#include "Window.hpp"
#include "Global.hpp"


class Skin
{
public:
	struct Color
	{
		Color() // Constructor in struct? Evil me :D
			: r(255)
			, g(255)
			, b(255)
			, a(255)
		{}

		u8 r;
		u8 g;
		u8 b;
		u8 a;

		unsigned char& operator [] (int index) 
		{
			switch (index)
			{
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
			default:
				throw std::runtime_error("Out of Bounds");
			}
		}
	};

	struct Entry
	{
		struct Layer
		{
			std::string texture;
			float opacity;
		};
		typedef std::list<Layer> LayerList;

		std::string name;
		Color bgColor;
		Color fontColor;

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

