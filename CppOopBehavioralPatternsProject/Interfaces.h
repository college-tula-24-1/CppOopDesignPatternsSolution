#pragma once
#include <exception>
#include <stdexcept>

template <typename TValue>
class IIterator;

/// <summary>
/// Base abstract class for conteiners
/// </summary>
/// <typeparam name="TValue"></typeparam>

template <typename TValue>
class Container
{
protected:
	size_t size{};
public:
	virtual ~Container() = default;
	size_t Size() const { return this->size; }

	virtual IIterator<TValue>* GetForwardIterator() = 0;
	virtual IIterator<TValue>* GetReverceIterator() = 0;
};


/// <summary>
/// Base Interface for iterators
/// </summary>
/// <typeparam name="TValue"></typeparam>
template <typename TValue>
class IIterator
{
protected:
	Container<TValue>* container;

	Container<TValue>*& GetContainer() { return this->container; }
public:
	IIterator(Container<TValue>* container) : container{ container } {}

	virtual void Reset() = 0;
	virtual bool Next() = 0;
	virtual bool IsEnd() = 0;
	virtual TValue Current() = 0;
};
