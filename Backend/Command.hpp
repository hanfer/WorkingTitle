#pragma once

#include <iostream>
#include <string>

#include "Any.hpp"

class Backend;

class Command
{
public:
	virtual ~Command() {}

	virtual void validate(const AnyList& params) = 0;
	virtual void execute(Backend *backend) = 0;
	virtual void undo(Backend *backend) = 0;

	template<typename T>
	static Command* create()
	{
		return new T();
	}
};

class CreateBuffer : public Command
{
public:

	void validate(const AnyList& params) override
	{
		name = params.get<std::string>(0);
	};

	void execute(Backend* backend) override
	{
		std::cout << "CreateBuffer(" << name << ") execute" << std::endl;
	};

	void undo(Backend* backend) override
	{
		std::cout << "CreateBuffer(" << name << ") undo" << std::endl;
	};

private:
	std::string name;
};