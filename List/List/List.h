#pragma once

#include "Node.h"
#include <iostream>

template <typename T>
class List  {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	List();
	List(const T* arr, int n);
	List(const List<T>& other);

	~List();

	int getSize() const;
	void swap(List<T>& other);
	bool isEmpty() const;
	void clear();

	Node<T>* find(const T& key);
	Node<T>* find(const T& key) const;
	void insertHead(const T& value);
	void insertTail(const T& value);
	void insertAt(int pos, const T& value);
	void insertAfter(const T& key, const T& value);
	void removeHead();
	void removeTail();
	void removeAr(int pos);
	void remove(const T& key);
	Node<T>* maxElement() const;
	Node<T>* minElement() const;
	void sort();

};

