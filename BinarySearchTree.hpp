

#include "BinarySearchTree.h"


//Constructor - initializes a root node to nullptr.
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{ m_root = new BinaryNode<T>(); }

//Destructor - Destroys the tree at the root
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{ destroyTree(m_root); }

//Destroy a subtree
template <class T>
void BinarySearchTree<T>::destroyTree(BinaryNode<T>* subtree){
    if (subtree) {
        destroyTree(subtree->getLeftChildPtr());
        destroyTree(subtree->getRightChildPtr());
        delete subtree;
    }
}

//Insert a given value to the tree
template <class T>
void BinarySearchTree<T>::insert(T value, BinaryNode<T>* subtree) {
  if (!m_root->getValue()) { m_root->setValue(value); std::cout << "\n" << value << " inserted to tree."; return; } //Case - Initial insertion
  if (!subtree) subtree = m_root; //Start traversing at the root when subtree's default value nullptr is observed.

  //Recursive logic - this particular approach is taken to allow usage of a default parameter for the subtree pointer
  if (value < subtree->getValue()) {
    if (subtree->getLeftChildPtr()) insert(value, subtree->getLeftChildPtr()); //Recurse
    else {                                                                     //Set
        subtree->setLeftChildPtr(new BinaryNode<T>(value));
        std::cout << "\n" << value << " inserted to tree.";
    }
  } else {
    if (subtree->getRightChildPtr()) insert(value, subtree->getRightChildPtr()); //Recurse
    else {                                                                       //Set
        subtree->setRightChildPtr(new BinaryNode<T>(value));
        std::cout << "\n" << value << " inserted to tree.";
    }
  }
}

//Entry to erase() for convenience
template <class T>
void BinarySearchTree<T>::eraseValue(T value) { erase(value, m_root); }

//Find a value to delete, and arbitrate deletion.
template <class T>
void BinarySearchTree<T>::erase(T value, BinaryNode<T>* subtree) {
    if (subtree) {                                          //Recursive search of children
        if (subtree == m_root && value == m_root->getValue()) m_root = eraseNode(subtree); //Root deletion case - no parents to worry about.
        BinaryNode<T>* left = (subtree->getLeftChildPtr()) ? subtree->getLeftChildPtr() : nullptr;
        BinaryNode<T>* right = (subtree->getRightChildPtr()) ? subtree->getRightChildPtr() : nullptr;
        if (left) if (value == left->getValue()) subtree->setLeftChildPtr(eraseNode(left));
        if (right) if (value == right->getValue()) subtree->setRightChildPtr(eraseNode(right));
        if (value < subtree->getValue()) erase(value, left); else erase(value, right); //Continue search for parent
    }
}

//Delete a Node from the tree. Given the Node to delete. Returns the Node to replace it if existent, otherwise nullptr
template <class T>
BinaryNode<T>* BinarySearchTree<T>::eraseNode(BinaryNode<T>* subtree) {
    if (subtree == nullptr) return nullptr;

    //Determine children of node to delete.
    BinaryNode<T>* left = (subtree->getLeftChildPtr());
    BinaryNode<T>* right = (subtree->getRightChildPtr());

    if (subtree->isLeaf()) { //Leaf case
        delete subtree;
        subtree = nullptr;
        return subtree;
    } else if ((left || right) && !(left && right)){  //One child case
        BinaryNode<T>* child = (left) ? left : right; //Save the one child
        delete subtree;
        subtree = nullptr;
        return child;
    } else {                                          //Two children case
        BinaryNode<T>* temp = deleteMin(right, false);
        subtree->setRightChildPtr(temp);
        subtree->setValue(temp->getValue());
        return subtree;
    }

}

//Delete the minimum value from the tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::deleteMin(BinaryNode<T>* subtree, bool verbose) {
  if (!subtree) { if (m_root == nullptr){ std::cout << "\nTree empty."; return nullptr; } else subtree = m_root; } //Default to root
  if (subtree->getLeftChildPtr()) while (subtree->getLeftChildPtr()->getLeftChildPtr()) subtree = subtree->getLeftChildPtr();
  if (verbose) std::cout << "\nDeleted minimum value " << subtree->getLeftChildPtr()->getValue() << " from tree.";
  BinaryNode<T>* min = eraseNode(subtree->getLeftChildPtr());
  subtree->setLeftChildPtr(min); //Destroy Node and set replacement node.
  return min;
}

//Delete the maximum value from the tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::deleteMax(BinaryNode<T>* subtree, bool verbose) {
  if (!subtree) { if (m_root == nullptr){ std::cout << "\nTree empty."; return nullptr; } else subtree = m_root; } //Default to root
  if (subtree->getRightChildPtr()) while (subtree->getRightChildPtr()->getRightChildPtr()) subtree = subtree->getRightChildPtr();
  if (verbose) std::cout << "\nDeleted maximum value " << subtree->getRightChildPtr()->getValue() << " from the tree.";
  BinaryNode<T>* max = eraseNode(subtree->getRightChildPtr());
  subtree->setRightChildPtr(max); //Destroy Node and set replacement node.
  return max;
}


//Find the minimum value in the tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMin(BinaryNode<T>* subtree, bool verbose) {
  if (!subtree) subtree = m_root; //Default to root
  while (subtree->getLeftChildPtr()) subtree = subtree->getLeftChildPtr();
  if (verbose) std::cout << "\nFound minimum value " << subtree->getValue() << " in the tree.";
  return subtree;
}

//Find the maximum value in the tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMax(BinaryNode<T>* subtree, bool verbose) {
  if (!subtree) subtree = m_root; //Default to root
  while (subtree->getRightChildPtr()) subtree = subtree->getRightChildPtr();
  if (verbose) std::cout << "\nFound maximum value " << subtree->getValue() << " in the tree.";
  return subtree;
}

//Print out all elements using preorder.
template <class T>
void BinarySearchTree<T>::preorder(BinaryNode<T>* subtree) {
    if (!subtree) {
        if (m_root) {subtree = m_root; std::cout << "\npre-order: "; } //Entry case
        else {std::cout << "\nTree empty. "; return;}
    }

    std::cout << subtree->getValue() << " ";
    if (subtree->getLeftChildPtr()) preorder(subtree->getLeftChildPtr());
    if (subtree->getRightChildPtr()) preorder(subtree->getRightChildPtr());
}

//Print out all elements using inorder.
template <class T>
void BinarySearchTree<T>::inorder(BinaryNode<T>* subtree) {
    if (!subtree) {
        if (m_root) {subtree = m_root; std::cout << "\nin-order: "; } //Entry case
        else {std::cout << "\nTree empty. "; return;}
    }

    if (subtree->getLeftChildPtr()) preorder(subtree->getLeftChildPtr());
    std::cout << subtree->getValue() << " ";
    if (subtree->getRightChildPtr()) preorder(subtree->getRightChildPtr());
}

//Print out all elements using postorder.
template <class T>
void BinarySearchTree<T>::postorder(BinaryNode<T>* subtree) {
    if (!subtree) {
        if (m_root) {subtree = m_root; std::cout << "\npost-order: "; } //Entry case
        else {std::cout << "\nTree empty. "; return;}
    }


    if (subtree->getLeftChildPtr()) preorder(subtree->getLeftChildPtr());
    if (subtree->getRightChildPtr()) preorder(subtree->getRightChildPtr());
    std::cout << subtree->getValue() << " ";
}
