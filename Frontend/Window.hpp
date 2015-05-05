#pragma once

#include <string>
#include <vector>
#include "Control.hpp"

class Window : public Control
{
public:
	Window();
	~Window();

	virtual bool init() = 0;
	virtual void run() = 0;

	virtual void drawTexture(const std::string filename, int x, int y);

protected:
	void loadImage(const std::string &filename, std::vector<unsigned char> &data, unsigned int &width, unsigned int &height);

};