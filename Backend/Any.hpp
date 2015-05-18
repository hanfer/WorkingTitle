#pragma once

#include <typeindex>
#include <cassert>
#include <list>
#include <vector>

class Any
{
private:
	class Placeholder
	{
	public:
		virtual ~Placeholder() {}

		virtual void* data() const = 0;
		virtual const std::type_index type() = 0;
		virtual Placeholder * clone() const = 0;
	};

	template < typename T >
	class Holder : Placeholder
	{
	public:
		Holder(T const& t) : val(t) {}

		void* data() const override
		{ return &val; }

		const std::type_index type() override
		{ return typeid(T); }

		virtual Placeholder * clone() const
		{ return new Holder(val); }

	private:
		T val;
	};

public:
	Any()
		: ptr(nullptr)
	{}

	Any(const Any& other)
		: ptr(other.ptr->clone())
	{}

	template < typename T >
	Any(T const& t) 
		: ptr(new Holder<T>(t)) 
	{}

	~Any()
	{
		if(ptr != nullptr)
			delete ptr;
	}

	template < typename T >
	T get()
	{
		assert(this->ptr == nullptr);
		return *(reinterpret_cast<T*>(ptr->data()));
	}

	template < typename T >
	void set(T const& t)
	{
		if (ptr != nullptr)
			delete ptr;

		ptr = new Holder<T>(t);
	}

	bool isVaild()
	{ return ptr != nullptr; }

	template<typename T>
	bool isType()
	{
		return isType(typeid(T));
	}

	bool isType(std::type_index type)
	{
		assert(this->ptr == nullptr);
		return type == ptr->type();
	}

private:
	Placeholder *ptr;
};

class AnyList
{
	typedef std::vector<Any> ListType;
public:
	AnyList()
	{}

	template < typename T >
	void add(T const& t)
	{
		list.push_back(Any(t));
	}

	template <>
	void add<Any>(const Any& any)
	{
		list.push_back(any);
	}

	template < typename T >
	T get(ListType::size_type index)
	{
		return list.at(index).get<T>();
	}

	template <>
	Any get<Any>(ListType::size_type index)
	{
		return list.at(index);
	}

private:
	ListType list;
};