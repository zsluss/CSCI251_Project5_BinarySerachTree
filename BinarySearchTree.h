
/*
*  	BinarySearchTree.h
*  	Classes TreeNode and BinarySearchTree both represent a binary tree node and binary search tree, respectively
*
* 	@author Zach Slusser
* 	@version 4/4/2026
*/

#ifndef BinarySearchTree_h 
#define BinarySearchTree_h
#include <string>
#include <cmath>
using namespace std;


// ******** class TreeNode template object ************

template <class T>
struct TreeNode;

template <class T>
ostream& operator << (ostream& os, const TreeNode<T>& node);

template <class T>
class BinarySearchTree;

template <class T>
ostream& operator << (ostream& os, const BinarySearchTree<T>& tree);


template <class T>
class TreeNode{
public:
    friend ostream& operator << (ostream& os, const TreeNode<T>& node){
        os << node.data << "(";
        if(node.left != NULL)
            os << *(node.left);
        else os << "_";
        os << ", ";
        if(node.right != NULL)
            os << *(node.right);
        else os <<"_";
        os << ")";
        return os;
    }
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
    T data;
};

// ******** Implement the rest of the help functions are for class TreeNode object ************

template <class T>
bool isLeaf(TreeNode<T>* node){
    if(node == NULL) return false;
    return (node->left == NULL && node->right == NULL);
}

template <class T>
bool isRight(TreeNode<T>* node){
    if(node == NULL || node->parent == NULL) return false;
    return node == node->parent->right;
}

template <class T>
bool isLeft(TreeNode<T>* node){
    if(node == NULL || node->parent == NULL) return false;
    return node == node->parent->left;
}

template <class T>
bool isRoot(TreeNode<T>* node){
    if(node == NULL) return false;
    return node->parent == NULL;
}

template <class T>
int treeHeight(TreeNode<T>* node){
    if(node == NULL) return -1;
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return 1 + max(leftHeight, rightHeight);
}

template <class T>
int treeSize(TreeNode<T>* node){
    if(node == NULL) return 0;
    return 1 + treeSize(node->left) + treeSize(node->right);
}


// ****** Implement all the member (public and private) functions from BinarySearchTree class **********
// ****** All function names explain the purpose of their function *************************************

template <class T> class BinarySearchTree{
	
public:
    friend ostream& operator << (ostream& os, const BinarySearchTree<T>& tree){
        if (tree.root == nullptr) {
            os << "Empty Tree - without nodes";
        }
        else {
            os << *(tree.root);
        }
        
        return os;
    }
	
    BinarySearchTree();
    TreeNode<T>* search(T& data) const;
    void insert(T& data);
    TreeNode<T>* successor(TreeNode<T>* node) const;
    bool remove(T& data);
    bool isEmpty() const;
    int height() const;
    int size() const;
    TreeNode<T>* getRoot() const;
	
private:
    TreeNode<T>* root;
    bool remove(TreeNode<T>* node);
};

template <class T>
void BinarySearchTree<T>::insert(T& data) {
       if (root == nullptr) {
           root = new TreeNode<T>;
           root->data = data;
       }
       else {
           TreeNode<T>* currentNode = root;
           TreeNode<T>* parentNode = nullptr;
       }
}

#endif /* BinarySearchTree_h */
