//  ====================== Description ======================
///
/// Name: Ji Hoon Choi
/// SID: 861160400
/// Date: 4/29/15
///
//  =========================================================


// -*- bst.h -*-
#ifndef BST_H
#define BST_H
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <math.h>
using namespace std;
#define nil 0

#define Value int // restore for testing.
//template < typename Value >
class BST 
{
    class Node 
    { // binary tree node
    
    public:
        Node* left;
        Node* right;
        Value value;
        bool selected;
        Node( const Value v = Value() )
        : left(nil), right(nil), value(v), selected(false)
        {}
        Value& content() { return value; }
        bool isInternal() { return left != nil && right != nil; }
        bool isExternal() { return left != nil || right != nil; }
        bool isLeaf() { return left == nil && right == nil; }
        int height() 
        {
            // returns the height of the subtree rooted at this node
            
            int leftHeight = 0;
            int rightHeight = 0;
            int height = 0;
            
            if (this != 0) //don't run if node is null
            {
                if (value != nil)
                {
                    if (left != nil)
                    {
                        //if left node is valid increment height by 1
                        ++leftHeight;
                        //return height of branch and add to this height
                        leftHeight = leftHeight + left->height();
                    }
                    
                    if (right != nil)
                    {
                        //same as left
                        ++rightHeight;
                        rightHeight = rightHeight + right->height();
                    }
                    if (leftHeight >= rightHeight)
                    {
                        //if height of left branch is greater than right branch
                        //then total height = left height
                        //if height of left branch and height of right branch are equal,
                        //then left height takes precedence.
                        height = leftHeight;
                    }
                    else
                    {
                        //if right height is greater than left
                        //then total height = right height
                        height = rightHeight;
                    }
                }
            
            }
            else
            {
                //if node is null then height is 0
                return 0;
            }
            return height;
        }
        int size() 
        {
            int leftSize = 0;
            int rightSize = 0;
            
            //do not run if node is null
            if (this != 0)
            {
                if (value != nil)
                {
                    if (left != nil)
                    {
                        //if left is valid increment size
                        ++leftSize;
                        //add size of left branch to this leftSize
                        leftSize = leftSize + left->size();
                    }
                    
                    if (right != nil)
                    {
                        //same as left
                        ++rightSize;
                        rightSize = rightSize + right->size();
                    }
                }
                //return size of left branch + right branch
                return leftSize + rightSize;
            }
            else
            {
                //null node = size of 0
                return 0;
            }
        }
    }; // Node
    
    
    // const Node* nil; // later nil will point to a sentinel node.
    Node* root;
    int count;
    public:
        int size() 
        {
            // size of the overall tree.
            if (root == 0)
            {
                return 0;
            }
            else
            {
                //call size on root node
                return 1 + root->size();
            }

        }
        
        bool empty() { return size() == 0; }
        void print_node( const Node* n ) 
        {
            // Print the node’s value.
            cout << n->value << ' ';
        }
        
        bool search ( Value x ) 
        {
            // search for a Value in the BST and return true iff it was found.
            return searchFrom (x, root);

        }
        
        void preorder()const 
        {
            // Traverse and print the tree one Value per line in preorder.
            if (root != 0)
            {
                preorderHelper(root);
                cout << endl;
            }
        }
        
        void postorder()const 
        {
            // Traverse and print the tree one Value per line in postorder.
            if (root != 0)
            {
                postorderHelper(root);
                cout << endl;
            }
        }
        
        void inorder()const 
        {
            // Traverse and print the tree one Value per line in inorder.
            if (root != 0)
            {
                inorderHelper(root);
                cout << endl;
            }
        }
        
        Value& operator[] (int n) 
        {
            // returns reference to the value field of the n-th Node.
            int count = 0;
            return nthNodeHelper(root, count, n);
        }
        
        BST() : root(nil), count(0) {}
        void insert( Value X ) { root = insert( X, root ); }
        Node* insert( Value X, Node* T ) 
        {
            // The normal binary-tree insertion procedure ...
            if ( T == nil ) 
            {
                T = new Node( X ); // the only place that T gets updated.
            } 
            else if ( X < T->value ) 
            {
                T->left = insert( X, T->left );
            } 
            else if ( X > T->value ) 
            {
                T->right = insert( X, T->right );
            } 
            else 
            {
                T->value = X;
            }
            // later, rebalancing code will be installed here
            
            return T;
        }
        void remove( Value X ) { root = remove( X, root ); }
        Node* remove( Value X, Node*& T ) 
        {
            // The normal binary-tree removal procedure ...
            // Weiss’s code is faster but way more intricate.
            if ( T != nil ) 
            {
                if ( X > T->value ) 
                {
                    T->right = remove( X, T->right );
                } 
                else if ( X < T->value ) 
                {
                    T->left = remove( X, T->left );
                } 
                else 
                { // X == T->value
                    if ( T->right != nil ) 
                    {
                        Node* x = T->right;
                        while ( x->left != nil ) x = x->left;
                        T->value = x->value; // successor’s value
                        T->right = remove( T->value, T->right );
                    } 
                    else if ( T->left != nil ) 
                    {
                        Node* x = T->left;
                        while ( x->right != nil ) x = x->right;
                        T->value = x->value; // predecessor’s value
                        T->left = remove( T->value, T->left );
                    } 
                    else 
                    { // *T is external
                        delete T;
                        T = nil; // the only updating of T
                    }
                }
            }
            // later, rebalancing code will be installed here
            return T;
        }
        void okay( ) { okay( root ); }
        void okay( Node* T ) 
        {
            // diagnostic code can be installed here
            return;
        }
        
        void minCover()
        {
            if (root != nil)
            {
                //if nodes are already selected deselect them
                deselect(root);
                //run minCoverHelper on nodes that are not root
                minCoverHelper(root->left);
                minCoverHelper(root->right);
                
            }
        }
        
        void displayMinCover()
        {
            if (root != nil)
            {
                int numNodes = 0;
                numNodes = displayMinCoverHelper(root);
                cout << endl << numNodes << endl;
                //deselect nodes after everything is done
                deselect(root);
            }
        }
        
        void findSumPath(Node* n, int sum, int buffer[])
        {
            bool sumFound = false;
            if (n != 0)
            {
                if (n->value != nil)
                {
                    n->selected = true;
                    unsigned a = 0;
                    while (buffer[a] == 0)
                    {
                        if (buffer[a] == 0)
                        {
                            buffer[a] = n->value;
                            break;
                        }
                        ++a;
                    }
                    int valsum = 0;
                    unsigned b = 0;
                    while (buffer[b] != 0)
                    {
                        valsum += buffer[b];
                        ++b;
                    }
                    if (valsum == sum)
                    {
                        sumFound = true;
                    }
                    if (!sumFound && (n->left != nil))
                    {
                        //traverse left if it is valid
                        if (valsum + n->left->value <= sum)
                        {
                            findSumPath(n->left, sum, buffer);
                        }
                    }
                    if (!sumFound && (n->right != nil))
                    {
                        //traverse right if it is valid
                        if (valsum + n->right->value <= sum)
                        {
                            findSumPath(n->right, sum, buffer);
                        }
                    }
                }
                displayMinCover();
                //deselect nodes after everything is done
                deselect(root);
            }
        }
        
    private:
        bool searchFrom (Value x, Node* from)
        {
            bool leftFound = false;
            bool rightFound = false;
            bool found = false;
            
            //don't run if node is null
            if (from != 0)
            {
                if (from->value != nil)
                {
                    if (from->value == x)
                    {
                        //if current node's value is the value we are looking for
                        //then set bool found to true
                        found = true;
                    }
                    //did not find value yet
                    else
                    {
                        if (left != nil)
                        {
                            //if left is valid then search from left node
                            leftFound = searchFrom(x, from->left);
                        }
                        
                        if (right != nil)
                        {
                            //same as left
                            rightFound = searchFrom(x, from->right);
                        }
                        
                        if (leftFound || rightFound)
                        {
                            //if value is found in left or right
                            //then set bool found to true
                            found = true;
                        }
                    }
                }
            }
            //return value of found
            return found;
        }
        
        void deselect(Node* &node)
        {
            if (node != 0)
            {
                if (node->value != nil)
                {
                    //deselect only if node is selected
                    if (node->selected)
                    {
                        node->selected = false;
                    }
                    if (node->left != nil)
                    {
                        //traverse left if it is valid
                        deselect(node->left);
                    }
                    if (node->right != nil)
                    {
                        //traverse right if it is valid
                        deselect(node->right);
                    }
                }
            }
        }
        
        void minCoverHelper(Node* const& node)
        {
            if (node != 0)
            {
                if (node->value != nil)
                {
                    if (node->left != nil)
                    {
                        //if node to left is not selected select current node
                        node->selected = true;
                        //traverse left if it is valid
                        minCoverHelper(node->left);
                    }
                    if (node->right != nil)
                    {
                        //if node to right is not selected select current node
                        node->selected = true;
                        //traverse right if it is valid
                        minCoverHelper(node->right);
                    }
                }
            }
        }
        
        int displayMinCoverHelper(Node* const& node) const
        {
            int coverNodes = 0;
            if (node != 0)
            {
                if (node->value != nil)
                {
                    if (node->left != nil)
                    {
                        //traverse left if it is valid
                        coverNodes += displayMinCoverHelper(node->left);
                    }
                    if (node->selected)
                    {
                        //output value of current node
                        ++coverNodes;
                        cout << node->value << ' ';
                    }
                    if (node->right != nil)
                    {
                        //traverse right if it is valid
                        coverNodes += displayMinCoverHelper(node->right);
                    }
                }
            }
            return coverNodes;
        }
        
        void preorderHelper(Node* const& node) const
        {
            if (node != 0)
            {
                if (node->value != nil)
                {
                    //output value of node
                    cout << node->value << ' ';
                    if (node->left != nil)
                    {
                        //traverse left if it is valid
                        preorderHelper(node->left);
                    }
                    if (node->right != nil)
                    {
                        //traverse right if it is valid
                        preorderHelper(node->right);
                    }
                }
            }
        }
        
        void postorderHelper(Node* const& node) const
        {
            if (node != 0)
            {
                if (node->value != nil)
                {
                    if (node->left != nil)
                    {
                        //traverse left if it is valid
                        postorderHelper(node->left);
                    }
                    if (node->right != nil)
                    {
                        //traverse right if it is valid
                        postorderHelper(node->right);
                    }
                    //output value of current node
                    cout << node->value << ' ';
                }
                
            }
        }
        
        void inorderHelper(Node* const& node) const
        {
            if (node != 0)
            {
                if (node->value != nil)
                {
                    if (node->left != nil)
                    {
                        //traverse left if it is valid
                        inorderHelper(node->left);
                    }
                    //output value of current node
                    cout << node->value << ' ';
                    if (node->right != nil)
                    {
                        //traverse right if it is valid
                        inorderHelper(node->right);
                    }
                }
            }
        }
        Value& nthNodeHelper(Node*& node, int& count, int n)
        {
            //bool found = false;
            Value& val = node->value;
            if (node != 0 && count < n)
            {
                if (node->value != nil)
                {
                    if (node->left != nil)
                    {
                        val = nthNodeHelper(node->left, count, n);
                    }
                    ++count;
                    if (!(count <= n))
                    {
                        if (node->right != nil)
                        {
                            val = nthNodeHelper(node->right, count, n);
                        }
                    }
                }
            }
            return val;
        }
        
}; // BST
#endif