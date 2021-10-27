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
   BST(const BST& rhs) : numElements(0), root(nullptr) { *this = rhs; }                                              //Copy constructor 
   BST(      BST && rhs) : root(rhs.root), numElements(rhs.numElements) {rhs.root = nullptr; rhs.numElements = 0;}   //Move Constructor
   BST(const std::initializer_list<T>& il) : root(nullptr), numElements(0) {*this = il;}                             //Initializer List Constructor
   ~BST() { 
       clear(); 
   }                                                                                               //Deconstructor

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

   void assign(BNode* pDest, const BNode* pSrc);
   void clear(BNode * pThis);
   // 
   // Status
   //
   bool isRightChild(BNode* pNode) const { return pNode->data > pNode->pParent->data; } // DON'T KNOW IF IT CHANGES ANYTHING
   bool isLeftChild (BNode* pNode) const { return pNode->data < pNode->pParent->data; } // <-/

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
 *******************       *******************
 *******************  BST  *******************
 *******************       *******************
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
    /* if (!rhs.root) { // Source is Empty
        clear();
        return *this;
    }
    if (rhs.root) {
        this->root->data = rhs.root->data;
        this->root->pRight = rhs.root->pRight;
        this->root->pLeft = rhs.root->pLeft;
    
    }
    // Setting parent values
    if (this->root->pRight)
        this->root->pRight->pParent = this->root;
    if (this->root->pLeft)
        this->root->pLeft->pParent = this->root; */


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

    root->assign(root, rhs.root);
    numElements = rhs.numElements;

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
        insert(t); // WILL PROB INCREASE % WHEN INSERT IS DONE
    }
    
    return *this;
}

/*********************************************
 * BST :: ASSIGN-MOVE OPERATOR - Steve | Finished?
 * Move one tree to another
 ********************************************/
template <typename T>
BST <T> & BST <T> :: operator = (BST <T> && rhs)
{
    root->clear(root);
    if (rhs.root != nullptr)
        swap(rhs);


    return *this;
}

/*********************************************
 * BST :: SWAP  - Steve | Finished
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
   // I'm calling on BNode's functions improperly here, but I don't know how to fix it.
   
   /*if (root == nullptr)
   {
      return;
   }

   clear(BNode->pLeft);
   clear(BNode->pRight);
   delete root;
   root = nullptr;*/
}


/*************************************************
 * BST :: ERASE
 * Remove a given node as specified by the value
 ************************************************/
template <typename T>
bool BST <T> ::erase(const T& t)
{
    // CALL ON FIND(T), DELETE AT ITERATOR POINT
   return true;
}

/******************************************************
 ******************************************************
 **********************          **********************
 **********************  B NODE  **********************
 **********************          **********************
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
    if (pNode)
        pParent = pNode->pParent;
    pLeft = pNode->pLeft;
}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> :: BNode :: addRight (BNode * pNode)
{
    // does not increase %
    if (pNode)
        pParent = pNode->pParent;
    pRight = pNode->pRight;
}

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <typename T>
void BST<T> :: BNode :: addLeft (const T & t)
{
    // does not increase %
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
    // does not increase %
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
    // does not increase %
    if (t)
        this.pRight->data = new BNode(t);
}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <typename T>
void BST <T> ::BNode::addRight(T && t)
{
    // does not increase %
    if (t)
        this.pRight->data = new BNode(t);
}




 // namespace custom
/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <typename T>
void BST<T> ::BNode::assign(BST<T> ::BNode * pDest, const BST<T> ::BNode * pSrc)
{

   // Source is Empty
   if (!pSrc) {
      clear(pDest);
      return;
   }

   // Neither the Source nor Destination are Empty
   if (pDest && pSrc) {
      pDest->data = pSrc->data;
      assign(pDest->pRight, pSrc->pRight);
      assign(pDest->pLeft, pSrc->pLeft);
   }

   // Destination is Empty
   if (!pDest && pSrc) {
      pDest = new BST::BNode(pSrc->data);
      assign(pDest->pRight, pSrc->pRight);
      assign(pDest->pLeft, pSrc->pLeft);
   }

   // Setting parent values
   if (pDest->pRight)
      pDest->pRight->pParent = pDest;
   if (pDest->pLeft)
      pDest->pLeft->pParent = pDest;
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void BST<T>::BNode::clear(BNode * pThis)
{
   if (!pThis)
      return;

   clear(pThis->pLeft);
   clear(pThis->pRight);
   pThis = NULL;
}
}