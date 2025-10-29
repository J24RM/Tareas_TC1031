#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <queue> 

using namespace std;


template <class T> class BST;

template <class T> 
class TreeNode{
public:
	T value;
	TreeNode<T> *left, *right;
public:
	TreeNode(T);
	void add(T);
	void postorder(std::stringstream &);
	void inorder(std::stringstream &);
	void preorder(std::stringstream &);
	int height();
	bool ancestors(T, std::stringstream &);
	int whatlevelamI(T, int);

};

template <class T>
TreeNode<T>::TreeNode(T val) {
	value = val;
	left = 0;
	right = 0;
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) {
	if(left != NULL){
		left->postorder(aux);
	}

	if(right != NULL){
		right->postorder(aux);
	}

	aux << value << " ";
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) {
	if(left != NULL){
		left->inorder(aux);
	}

	aux << value << " ";

	if(right != NULL){
		right->inorder(aux);
	}

}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) {

	aux << value << " ";

	if(left != NULL){
		left->preorder(aux);
	}

	if(right != NULL){
		right->preorder(aux);
	}

}

template <class T>
void TreeNode<T>::add(T val) {
	// IZQ
	if(val < value){
		if(left != NULL){
			left->add(val);
		}
		else{
			left = new TreeNode<T>(val);
		}
	}

	// DER
	else{
		if(right != NULL){
			right->add(val);
		}
		else{
			right = new TreeNode<T>(val);
		}
		
	}
}

template <class T>
int TreeNode<T>::height() {
	int left_h = 0;
	int right_h = 0;

	if(left != NULL){
		left_h = left->height();
	}

	if(right != NULL){
		right_h = right->height();
	}

	return 1 + std::max(left_h, right_h);
}

template <class T>
bool TreeNode<T>::ancestors(T val, std::stringstream &aux){
	if (val == value){
		return true;
	}
	aux << value << " ";
	if(val < value){
		return(left != 0 && left->ancestors(val, aux));
		}
	else if(val > value){
		return(right != 0 && right->ancestors(val, aux));
		}
	return false;
}

template <class T>
int TreeNode<T>::whatlevelamI(T val, int NV){
	if (val == value){
		return NV;
	}
	if(val < value){
		NV += 1;
		if(left != 0){
			return left->whatlevelamI(val, NV);
		}
	}
	else if(val > value){
		NV += 1;
		if(right != 0){
			return right->whatlevelamI(val, NV);
		}
	}
	return -1;
}



template <class T>
class BST{
private:
	TreeNode<T> *root;

public:
	BST();
	void add(T); 
	string levelByLevel() const;
	string visit();
string preorder() const;
	string inorder() const;
	string postorder() const;
	int height() const;
	string ancestors(T) const;
	int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
void BST<T>::add(T val){
	if (root == NULL){
		root = new TreeNode<T>(val);
	} else {
		root->add(val);
	}
}


template <class T>
string BST<T>::levelByLevel() const {
    stringstream aux;
    if (root == nullptr) {
        return "";
    }

    queue<TreeNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<T> *current = q.front();
        aux << current->value << " ";
        q.pop();
        if (current->left != NULL){
        	q.push(current->left);
        }
        if(current->right != NULL){
        	q.push(current->right);
        }
    }

    string result = aux.str(); 
    if (!result.empty()) {
        	result.pop_back();    
    	}
    return result;
}

template <class T>
string BST<T>::preorder() const {
		stringstream aux;
		if (root != nullptr) {
			root->preorder(aux); 
		}

		string result = aux.str(); 
    	if (!result.empty()) {
        	result.pop_back();    
    	}
    	return result;
	}

template <class T>
string BST<T>::inorder() const {
		stringstream aux;
		if (root != nullptr) {
			root->inorder(aux); 
		}

		string result = aux.str(); 
    	if (!result.empty()) {
        	result.pop_back();    
    	}
    	return result;
	}

template <class T>
string BST<T>::postorder() const {
		stringstream aux;
		if (root != nullptr) {
			root->postorder(aux); 
		}

		string result = aux.str(); 
    	if (!result.empty()) {
        	result.pop_back();    
    	}
    	return result;
	}

template <class T>
string BST<T>::visit() {
	stringstream aux;

	aux << "[" << preorder() << "]\n";

	aux << "[" << inorder() << "]\n";

	aux << "[" << postorder() << "]\n";

	aux << "[" << levelByLevel() << "]"; 

	return aux.str();
}

template <class T>
int BST<T>::height() const {
	if (root == 0){
		return 0;
	}

	else{
		int juan = root->height();
		return juan;
	}
}

template <class T>
string BST<T>::ancestors(T val) const {
	stringstream aux;
	aux << "[";
	bool M = root->ancestors(val, aux);
	if (M){
		string result = aux.str(); 
    	if (!result.empty()) {
       		result.pop_back();    
   		}
   		result += "]";
   		return result;
	}
	return "[]";
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
	int NV = 1;
	return(root->whatlevelamI(val, NV));
}

#endif /* BST_H_ */
