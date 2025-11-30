#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

using namespace std;

template <class T> class List;

template <class T> 
class Link{
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;


};

template <class T>
Link<T>::Link(T val){
	value = val;
	next = 0;
}

template <class T>
Link<T>::Link(T val, Link<T>* nxt){
	value = val;
	next = nxt;
}

template <class T>
Link<T>::Link(const Link<T> &source){
	value = source.value;
	next = source.next;
}



template <class T>
class List{
public:
	List();

	//Funciones

    std::string toString() const;

	void insertion(T);

	int search(T);

	void update(int, T);

	T deleteAt(int);

private:
	Link<T> *head;
	int 	size;


};

template <class T>
List<T>::List(){
head = 0;
size = 0;
}

template <class T>
void List<T>::insertion(T val){
	Link<T> *ptr , *newLink;
	ptr = head;

	newLink = new Link<T>(val);

	if(head == 0){
		head = newLink;
		size++;
		return;
	}

	while(ptr->next != 0){
		ptr = ptr->next;
	}
	newLink->next = 0;
	ptr->next = newLink;
	size++;
}

template <class T>
int List<T>::search(T val){
	Link<T> *ptr;
	ptr = head;
	int i = 0;

	while(ptr != 0){
		if (ptr->value == val){
			return i;
		}
		ptr = ptr->next;
		i++;
	}
	return -1;

}

template <class T>
void List<T>::update(int n, T val){
	Link<T> *ptr;
	ptr = head;
	int count = 0;
	while(ptr != 0){
		if(count == n){
			ptr->value = val; 
			return;
		}
		ptr = ptr->next;
		count++;
	}

}

template <class T>
T List<T>::deleteAt(int n){
	Link<T> *ptr, *ptrD;
	T val;
	ptr = head;

	if(n == 0) {
		ptrD = head;
		val = head->value;
		head = head->next;
		delete ptrD;
		size--;
		return val;
	}
	
	int count = 0;
	while(ptr->next != 0){
		if(count == n-1){
			ptrD = ptr->next;
			val = ptrD->value;
			ptr->next = ptrD->next;
			delete ptrD;
			size--;
			return val;
		}
		ptr = ptr->next;
		count++;
	}	
	return T();
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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

#endif 
