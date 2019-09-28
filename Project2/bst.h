/*bst.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{

private:
  struct NODE
  {
    TKey    Key;
    TValue  Value;
    NODE*   Left;
    NODE*   Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " " << cur->Value << endl;
        _inorder(cur->Right);
     }
  }

   //helper function for recursive height() function
   int _height(NODE* rt)
   {
      if (rt == nullptr)
      {
         return -1;
      }

      int leftHeight = _height(rt->Left);
      int rightHeight = _height(rt->Right);
      return 1 + max(leftHeight, rightHeight);
   }

   void _copystructor(NODE* copyNode)
   {
    // 1st iteration: we passed in the pointer to the old BST's root
    // This will be the root of a new BST that will have nodes inserted into it
    
    // check to see if we're at the bottom of the tree
    // (or if the old BST was empty)
    if (copyNode == nullptr)
    {
      return;
    }
    // Make sure this function does its recursive operations by Pre-order
    // Op, Left, Right
    else
    {
      insert(copyNode->Key, copyNode->Value); // Note: insert() should also update new tree's Size
      _copystructor(copyNode->Left);
      _copystructor(copyNode->Right);
    }
   }

public:

  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  binarysearchtree(binarysearchtree& other)
  {
    // initialize new BST fields for Root and Size
    this->Root = nullptr;
    this->Size = 0;
    // go to internal helper function and pass Root of old BST
    _copystructor(other.Root);
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
     return _height(Root);
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else                 // search right:
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 

    //
    // allocate a new node, store key, initialize
    // pointer fields:
    NODE* newNode = new struct NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    
    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //

    //
    // link in the new node, updating Root 
    // pointer as appropriate
    if (prev == nullptr)
    {
      Root = newNode;
    }
    else
    {
       if (key < prev->Key)
       {
         prev->Left = newNode;
       }
       else //if (key > prev->Key)
       {
          prev->Right = newNode;
       }
    }
    // 4. update size and we're done:
    Size++;
  }

  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

};

