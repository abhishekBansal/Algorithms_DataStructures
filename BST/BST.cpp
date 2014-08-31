/**
* Binary Search Tree and a few related Algorithms
* \author Abhishek Bansal
*/

#include "iostream"
#include "math.h"
#include <memory>

class Node
{
    public:

        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        const int getData() const
        {
            return _data;
        }
        
        void setData(const int data)
        {
            _data = data;
        }

    private:
        int _data;
};


class BinarySearchTree
{
    public:
        void insert(int data);

        // just removing first node found with
        // value as data
        void remove(int data);

        void printInOrder();

        void printPreOrder();

        void printPostOrder();
    
    private:

        void _insertNode(std::shared_ptr<Node>& root, std::shared_ptr<Node>& newNode);

        void _inOrderTraversal(std::shared_ptr<Node>& root);

        void _preOrderTraversal(std::shared_ptr<Node>& root);

        void _postOrderTraversal(std::shared_ptr<Node>& root);

        std::shared_ptr<Node> _root;
};

void
BinarySearchTree::insert(int data)
{
    std::shared_ptr<Node> newNode(new Node());
    newNode->setData(data);
    
    _insertNode(_root, newNode);
}

void
BinarySearchTree::printInOrder()
{
    _inOrderTraversal(_root);
}

void
BinarySearchTree::printPreOrder()
{
    _preOrderTraversal(_root);
}

void
BinarySearchTree::printPostOrder()
{
    _postOrderTraversal(_root);
}


// left -> root -> right
void
BinarySearchTree::_inOrderTraversal(std::shared_ptr<Node>& root)
{
    if(!root.get())
        return;

    _inOrderTraversal(root->left);
    std::cout << root->getData() << std::endl;
    _inOrderTraversal(root->right);
}

// root -> left -> right
void
BinarySearchTree::_preOrderTraversal(std::shared_ptr<Node>& root)
{
    if(!root.get())
        return;

    std::cout << root->getData() << std::endl;
    _preOrderTraversal(root->left);
    _preOrderTraversal(root->right);
}

// left -> right -> root
void
BinarySearchTree::_postOrderTraversal(std::shared_ptr<Node>& root)
{
    if(!root.get())
        return;

    _postOrderTraversal(root->left);
    _postOrderTraversal(root->right);
    std::cout << root->getData() << std::endl;
}

void
BinarySearchTree::_insertNode(std::shared_ptr<Node>& root, std::shared_ptr<Node>& newNode)
{
    // if this node itself is null then it is right place
    if(!root.get())
    {
        root = newNode;
        return;
    }
    else if(root->getData() >= newNode->getData())
    {
        _insertNode(root->left, newNode);
    }
    else
    {
        _insertNode(root->right, newNode);
    }
}

int main()
{
    BinarySearchTree bst;
    
    bst.insert(5);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(7);
    bst.insert(6);
    bst.insert(8);

    std::cout << "inorder Traversal:" << std::endl;
    bst.printInOrder();

    std::cout << "Pre-order Traversal:" << std::endl;
    bst.printPreOrder();

    std::cout << "Post-order Traversal:" << std::endl;
    bst.printPostOrder();

     return 0;
}