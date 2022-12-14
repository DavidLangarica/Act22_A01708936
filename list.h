// =================================================================
//
// File: list.h
// Author: David René Langarica Hernández | A01708936
// Date: 5 de octubre de 2022
//
// =================================================================
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class DoubleLinkedList;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*, Node<T>*);

	T	    	value;
	Node<T> *previous, *next;

	friend class DoubleLinkedList<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), previous(NULL), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node *prev, Node* nxt)
	: value(val), previous(prev), next(nxt) {
}

// =================================================================
// Definition of the DoubleLinkedList class
// =================================================================
template <class T>
class DoubleLinkedList {
private:
	Node<T> *head;
	uint 		size;

public:
	DoubleLinkedList();
	~DoubleLinkedList();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T front() const;
	T last() const;
	T before(T) const;
	T after(T) const;

	void push_front(T);
	void push_back(T);
	void insert_before(T, T);
	void insert_after(T, T);

	T    pop_front();
	T 	 pop_back();
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
DoubleLinkedList<T>::DoubleLinkedList() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

// =================================================================
// Returns if the DoubleLinkedList is empty or not
//
// @returns true if the DoubleLinkedList is empty, false otherwise.
// =================================================================
template <class T>
bool DoubleLinkedList<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the DoubleLinkedList.
//
// @returns size, the number of items in the DoubleLinkedList.
// =================================================================
template <class T>
uint DoubleLinkedList<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the DoubleLinkedList.
//
// @returns true if val is in the DoubleLinkedList, false otherwise
// =================================================================
template <class T>
bool DoubleLinkedList<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the DoubleLinkedList.
//
// @returns a string containing all the elements of the DoubleLinkedList.
// =================================================================
template <class T>
std::string DoubleLinkedList<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the DoubleLinkedList.
//
// @returns the object T at the beginning of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the DoubleLinkedList.
//
// @returns the object T at the end of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the value before the first occurrence if certain value.
//
// @throws NoSuchelement, if val is not on the list.
// @Complexity O(n), depende de que no haya alguna interrupción, de esa forma el ciclo se ejecutará tantas veces como esto no pase.
// =================================================================
template <class T>
T DoubleLinkedList<T>::before(T val) const {
	if (contains(val) == false){
		// val isn't part of the list
		throw NoSuchElement();
	}

	else {
		Node<T> *prev_node = head;
		Node<T> *temp_node = NULL;
		T temp_val;

		if(val == head->value){
			// val is the first element of the list
			throw NoSuchElement();
		}

		while(prev_node){
			
			if (prev_node->value == val){
				// the element of the current node matches the val number
				temp_node = prev_node->previous;
				temp_val = temp_node->value;
				return temp_val;
			}

			prev_node = prev_node->next;
		}
	}
	return val;
}

// =================================================================
// Returns the value after the first occurrence of certain value.
//
// @throws NoSuchelement, if val is not on the list.
// @Complexity O(n), solo existe un ciclo while que depende de la condición que el nodo siguiente al "next_node" no sea NULL, por lo que se
// ciclará tantas veces sean necesarias mientras que la condición se cumpla.
// =================================================================
template <class T>
T DoubleLinkedList<T>::after(T val) const {
	if (contains(val) == false){
		// val is not on the list
		throw NoSuchElement();
	}

	else {
		Node<T> *next_node = head;
		Node<T> *temp_node = NULL;
		T temp_val;

		while(next_node->next != NULL){
			// the element of the current node matches the val number
			if (next_node->value == val){
				temp_node = next_node->next;
				temp_val = temp_node->value;
				return temp_val;
			}

			next_node = next_node->next;
		}

		throw NoSuchElement();

	}
	return val;
}

// =================================================================
// Add an item to the beginning of the DoubleLinkedList. Increase the size of
// the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_front(T val) {
	Node<T> *q, *p;

	q = new Node<T>(val);
	if (head == NULL) {
		q->next = NULL;
		q->previous = NULL;
	} else {
		p = head;

		q->next = p; // q->next = head;
		q->previous = NULL;

		p->previous = q; //head->previous = q;
	}
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the DoubleLinkedList. Increase the size of
// the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	q->previous = p;

	p->next = q;
	size++;
}

// =================================================================
// Insert an element before the first occurrence of a certain value.
//
// @throws NoSuchelement, if lookingFor is not on the list.
// @Complexity O(n), se ciclará tantas veces como la condición de no llegar al valor buscado se cumpla.
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_before(T lookingFor, T newVal) {
	Node<T> *temp_node;
	Node<T> *new_node = new Node<T>(newVal);

	if (head->value == lookingFor){
		// if lookingFor is in the first node
		push_front(newVal);
	}

	else if (contains(lookingFor) == false){
		// If lookingFor doesn't match any element from the list
		throw NoSuchElement();
	}

	else {

		temp_node = head;

		while (temp_node->value != lookingFor){
			// Move to the desired node
			temp_node = temp_node->next;
		}
		
		new_node->previous = temp_node->previous;
		temp_node->previous = new_node;

		if (new_node->previous != NULL){
			(new_node->previous)->next = new_node;
			new_node->next = temp_node;
		}

		size++;
	}
}

// =================================================================
// Insert an element after the first occurrence of a certain value.
//
// @throws NoSuchelement, if lookingFor is not on the list.
// @Complexity O(n), como el anterior, el ciclo while se ciclará tantas veces como no se cumpla la condición de llegar al valor buscado.
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_after(T lookingFor, T newVal) {
	Node<T> *temp_node;
	Node<T> *new_node = new Node<T>(newVal);

	if (contains(lookingFor) == false){
		// lookingFor is not part of the list
		throw NoSuchElement();
	}

	else {

		temp_node = head;

		while (temp_node->value != lookingFor){
			// Move to the desired node
			temp_node = temp_node->next;
		}

		if (temp_node->next == NULL){
			push_back(newVal);
		}

		else{

			new_node->next = temp_node->next;
			temp_node->next = new_node;

			if (new_node->next != NULL)
			{
				(new_node->next)->previous = new_node;
				new_node->previous = temp_node;
			}
			size++;
		}
	}
}

// =================================================================
// Delete the item at the beginning of the DoubleLinkedList.
//
// @returns the element that was at the beginning of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_front() {
	T val;
	Node<T> *p, *q;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	if (size == 1) {
		head = p->next;
	} else {
		q = p->next;

		q->previous = NULL;
		head = q;
	}

	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the item at the end of the DoubleLinkedList.
//
// @returns the element that was at the end of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}
	q = p->previous;

	q->next = p->next;

	val = p->value;
	delete p;
	size--;

	return val;
}

#endif /* DoubleLinkedList_H */
