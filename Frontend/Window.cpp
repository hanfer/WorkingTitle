#include "Window.hpp"

#include "lodepng.hpp"

Window::Window()
{
	
}

Window::~Window()
{
	
}

void Window::loadImage(const std::string &filename, std::vector<unsigned char> &data, unsigned int &width, unsigned int &height)
{
	unsigned error = lodepng::decode(data, width, height, filename);

	if (error) 
		throw std::runtime_error(lodepng_error_text(error));
}
