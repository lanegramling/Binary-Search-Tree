#ifndef BINARY_NODE
#define BINARY_NODE


template <class T>
class BinaryNode {

public:

  //Constructor
  BinaryNode(T value=T(), BinaryNode<T>* leftChild=nullptr, BinaryNode<T>* rightChild=nullptr);

  //Set the value of this BinaryNode.
  void setValue(T value);

  //Get the value of this BinaryNode.
  T getValue();

  //Set the pointer to the Left child.
  void setLeftChildPtr(BinaryNode<T>* leftPtr);

  //Set the pointer to the Right child.
  void setRightChildPtr(BinaryNode<T>* rightPtr);

  //Get the pointer to the Left child.
  BinaryNode<T>* getLeftChildPtr();

  //Get the pointer to the Right child.
  BinaryNode<T>* getRightChildPtr();

  //Determine whether this BinaryNode is a leaf, for convenience.
  bool isLeaf();


private:

  T m_value;  //Value stored in this BinaryNode

  BinaryNode<T>* m_leftChild;       //Left Child Pointer
  BinaryNode<T>* m_rightChild;      //Right Child Pointer




};

#include "BinaryNode.hpp"

#endif
