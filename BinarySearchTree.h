
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
ostream &operator<<(ostream &os, const TreeNode<T> &node);

template <class T>
class BinarySearchTree;

template <class T>
ostream &operator<<(ostream &os, const BinarySearchTree<T> &tree);

template <class T>
class TreeNode
{
public:
    friend ostream &operator<<(ostream &os, const TreeNode<T> &node)
    {
        os << node.data << "(";
        if (node.left != NULL)
            os << *(node.left);
        else
            os << "_";
        os << ", ";
        if (node.right != NULL)
            os << *(node.right);
        else
            os << "_";
        os << ")";
        return os;
    }
    TreeNode<T> *parent;
    TreeNode<T> *left;
    TreeNode<T> *right;
    T data;
};

// ******** Implement the rest of the help functions are for class TreeNode object ************

template <class T>
bool isLeaf(TreeNode<T> *node)
{
    if (node == NULL)
        return false;
    return (node->left == NULL && node->right == NULL);
}

template <class T>
bool isRight(TreeNode<T> *node)
{
    if (node == NULL || node->parent == NULL)
        return false;
    return node == node->parent->right;
}

template <class T>
bool isLeft(TreeNode<T> *node)
{
    if (node == NULL || node->parent == NULL)
        return false;
    return node == node->parent->left;
}

template <class T>
bool isRoot(TreeNode<T> *node)
{
    if (node == NULL)
        return false;
    return node->parent == NULL;
}

template <class T>
int treeHeight(TreeNode<T> *node)
{
    //checking if node exists
    if (node == NULL)
        return -1;
    // calculating the height of the left and right subtrees, then returning the maximum of the two heights plus one for the current node
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return 1 + max(leftHeight, rightHeight);
}

template <class T>
int treeSize(TreeNode<T> *node)
{
    //checking if node exists
    if (node == NULL)
        return 0;
    // calculating the size of the left and right subtrees, then returning the sum of the two sizes plus one for the current node
    return 1 + treeSize(node->left) + treeSize(node->right);
}

// ****** Implement all the member (public and private) functions from BinarySearchTree class **********
// ****** All function names explain the purpose of their function *************************************

template <class T>
class BinarySearchTree
{

public:
    friend ostream &operator<<(ostream &os, const BinarySearchTree<T> &tree)
    {
        if (tree.root == nullptr)
        {
            os << "Empty Tree - without nodes";
        }
        else
        {
            os << *(tree.root);
        }

        return os;
    }

    BinarySearchTree();
    TreeNode<T> *search(T &data) const;
    void insert(T &data);
    TreeNode<T> *successor(TreeNode<T> *node) const;
    bool remove(T &data);
    bool isEmpty() const;
    int height() const;
    int size() const;
    TreeNode<T> *getRoot() const;

private:
    TreeNode<T> *root;
    bool remove(TreeNode<T> *node);
};

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::search(T &data) const
{
    TreeNode<T> *currentNode = root;
    //going to keep going through the tree until we find the data or reach a null pointer, if we find the data, we return the node, if we reach a null pointer, we return null
    while (currentNode != nullptr)
    {
        if (data == currentNode->data) // if we find the data, we return the node
        {
            return currentNode;
        }
        else if (data < currentNode->data) // if the data is less than the current node's data, we go left, if not we go right
        {
            currentNode = currentNode->left; 
        }
        else //if its not less than or equal then it has to go right
        {
            currentNode = currentNode->right;
        }
    }
    return nullptr; // if it can't find the searched number then it returns null
}   

template <class T>
void BinarySearchTree<T>::insert(T &data)
{
    // IF the tree is empty, create a new node and set it as the root, had to set the parent to null, and left and right to null
    if (root == nullptr)
    {
        root = new TreeNode<T>;
        root->data = data;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
    }
    else
    {
        TreeNode<T> *currentNode = root;
        TreeNode<T> *parentNode = nullptr;
        // Looking through the tree to find the correct position for the new node, the while loop will continue until we find an open spot (null) to insert the new node
        while (currentNode != nullptr)
        {
            parentNode = currentNode;
            // checking to see if the data is less than the current node's data, if it is, we go left, if not we go right
            if (data < currentNode->data)
            {
                //checking if the left is open (null), if it is, we insert the new node there, if not we keep traversing left
                if (currentNode->left == nullptr)
                {
                    currentNode->left = new TreeNode<T>;
                    currentNode->left->data = data;
                    currentNode->left->parent = currentNode;
                    currentNode->left->left = nullptr;
                    currentNode->left->right = nullptr;
                    return;
                }
                // if the left is not open, we keep going until we find an open spot
                currentNode = currentNode->left;
            }
            else
            {
                //checking if the right is open (null), if it is, we insert the new node there, if not we keep traversing right
                if (currentNode->right == nullptr)
                {
                    currentNode->right = new TreeNode<T>;
                    currentNode->right->data = data;
                    currentNode->right->parent = currentNode;
                    currentNode->right->left = nullptr;
                    currentNode->right->right = nullptr;
                    return;
                }
                // if the right is not open, we keep going until we find an open spot
                currentNode = currentNode->right;
            }
        }
    }
}



#endif /* BinarySearchTree_h */
