#ifndef BINARYTREE
#define BINARYTREE

#include <iostream>
#include <math.h>

template <class T>
class BinaryTree {

	struct Node{
		T value;
		struct Node* right;
		struct Node* left;
	};

public:
	BinaryTree();//TODO Turn into AVL
	~BinaryTree();
	void buildTree(std::vector<T>& data);//Assume vector is sorted
	void insert(T val);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	int size();
	bool search(T val);

private:
	struct Node* root;
	int treeSize;
	void buildTree(struct Node** node, std::vector<T>& data, int l, int r);
	void insert(struct Node** node, T val);
	bool search(struct Node* node, T val);
	void printPreOrder(struct Node* node);
	void printInOrder(struct Node* node);
	void printPostOrder(struct Node* node);
	void deleteTree(struct Node* node);
};

template <class T>
BinaryTree<T>::BinaryTree(){
	this->root = NULL;
	this->treeSize = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree(){
	deleteTree(this->root);
}

template <class T>
int BinaryTree<T>::size(){
	return this->treeSize;
} 

template <class T>
void BinaryTree<T>::insert(T val) {
	insert(&(this->root), val);
}

template <class T>
void BinaryTree<T>::insert(struct Node** node, T val){

	if(*node == NULL)	{
		struct Node* tmp = new struct Node;
		tmp->value = val;
		tmp->left=NULL;
		tmp->right = NULL;
		*node = tmp;

		this->treeSize++;
	}else{
		if(val > (*node)->value){
			insert(&(*node)->right, val);
		}else{
			insert(&(*node)->left, val);
		}
	}
}

template <class T>
void BinaryTree<T>::printInOrder(){
	printInOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder(struct Node* node){
	if(node != NULL){
		printInOrder(node->left);
		std::cout << node->value << ", ";
		printInOrder(node->right);
	}
}

template <class T>
void BinaryTree<T>::printPreOrder(){
	printPreOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPreOrder(struct Node* node){
	if(node != NULL)	{
		std::cout << node->value << ", ";
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

template <class T>
void BinaryTree<T>::printPostOrder(){
	printPostOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPostOrder(struct Node* node){
	if(node != NULL){
		printPostOrder(node->left);
		printPostOrder(node->right);
		std::cout << node->value << ", ";
	}
}


template <class T>
void BinaryTree<T>::deleteTree(struct Node* node){
	if(node != NULL){
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

template <class T>
bool BinaryTree<T>::search(T val){
	return search(this->root, val);
}

template <class T>
bool BinaryTree<T>::search(struct Node* node, T val){
	if(node == NULL){
		return false;
	}else{
		if(val == node->value){
			return true;
		}

		if(val > node->value){
			return search(node->right, val);
		}else{
			return search(node->left, val);
		}
	}

}

template <class T>
void BinaryTree<T>::buildTree(std::vector<T>& data) {
	if(data.size() < 0) {
		return;
	}
	buildTree(&(this->root), data, 0, data.size()-1);
}

template <class T>
void BinaryTree<T>::buildTree(struct Node** node, std::vector<T>& data, int l, int r) {
	if(l > r) {
		*node = NULL;
		return;
	}
	int m = (l+r)/2;

	struct Node* tmp = new struct Node;
	tmp->value = data[m];
	buildTree(&(tmp)->left, data, l, m-1);
	buildTree(&(tmp)->right, data, m+1, r);
	*node = tmp;

	this->treeSize++;
}

#endif