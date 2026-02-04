#pragma once
#include "Interfaces.h"

template <typename TValue>
struct Node
{
	TValue value;
	Node<TValue>* next;
};

template <typename TValue>
class ForwardList : public Container<TValue>
{
protected:
	Node<TValue>* head{};

public:
	ForwardList() : head{ nullptr } { this->size = 0; }

	Node<TValue>* Head() { return this->head; }

	void Push(TValue value);
	TValue Pop();

	void Show();

	TValue Peek();

	Node<TValue>* Find(TValue value);
	void Insert(Node<TValue>* node, TValue value);
	TValue Remove(Node<TValue>* node);

	IIterator<TValue>* GetForwardIterator() override;
	IIterator<TValue>* GetReverceIterator() override { return nullptr; }
};

template <typename TValue>
class ForwardListForwardIterator : public IIterator<TValue>
{
	Node<TValue>* currentNode{};
public:
	ForwardListForwardIterator(ForwardList<TValue>* list)
		: IIterator<TValue>(list), currentNode{ list->Head() } { }


	void Reset() override
	{
		this->currentNode = ((ForwardList<TValue>*)this->GetContainer())->Head();
	}

	bool Next() override
	{
		if (currentNode)
			currentNode = currentNode->next;
		
		return !(bool)currentNode;
	}

	bool IsEnd() override
	{
		return !(bool)currentNode;
	}

	TValue Current() override
	{
		return this->currentNode->value;
	}

};

template<typename TValue>
inline void ForwardList<TValue>::Push(TValue value)
{
	Node<TValue>* node = new Node<TValue>;
	node->value = value;
	node->next = this->head;
	
	this->head = node;
	this->size++;
}

template<typename TValue>
inline TValue ForwardList<TValue>::Pop()
{
	TValue value{ head->value };
	Node<TValue>* node = this->head;

	this->head = this->head->next;
	delete node;
	this->size--;

	return value;
}

template<typename TValue>
inline void ForwardList<TValue>::Show()
{
	Node<TValue>* node{ this->head };
	while (node)
	{
		std::cout << node->value << " ";
		node = node->next;
	}
	std::cout << "\n";
}

template<typename TValue>
inline TValue ForwardList<TValue>::Peek()
{
	return this->head->value;
}

template<typename TValue>
inline Node<TValue>* ForwardList<TValue>::Find(TValue value)
{
	Node<TValue>* node{ this->head };
	while (node)
	{
		if (node->value == value)
			break;
		node = node->next;
	}
	return node;
}

template<typename TValue>
inline void ForwardList<TValue>::Insert(Node<TValue>* node, TValue value)
{
	Node<TValue>* nodeNew = new Node<TValue>;
	nodeNew->value = value;
	nodeNew->next = node->next;

	node->next = nodeNew;

	this->size++;
}

template<typename TValue>
inline TValue ForwardList<TValue>::Remove(Node<TValue>* node)
{
	TValue value{ node->value };

	Node<TValue>* nodeBefore{ this->head };
	while (nodeBefore->next != node)
		nodeBefore = nodeBefore->next;

	nodeBefore->next = node->next;
	delete node;

	this->size--;
	return value;
}

template<typename TValue>
inline IIterator<TValue>* ForwardList<TValue>::GetForwardIterator()
{
	return new ForwardListForwardIterator(this);
}



