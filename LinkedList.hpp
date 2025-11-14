#pragma once
#include <iostream>
using namespace std;
template<typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};


template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;
		const Node<T>* on = list.getHead();
		for (unsigned int i = 0; i < list.getCount(); i++) {
			addTail(on->data);
			on = on->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T> * head;
	Node<T>* tail;
	unsigned int count;

};
template<typename T>
void LinkedList<T>::printForward() const {
	Node<T>* current = this->head;
	for (int i = 0; i < count; i++) {
		std::cout << current->data << std::endl;
		current = current->next;
	}
}
template<typename T>
void LinkedList<T>::printReverse() const {
	Node<T>* current = this->tail;
	for (int i = count - 1; i <= 0; i--) {
		std::cout << current->data << std::endl;
		current = current->prev;
	}
}
template<typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const {
	return this->count;
}
template<typename T>
Node<T>* LinkedList<T>::getHead() {
	return this->head;
}
template<typename T>
const Node<T>* LinkedList<T>::getHead() const {
	return this->head;
}
template<typename T>
Node<T>* LinkedList<T>::getTail() {
	return this->head;
}
template<typename T>
const Node<T>* LinkedList<T>::getTail() const {
	return this->head;
}
template<typename T>
void LinkedList<T>::addHead(const T &data) {
	Node<T>* newNode = new Node<T>(data);
	this->head->prev = newNode;
	newNode->next = this->head;
	this->head = newNode;
}
template<typename T>
void LinkedList<T>::addTail(const T &data) {
	Node<T>* newNode = new Node<T>(data);
	this->tail->next = newNode;
	newNode->prev = this->tail;
	this->tail = newNode;
}
template<typename T>
bool LinkedList<T>::removeHead() {
	if (this->head == nullptr) {
		return false;
	}
	this->head = this->head->next;
	delete this->head->prev;
	this->head->prev = nullptr;
	return true;
}
template<typename T>
bool LinkedList<T>::removeTail() {
	if (this->tail == nullptr) {
		return false;
	}
	this->tail = this->tail->prev;
	delete this->tail->next;
	this->tail->next = nullptr;
	return true;
}
template<typename T>
void LinkedList<T>::clear() {
	if (this->count == 0) {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
		return;
	}
	Node<T>* current = this->head;
	while (current != nullptr) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	this->head = nullptr;
	this->tail = nullptr;
	this->count = 0;
}
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this != &other) {
		this->clear();
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
	}
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
	return *this;
}
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	clear();
	if (rhs.getCount() == 0) {
		return *this;
	}
	const Node<T>* current = rhs.getHead();
	for (unsigned int  i = 0; i < rhs.getCount(); i++) {
		addTail(current->data);
	}
	return *this;
	// if (this != &rhs) {
	// 	this->clear();
	// 	this->count = rhs.count;
	// 	Node<T>* current = rhs.head;
	// 	if (rhs.count != 0) {
	// 		this->addTail(current->data);
	// 		if (rhs.count == 1) {
	// 			this->head->next = nullptr;
	// 			return *this;
	// 		}
	// 		current = current->next;
	// 	} else {
	// 		this->head = nullptr;
	// 		this->tail = nullptr;
	// 		this->count = 0;
	// 		return *this;
	// 	}
	// 	for (int i = 1; i < rhs.count; i++) {
	// 		this->addTail(current->data);
	// 		current = current->next;
	// 	}
	// }
	// return *this;
}