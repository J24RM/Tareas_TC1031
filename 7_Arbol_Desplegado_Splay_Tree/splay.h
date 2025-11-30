/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 3.3 Implementacion Splay
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*		Nota: Esta imlpementación es bottom up, no divide al árbol para la operacións
*		de barrado
*/

#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
	if(val < value){
		if(left != 0){
			return left->add(val);
		}
		else{
			Node<T> *added = new Node<T>(val);
			added->parent = this;
			left = added;
			return left;
		}
	}
	else{
		if(right != 0){
			return right->add(val);
		}
		else{
			Node<T> *added = new Node<T>(val);
			added->parent = this;
			right = added;
			return right;
		}

	}

}

template <class T>
Node<T>* Node<T>::find(T val) {
	if(val == value){
		return this;
	}

	else if(val < value){
		return left->find(val);
	}
	else{
		return right->find(val);
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	// Movimiento
	if(val < value){
		return left->remove(val);
	}

	if(val > value){
		return right->remove(val);
	}
	if (val == value){
		Node<T> *p;
		p = this->parent;
		{
		// Caso 1
			if(this->left == 0 && this->right == 0){
				// Verificar donde borrar
				if(p != 0){
					if(p->left && p->left->value == val){
						p->left = 0;
					}
					else{
						p->right = 0;
					}
					delete this;
					return p;
				}
			}

			// Caso 2 
			if(this->right == 0 && this->left != 0){
				this->left->parent = p;
				if(p->left && p->left->value == val){
					p->left = this->left;
				}
				else{
					p->right = this->left;
				}
				delete this;
				return p;
			}
			// Caso 3
			if(this->left == 0 && this->right != 0){
				this->right->parent = p;
				if(p->left && p->left->value == val){

					p->left = this->right;
				}
				else{
					p->right = this->right;
				}
				delete this;
				return p;
			}
			// Caso 4
			else{
				Node<T> *succ = this->succesor();
				this->value = succ->value;
				return this;
			}
		}
	}
	
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){
		if(x->parent && x->parent->value == root->value){
			if(root->left && root->left->value == x->value){
				rot_right(x->parent);
			}
			else{
				rot_left(x->parent);
			}
		}
		else{
			Node<T> *p, *g;
			p = x->parent;
			g = p->parent;
			if(p->left && g->left 
				&& p->left->value == x->value && g->left->value == p->value){
				rot_right(g);
				rot_right(p);
			}
			else if(p->right && g->right 
				&& p->right->value == x->value && g->right->value == p->value){
				rot_left(g);
				rot_left(p);
			}
			else if(p->left && g->right 
				&& p->left->value == x->value && g->right->value == p->value){
				rot_right(p);
				rot_left(g);
			}
			else{
				rot_left(p);
				rot_right(g);
			}
		}


	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* SplayTree_H_ */
