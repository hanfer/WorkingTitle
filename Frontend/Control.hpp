#pragma once

#include <string>
#include <list>

class Control
{
public:
	Control(std::string pName, Control *pParent = nullptr);

	std::string fullname();

private:
	void addChild(Control *control);

	Control* parent;
	std::string name;
	std::list<Control *> children;
};