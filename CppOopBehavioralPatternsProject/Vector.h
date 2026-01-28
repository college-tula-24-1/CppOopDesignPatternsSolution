#pragma once
#include "Interfaces.h"

template <typename TValue>
class Vector : public Container<TValue>
{
	TValue* items;
	size_t capacity;
public:
	Vector();
	Vector(size_t size);
	Vector(const Vector& other);

	~Vector();

	size_t Capacity() const;

	TValue& At(size_t index);
	TValue& operator[](size_t index);

	void PushBack(TValue value);
	void PushFront(TValue value);
	void Insert(size_t index, TValue value);

	TValue PopBack();
	TValue PopFront();
	TValue Remove(size_t index);

	IIterator* GetIterator() override;
};

template <typename TValue>
class ForwardIterator : public IIterator<TValue>
{
	size_t currentIndex{};
public:
	ForwardIterator(Vector* vector)
		: IIterator(vector), currentIndex{}{ }
	
	ForwardIterator(const ForwardIterator& other);
	ForwardIterator operator=(const ForwardIterator& other);

	void Reset() override;
	bool Next() override;
	bool IsEnd() override;
	TValue Current() override;
};

/////////
template<typename TValue>
inline Vector<TValue>::Vector()
{
	this->capacity = 2;
	this->size = 0;
	this->items = new TValue[this->capacity];
}

template<typename TValue>
inline Vector<TValue>::Vector(size_t size)
{
	this->capacity = size * 1.5;
	this->items = new TValue[this->capacity]{};
	this->size = size;
}

template<typename TValue>
inline Vector<TValue>::Vector(const Vector& other)
{
	this->size = other.size;
	this->capacity = this->size * 1.5;
	this->items = new TValue[this->capacity];

	for (int i{}; i < other.size; i++)
		this->items[i] = other.items[i];
}

template<typename TValue>
inline Vector<TValue>::~Vector()
{
	delete[] this->items;
}
