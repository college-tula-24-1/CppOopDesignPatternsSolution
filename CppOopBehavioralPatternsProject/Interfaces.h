#pragma once

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
	size_t size;
public:
	virtual ~Container() = default;
	size_t Size() const { return this->size; }

	virtual IIterator* GetIterator() = 0;
};


/// <summary>
/// Base Interface for iterators
/// </summary>
/// <typeparam name="TValue"></typeparam>
template <typename TValue>
class IIterator
{
protected:
	Container* container;
public:
	IIterator(Container* container) : container{ container } {}

	virtual void Reset() = 0;
	virtual bool Next() = 0;
	virtual bool IsEnd() = 0;
	virtual TValue Current() = 0;
};