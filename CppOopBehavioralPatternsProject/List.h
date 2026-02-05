#pragma once
#include <iostream>
#include "Interfaces.h"

namespace ListNamespace
{
	template <typename TValue>
	struct Node
	{
		TValue value{};
		Node<TValue>* next{};
		Node<TValue>* prev{};
	};

	template <typename TValue>
	class List : public Container<TValue>
	{
		Node<TValue>* front{};
		Node<TValue>* back{};
	public:
		List();
		~List();

		void Clear();

		void PushFront(TValue value);
		TValue PopFront();

		void PushBack(TValue value);
		TValue PopBack();

		Node<TValue>* FindNode(TValue value);
		void InsertAfter(Node<TValue>* node, TValue value);
		void InsertBefore(Node<TValue>* node, TValue value);
		TValue Remove(Node<TValue>* node);

		IIterator<TValue>* Find(TValue value);
		void InsertAfter(IIterator<TValue>* node, TValue value);
		void InsertBefore(IIterator<TValue>* node, TValue value);
		TValue Remove(IIterator<TValue>* node);

		IIterator<TValue>* GetForwardIterator() override { return nullptr; }
		IIterator<TValue>* GetReverceIterator() override { return nullptr; }

		void ConsoleShow();
	};
	template<typename TValue>
	inline List<TValue>::List(){}

	template<typename TValue>
	inline List<TValue>::~List() { this->Clear(); }

	template<typename TValue>
	inline void List<TValue>::Clear()
	{
		while (this->front != this->back)
		{
			this->front = this->front->next;
			delete this->front->prev;
		}
		delete this->front;
		this->front = this->back = nullptr;
		this->size = 0;
	}

	template<typename TValue>
	inline void List<TValue>::PushFront(TValue value)
	{
		Node<TValue>* node{ new Node<TValue> };
		node->value = value;

		if (this->size > 0)
		{
			node->next = this->front;
			this->front->prev = node;	
		}
		else
		{
			this->back = node;
		}

		this->front = node;

		this->size++;
	}

	template<typename TValue>
	inline TValue List<TValue>::PopFront()
	{
		if (this->size == 0)
			throw new std::runtime_error("Attempt to delete from an empty list");

		TValue value{ this->front->value };
		this->front = this->front->next;

		if (this->size > 1)
		{
			delete this->front->prev;
			this->front->prev = nullptr;
		}
		else
		{
			delete this->back;
			this->back = nullptr;
		}

		

		this->size--;

		return value;
	}

	template<typename TValue>
	inline void List<TValue>::ConsoleShow()
	{
		Node<TValue>* node{ this->front };
		while (node)
		{
			std::cout << node->value << " ";
			node = node->next;
		}
		std::cout << "\n";
	}

}




