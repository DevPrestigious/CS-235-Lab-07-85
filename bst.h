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
   BST(const BST& rhs) : root(nullptr), numElements(0) { /* *this = &rhs;*/ }                                        //Copy constructor - Missing 2
   BST(      BST && rhs) : root(rhs.root), numElements(rhs.numElements) {rhs.root = nullptr; rhs.numElements = 0;}   //Move Constructor - Missing 1part of 1
   BST(const std::initializer_list<T>& il) : root(nullptr), numElements(0) {*this = il;}                             //Initializer List Constructor
   ~BST() { clear(); }                                                                                               //Deconstructor

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
    // No increase in % yet

    // ATTEMPT #1
    //// Source is Empty
    //if (!rhs.root) {
    //    clear();
    //    return *this;
    //}

    //if (rhs.root) {
    //    this->root->data = rhs.root->data;
    //    this->root->pRight = rhs.root->pRight;
    //    this->root->pLeft = rhs.root->pLeft;
    //}

    //// Setting parent values
    //if (this->root->pRight)
    //    this->root->pRight->pParent = this->root;
    //if (this->root->pLeft)
    //    this->root->pLeft->pParent = this->root; 


    // ATTEMPT #2
    /*if (this != &rhs)
    {
        BST <T> ptr = rhs;
        clear();
        root = ptr.root;
        ptr.root = nullptr;
    }*/

    // ATTEMPT #3
    /*BST.copy-assignment(rhs)
        assign(root, rhs.root)
        numElements = rhs.numElements
    */
    swap(&rhs);
    //numElements = rhs.numElements;

    return *this;
}

/*********************************************
 * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
 * Copy nodes onto a BTree
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (const std::initializer_list<T>& il)
{
    // ATTEMPT #1
    /*if (il.size() == 0)
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
    }*/

    // ATTEMPT #2 -- No % increase yet, but with insert done it might
    /*clear()
     FOREACH t IN rhs
     insert(t)
     RETURN *this
    */
    clear();
    for (T t : il) {
        insert(t);
    }
    
    return *this;
}

/*********************************************
 * BST :: ASSIGN-MOVE OPERATOR - Steve | Finished
 * Move one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (BST <T> && rhs)
{
    clear();
    /*swap(rhs);*/ // Will re-implement when swap is done

    /*root = rhs.root;
    numElements = rhs.numElements;*/

    return *this;
}

/*********************************************
 * BST :: SWAP  - Steve
 * Swap two trees
 ********************************************/
template <typename T>
void BST <T> :: swap (BST <T>& rhs)
{
    // ATTEMPT #1
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
    
    // MAY HAVE TO LOOP THROUGH BNODE ELEMENTS

    // ATTEMPT #2 (adds to %)
    auto tempRoot = rhs.root;
    rhs.root = root;
    root = tempRoot;

    auto tempElements = rhs.numElements;
    rhs.numElements = numElements;
    numElements = tempElements; 
    
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
    /*BST.find(pNode, value)
     IF pNode = NULL
     RETURN end()
     IF pNode.data = value
     RETURN iterator(pNode)
     IF value < pNode.date
     RETURN find(pNode.pLeft)
     ELSE
     RETURN find(pNode.pRight)*/
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
    if(t)
        this.pLeft->data = new BNode(t);
}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> ::BNode::addLeft(T && t)
{
    if (t)
        this.pLeft->data = new BNode(t);
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


