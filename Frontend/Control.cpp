#include "Control.hpp"

Control::Control(std::string pName, Control* pParent)
	: parent(pParent)
	, name(pName)
{
	if (parent != nullptr)
		parent->addChild(this);
}

std::string Control::fullname()
{
	std::string temp;

	if (parent != nullptr)
		temp = parent->fullname();

	temp += "." + name;

	return temp;
}

void Control::addChild(Control* control)
{
	children.push_back(control);
}