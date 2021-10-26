/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    Our custom implementation of a BST for set and for map
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *    This will contain the class definition of:
 *        BST                 : A class that represents a binary search tree
 * Author
 *    Alexander Dohms, Stephen Costigan 
 ************************************************************************/

#pragma once

#ifdef DEBUG
#define debug(x) x
#else // !DEBUG
#define debug(x)
#endif // !DEBUG

#include <cassert>
#include <utility>
#include <memory>     // for std::allocator
#include <functional> // for std::less
#include <utility>    // for std::pair

namespace custom
{

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <typename T>
class BST
{
public:
   //
   // Construct - Finished | Alexander
   //

   BST() : root(nullptr), numElements(0) {}                                                                          //Default Constructor
   BST(const BST &  rhs) : root(nullptr), numElements(0) { *this = rhs; }                                            //Copy constructor - Missing 2
   BST(      BST && rhs) : root(rhs.root), numElements(rhs.numElements) {rhs.root = nullptr; rhs.numElements = 0;}   //Move Constructor - Missing 1part of 1
   BST(const std::initializer_list<T>& il) : root(nullptr), numElements(0) {*this = il;}                             //Initializer List Constructor
   ~BST() {clear();}                                                                                                 //Deconstructor

   //
   // Assign - Steve
   //

   BST & operator = (const BST &  rhs);
   BST & operator = (      BST && rhs);
   BST & operator = (const std::initializer_list<T>& il);
   void swap(BST & rhs);

   //
   // Access - Shaun
   //

   const T* find(const T& t) const;
   T* find(const T& t);

   // 
   // Insert - Shaun
   //

   bool insert(const T&  t, bool keepUnique = false);
   bool insert(      T&& t, bool keepUnique = false);

   //
   // Remove - Jon
   // 

   void clear() noexcept;
   bool erase(const T& t);
   // 
   // Status
   //

   bool   empty() const noexcept { return numElements == 0; }
   size_t size()  const noexcept { return numElements;   }
   

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   class BNode;
   BNode * root;              // root node of the binary search tree
   size_t numElements;        // number of elements currently in the tree
};


/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree. Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <typename T>
class BST <T> :: BNode
{
public:
   //
   // Construct
   //
    BNode() : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(T()) {}               // Default Constructor
    BNode(const T& t) : pParent(nullptr), pLeft(nullptr), pRight(nullptr), data(t) {}       // Copy Constructor
    BNode(T&& t) : pLeft(nullptr), pRight(nullptr), data(std::move(t)) {}                   // Move Constructor

   //
   // Insert
   //
   void addLeft (BNode * pNode);
   void addRight(BNode * pNode);
   void addLeft (const T &  t);
   void addRight(const T &  t);
   void addLeft(       T && t);
   void addRight(      T && t);

   // 
   // Status
   //
   bool isRightChild(BNode * pNode) const { return true; }
   bool isLeftChild( BNode * pNode) const { return true; }

   //
   // Data
   //
   T data;                  // Actual data stored in the BNode
   BNode* pLeft;          // Left child - smaller
   BNode* pRight;         // Right child - larger
   BNode* pParent;        // Parent
   bool isRed;              // Red-black balancing stuff
};

/*********************************************
 *********************************************
 *********************************************
 ******************** BST ********************
 *********************************************
 *********************************************
 *********************************************/


/*********************************************
 * BST :: ASSIGNMENT OPERATOR
 * Copy one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs)
{
    if (rhs.size() == 0)
    {
        clear();
        return *this;
    }

    /*const int* itRHS = rhs.begin();
    while (itRHS != rhs.end())
    {
        root.insert(*itRHS);
        ++itRHS;
        numElements++;
    }
    root = rhs.root;
    numElements = rhs.numElements;*/
    return *this;
}

/*********************************************
 * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
 * Copy nodes onto a BTree
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (const std::initializer_list<T>& il)
{
    if (il.size() == 0)
    {
        clear();
        return *this;
    }

    const int* itRHS = il.begin();
    while (itRHS != il.end())
    {
        root.insert(* itRHS);
        ++itRHS;
        numElements++;
    }
    
    return *this;
}

/*********************************************
 * BST :: ASSIGN-MOVE OPERATOR
 * Move one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (BST <T> && rhs)
{
    root = rhs.root;
    numElements = rhs.numElements;
    return *this;
}

/*********************************************
 * BST :: SWAP  - Steve
 * Swap two trees
 ********************************************/
template <typename T>
void BST <T> :: swap (BST <T>& rhs)
{
    /*if (rhs.root == nullptr) {
        rhs.root = root = nullptr;
        rhs.numElements = numElements = 0;
        return;
    }

    BST <T> ::BNode* tempRoot = new BST <T> ::BNode();

    rhs.root = root;
    root = tempRoot;
    size_t tempElements = rhs.numElements;
    rhs.numElements = numElements;
    numElements = tempElements;*/
    
    // GOING TO HAVE TO LOOP THROUGH BNODE ELEMENTS

}

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <typename T>
bool BST <T> :: insert(const T & t, bool keepUnique)
{
    return false;
}

template <typename T>
bool BST <T> ::insert(T && t, bool keepUnique)
{
   return false;
}

/****************************************************
 * BST :: FIND
 * Return a pointer to the value if it exists, nullptr otherwise
 ****************************************************/
template <typename T>
const T* BST<T>::find(const T& t) const
{
   return nullptr;
}

/****************************************************
 * BST :: FIND
 * Return a pointer to the value if it exists, nullptr otherwise
 ****************************************************/
template <typename T>
T* BST<T>::find(const T& t)
{
   return nullptr;
}


/*****************************************************
 * BST :: CLEAR
 * Removes all the BNodes from a tree
 ****************************************************/
template <typename T>
void BST <T> ::clear() noexcept
{
    root = nullptr;
    numElements = 0;
}


/*************************************************
 * BST :: ERASE
 * Remove a given node as specified by the value
 ************************************************/
template <typename T>
bool BST <T> ::erase(const T& t)
{
   return true;
}

/******************************************************
 ******************************************************
 ******************************************************
 *********************** B NODE ***********************
 ******************************************************
 ******************************************************
 ******************************************************/
//// Putting this here so we can quickly see what data types we have.
//// Data
////
//T data;                  // Actual data stored in the BNode
//BNode* pLeft;          // Left child - smaller
//BNode* pRight;         // Right child - larger
//BNode* pParent;        // Parent
//bool isRed;              // Red-black balancing stuff
 
/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addLeft (BNode * pNode)
{
    // does not increase % 
   BST <T> ::BNode* pAdd = new BST <T> :: BNode();
   pAdd->pParent = pNode;
   pNode->pLeft = pAdd;
}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addRight (BNode * pNode)
{
    // does not increase %
   BST <T> ::BNode* pAdd = new BST <T> :: BNode();
    pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> :: BNode :: addLeft (const T & t)
{

    pLeft->pLeft->data = t;
}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> ::BNode::addLeft(T && t)
{

}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addRight (const T & t)
{

}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> ::BNode::addRight(T && t)
{

}




} // namespace custom


