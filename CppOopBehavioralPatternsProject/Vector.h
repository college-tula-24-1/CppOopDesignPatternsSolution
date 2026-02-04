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

	//TValue Current(size_t index) override;

	IIterator<TValue>* GetForwardIterator() override;
	IIterator<TValue>* GetReverceIterator() override;
};

template <typename TValue>
class ForwardIterator : public IIterator<TValue>
{
	size_t currentIndex{};
public:
	ForwardIterator(Vector<TValue>* vector)
		: IIterator<TValue>(vector), currentIndex{}{ }
	
	ForwardIterator(const ForwardIterator& other);
	ForwardIterator operator=(const ForwardIterator& other);

	void Reset() override;
	bool Next() override;
	bool IsEnd() override;
	TValue Current() override;
};

template <typename TValue>
class ReverceIterator : public IIterator<TValue>
{
	size_t currentIndex{ this->container->Size() - 1 };
public:
	ReverceIterator(Vector<TValue>* vector)
		: IIterator<TValue>(vector), currentIndex{ this->GetContainer()->Size() - 1}{ }

	ReverceIterator(const ReverceIterator& other);
	ReverceIterator operator=(const ReverceIterator& other);

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

template<typename TValue>
inline size_t Vector<TValue>::Capacity() const { return this->capacity; }

template<typename TValue>
inline TValue& Vector<TValue>::At(size_t index)
{
	if (index < 0 || index >= this->size) throw new std::out_of_range("out of range");
	return this->items[index];
}

template<typename TValue>
inline TValue& Vector<TValue>::operator[](size_t index)
{
	return this->items[index];
}

template<typename TValue>
inline void Vector<TValue>::PushBack(TValue value)
{
	if (this->size >= this->capacity)
	{
		this->capacity *= 1.5;
		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{}; i < this->size; i++)
			itemsNew[i] = this->items[i];

		delete[] this->items;
		this->items = itemsNew;
	}

	this->items[this->size++] = value;
}

template<typename TValue>
inline void Vector<TValue>::PushFront(TValue value)
{
	if (this->size >= this->capacity)
	{
		this->capacity *= 1.5;
		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{}; i < this->size; i++)
			itemsNew[i + 1] = this->items[i];

		delete[] this->items;
		this->items = itemsNew;
	}
	this->items[0] = value;
	this->size++;
}

template<typename TValue>
inline void Vector<TValue>::Insert(size_t index, TValue value)
{
	if (this->size >= this->capacity)
	{
		this->capacity *= 1.5;
		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{}; i < index; i++)
			itemsNew[i] = this->items[i];
		this->items[index] = value;
		for (size_t i{ index }; i < this->size; i++)
			itemsNew[i + 1] = this->items[i];

		delete[] this->items;
		this->items = itemsNew;
	}
	else
	{
		for (size_t i{ this->size - 1 }; i >= index; i--)
			this->items[i + 1] = this->items[i];
		this->items[index] = value;
	}
	
	this->size++;
}

template<typename TValue>
inline TValue Vector<TValue>::PopBack()
{
	TValue value{ this->items[this->size - 1] };

	if (this->size * 1.5 < this->capacity)
	{
		this->capacity = this->size;
		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{}; i < this->size; i++)
			itemsNew[i] = this->items[i];
		
		delete[] this->items;
		this->items = itemsNew;
	}

	this->size--;
	
	return value;
}

template<typename TValue>
inline TValue Vector<TValue>::PopFront()
{
	TValue value{ this->items[0] };

	if (this->size * 1.5 < this->capacity)
	{
		this->capacity = this->size;
		
		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{ 1 }; i < this->size; i++)
			itemsNew[i - 1] = this->items[i];

		delete[] this->items;
		this->items = itemsNew;
	}
	else
	{
		for (size_t i{ 1 }; i < this->size; i++)
			this->items[i - 1] = this->items[i];
	}
	this->size--;

	return value;
}

template<typename TValue>
inline TValue Vector<TValue>::Remove(size_t index)
{
	TValue value{ this->items[index] };

	if (this->size * 1.5 < this->capacity)
	{
		this->capacity = this->size;

		TValue* itemsNew = new TValue[this->capacity];

		for (size_t i{}; i < index; i++)
			itemsNew[i] = this->items[i];

		for (size_t i{ index + 1 }; i < this->size; i++)
			itemsNew[i - 1] = this->items[i];

		delete[] this->items;
		this->items = itemsNew;
	}
	else
	{
		for (size_t i{ index + 1 }; i < this->size; i++)
			this->items[i - 1] = this->items[i];
	}
	this->size--;

	return value;
}

template<typename TValue>
inline IIterator<TValue>* Vector<TValue>::GetForwardIterator()
{
	return new ForwardIterator<TValue>(this);
}

template<typename TValue>
inline IIterator<TValue>* Vector<TValue>::GetReverceIterator()
{
	return new ReverceIterator<TValue>(this);
}


/////////
template<typename TValue>
inline void ForwardIterator<TValue>::Reset()
{
	this->currentIndex = 0;
}

template<typename TValue>
inline bool ForwardIterator<TValue>::Next()
{
	this->currentIndex++;
	
	return this->currentIndex < this->GetContainer()->Size();
}

template<typename TValue>
inline bool ForwardIterator<TValue>::IsEnd()
{
	return this->currentIndex >= this->GetContainer()->Size();
}

template<typename TValue>
inline TValue ForwardIterator<TValue>::Current()
{
	//return this->container->Current(currentIndex);
	return ((Vector<TValue>*)this->GetContainer())->At(currentIndex);
}


//////////
template<typename TValue>
inline void ReverceIterator<TValue>::Reset()
{
	this->currentIndex = this->GetContainer()->Size() - 1;
}

template<typename TValue>
inline bool ReverceIterator<TValue>::Next()
{
	this->currentIndex--;

	return this->currentIndex >= 0;
}

template<typename TValue>
inline bool ReverceIterator<TValue>::IsEnd()
{
	return this->currentIndex == std::numeric_limits<size_t>::max();
}

template<typename TValue>
inline TValue ReverceIterator<TValue>::Current()
{
	return ((Vector<TValue>*)this->GetContainer())->At(currentIndex);
}
