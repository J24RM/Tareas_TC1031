#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

#ifndef DLIST_H_
#define DLIST_H_

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

public: 
	T value;
	DLink<T> *next;
	DLink<T> *previous;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), next(0), previous(0){}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void clear();
	std::string toStringForward() const;
	std::string toStringBackward() const;


	//Tarea

	void insertion(int);
	int search(int);
	void update(int, T);
	T deleteAt(int);




private:
	DLink<T> *head;
	DLink<T> * tail;
	int size;
};

// Constructores
template <class T>
DList<T>::DList(): head(0), tail(0), size(0){}

template <class T>
DList<T>::~DList(){
	clear();
}

template <class T>
DList<T>::DList(const DList<T> &){
}

//Tarea
template <class T>
void DList<T>::insertion(int val){
	DLink<T> *ptr, *newLink ;
	ptr = head;

	newLink = new DLink<T>(val);

	if (size == 0){
		head = newLink;
		tail = newLink;
	}

	else{
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}

	size++;
}

template <class T>
int DList<T>::search(int val){
	int ind = 0;
	DLink<T> *ptr;
	ptr = head;

	while(ptr != 0){
		if (ptr->value == val){
			return ind; 
		}
		ptr = ptr->next;
		ind ++; 
	}
	return -1;
}

template <class T>
void DList<T>::update(int n, T val){
	DLink<T> *ptr;
	ptr = head;

	while(ptr != 0){
		if (n == 0){
			ptr->value = val;
		}
		ptr = ptr->next;
		n--;
	}
}

template <class T>
T DList<T>::deleteAt(int n){
	DLink<T> *ptr;
	ptr = head;
	T val;
	int pos = 0;

	if(n == 0){
		val = ptr->value;

		if (tail == head){
			head = 0;
			tail = 0;
		}
		else{
			head = ptr->next;
			ptr->next->previous = 0;
		}		

		delete ptr;

		size--;

		return val;
	}

	while(ptr != 0){
		if (pos == n)
		{
			val = ptr->value;
			ptr->previous->next = ptr->next;

			if (ptr->next != 0) {
				ptr->next->previous = ptr->previous;
			}

			delete ptr; 
			return val;
			size--;
		}
    	ptr = ptr->next;
    	pos++;
  }
  return T();
}


template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif