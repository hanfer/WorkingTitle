#pragma once

#include <iostream>
#include <string>

#include "Any.hpp"

class Command
{
public:
	Command() = delete;
	Command(const AnyList& pParams)
		: params(pParams)
	{}

	virtual ~Command() {}

	virtual void execute() = 0;
	virtual void undo() = 0;

	const AnyList params;
};

class CreateBuffer : public Command
{
public:
	void execute() override {};
	void undo() override {};
};