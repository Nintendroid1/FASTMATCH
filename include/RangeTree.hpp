#ifndef RANGETREE
#define RANGETREE

#include <iostream>
#include "BinaryTree.hpp"

template <class T>
class RangeTree {

	struct Node{
		T value;
		struct Node* right;
		struct Node* left;
	};

public:
	RangeTree();
	~RangeTree();
	void buildTree(vector<T> data);//Create BST from sorted points, ensuring it's balanced
	void add(T val);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	int size();
	bool lookup(T val);

private:
	struct Node* root;
	int treeSize;
	void add(struct Node** node, T val);
	bool lookup(struct Node* node, T val);
	void printPreOrder(struct Node* node);
	void printInOrder(struct Node* node);
	void printPostOrder(struct Node* node);
	void deleteTree(struct Node* node);
};

template <class T>
RangeTree<T>::RangeTree(){
	this->root = NULL;
	this->treeSize = 0;
}

template <class T>
RangeTree<T>::~RangeTree(){
	deleteTree(this->root);
}

template <class T>
int RangeTree<T>::size(){
	return this->treeSize;
}

template <class T>
void RangeTree<T>::add(T val){
	add(&(this->root), val);
}

template <class T>
void RangeTree<T>::add(struct Node** node, T val){

	if(*node == NULL)	{
		struct Node* tmp = new struct Node;
		tmp->value = val;
		tmp->left=NULL;
		tmp->right = NULL;
		*node = tmp;

		this->treeSize++;
	}else{
		if(val > (*node)->value){
			add(&(*node)->right, val);
		}else{
			add(&(*node)->left, val);
		}
	}
}

template <class T>
void RangeTree<T>::printInOrder(){
	printInOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void RangeTree<T>::printInOrder(struct Node* node){
	if(node != NULL){
		printInOrder(node->left);
		std::cout << node->value << ", ";
		printInOrder(node->right);
	}
}

template <class T>
void RangeTree<T>::printPreOrder(){
	printPreOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void RangeTree<T>::printPreOrder(struct Node* node){
	if(node != NULL)	{
		std::cout << node->value << ", ";
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

template <class T>
void RangeTree<T>::printPostOrder(){
	printPostOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void RangeTree<T>::printPostOrder(struct Node* node){
	if(node != NULL){
		printPostOrder(node->left);
		printPostOrder(node->right);
		std::cout << node->value << ", ";
	}
}


template <class T>
void RangeTree<T>::deleteTree(struct Node* node){
	if(node != NULL){
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

template <class T>
bool RangeTree<T>::lookup(T val){
	return lookup(this->root, val);
}

template <class T>
bool RangeTree<T>::lookup(struct Node* node, T val){
	if(node == NULL){
		return false;
	}else{
		if(val == node->value){
			return true;
		}

		if(val > node->value){
			return lookup(node->right, val);
		}else{
			return lookup(node->left, val);
		}
	}

}

#endif