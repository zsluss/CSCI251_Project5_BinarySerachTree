
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
    if (node == NULL)
        return -1;
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return 1 + max(leftHeight, rightHeight);
}

template <class T>
int treeSize(TreeNode<T> *node)
{
    if (node == NULL)
        return 0;
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
    // going to keep going through the tree until we find the data or reach a null pointer, if we find the data, we return the node, if we reach a null pointer, we return null
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
        else // if its not less than or equal then it has to go right
        {
            currentNode = currentNode->right;
        }
    }
    return nullptr; // if it can't find the searched number then it returns null
}

template <class T>
void BinarySearchTree<T>::insert(T &data)
{
    //this is in the book but the .cpp doesnt really have a response if this comes back with no data. So maybe I am supose to allow duplicates. 
    if(search(data) != nullptr)
    {
        return; // if the data is already in the tree, we don't insert it again, forgot to add this in my initial run
    }
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
                // checking if the left is open (null), if it is, we insert the new node there, if not we keep traversing left
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
                // checking if the right is open (null), if it is, we insert the new node there, if not we keep traversing right
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

template <class T>
TreeNode<T> *BinarySearchTree<T>::successor(TreeNode<T> *node) const
{
    if (node == nullptr)
        return nullptr;
    // If the node has a right child, the successor is the leftmost node in the right subtree
    if (node->right != nullptr)
    {
        TreeNode<T> *currentNode = node->right;
        while (currentNode->left != nullptr)
        {
            currentNode = currentNode->left;
        }
        return currentNode;
    }
    // If the node does not have a right child, the successor is one of its ancestors
    TreeNode<T> *currentNode = node;
    TreeNode<T> *parentNode = currentNode->parent;
    while (parentNode != nullptr && currentNode == parentNode->right)
    {
        currentNode = parentNode;
        parentNode = parentNode->parent;
    }
    return parentNode; // this will return null if there is no successor (if the node is the largest element in the tree)
}

template <class T>
bool BinarySearchTree<T>::remove(T &data)
{
    TreeNode<T> *parent = nullptr;
    TreeNode<T> *currentNode = root;
    while (currentNode != nullptr)
    {
        // Check if currentNode has an equal data
        if (currentNode->data == data)
        {
            if (currentNode->left == nullptr && currentNode->right == nullptr)
            {
                // Remove leaf

                if (isRoot(currentNode))
                { // Node is root
                    root = nullptr;
                }
                else if (parent->left == currentNode)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
                delete currentNode;
                return true; // Node found and removed
            }
            else if (currentNode->right == nullptr)
            {
                // Remove node with only left child

                if (isRoot(currentNode))
                { // Node is root
                    root = currentNode->left;
                    root->parent = nullptr;
                }
                else if (parent->left == currentNode)
                {
                    parent->left = currentNode->left;
                    currentNode->left->parent = parent;
                }
                else
                {
                    parent->right = currentNode->left;
                    currentNode->left->parent = parent;
                }
                delete currentNode;
                return true; // Node found and removed
            }
            else if (currentNode->left == nullptr)
            {
                // Remove node with only right child

                if (isRoot(currentNode))
                { // Node is root
                    root = currentNode->right;
                    root->parent = nullptr;
                }
                else if (parent->left == currentNode)
                {
                    parent->left = currentNode->right;
                    currentNode->right->parent = parent;
                }
                else
                {
                    parent->right = currentNode->right;
                    currentNode->right->parent = parent;
                }
                delete currentNode;
                return true; // Node found and removed
            }
            else
            {
                // Remove node with two children

                TreeNode<T> *foundSuccessor = successor(currentNode);

                // Copy successor's data to current node
                currentNode->data = foundSuccessor->data;
                parent = currentNode;

                // Reassign currentNode and data so that loop continues with new data
                currentNode = currentNode->right;
                data = foundSuccessor->data;
            }
        }
        else if (currentNode->data < data)
        {
            // Search right
            parent = currentNode;
            currentNode = currentNode->right;
        }
        else
        {
            // Search left
            parent = currentNode;
            currentNode = currentNode->left;
        }
    }
    return false; // Node not found
}

/*
//not ready to work on this
if (root == nullptr)
{
    return false; // Tree is empty, nothing to remove
}

TreeNode<T> *nodeToRemove = search(data);
if (nodeToRemove == nullptr)
{
    return false; // Data not found in the tree
}
if (isRoot(nodeToRemove) && isLeaf(nodeToRemove)) // if the node to remove is the root and a leaf,just set the root to null and delete the node
{
    delete root;
    root = nullptr;
    return true;
}
if(isLeaf(nodeToRemove)) // if the node to remove is a leaf, we can just delete it and set its parent's pointer to null
{
    if (isLeft(nodeToRemove))
    {
        nodeToRemove->parent->left = nullptr;
    }
    else
    {
        nodeToRemove->parent->right = nullptr;
    }
    delete nodeToRemove;
    return true;
}
if(nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) // if the node to remove has two children, we need to find its successor, replace the node's data with the successor's data, and then remove the successor node
{
    TreeNode<T> *successorNode = successor(nodeToRemove);
    //check if succesor left is null then it can just become the node to remove with the same parent and right child
    if(successorNode->left == nullptr)
    {
        successorNode->left = nodeToRemove->left;
        successorNode->parent = nodeToRemove->parent;
        if (isRoot(nodeToRemove))
        {
            root = successorNode;
        }
        else if (isLeft(nodeToRemove))
        {
            nodeToRemove->parent->left = successorNode;
        }
        else
        {
            nodeToRemove->parent->right = successorNode;
        }
        delete nodeToRemove;
        return true;
    }



}
if (nodeToRemove->left != nullptr || nodeToRemove->right != nullptr) // if the node to remove has one child, we need to replace the node with its child
{
    TreeNode<T> *childNode = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;
    if (isRoot(nodeToRemove))
    {
        root = childNode;
    }
    else if (isLeft(nodeToRemove))
    {
        nodeToRemove->parent->left = childNode;
    }
    else
    {
        nodeToRemove->parent->right = childNode;
    }
    childNode->parent = nodeToRemove->parent;
    delete nodeToRemove;
    return true;
}
}

*/

template <class T>
bool BinarySearchTree<T>::isEmpty() const
{
return root == nullptr;
}

template <class T>
int BinarySearchTree<T>::height() const
{
return treeHeight(root);
}

template <class T>
int BinarySearchTree<T>::size() const
{
return treeSize(root);
}


#endif /* BinarySearchTree_h */
