#pragma once

#include <string>
#include <vector>

#include "Control.hpp"
#include "Skin.hpp"

class Window : public Control
{
public:
	Window();
	~Window();

	virtual bool init() = 0;
	virtual void run() = 0;

	virtual void drawRect(int x, int y, int width, int height, Skin::Color color);
	virtual void drawTexture(const std::string filename, int x, int y) = 0;

protected:
	void loadImage(const std::string &filename, std::vector<unsigned char> &data, unsigned int &width, unsigned int &height);

};