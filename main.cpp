#include <iostream>   //I/O
#include <fstream>    //File Input handling
#include <string>     //String convenience

#include "BinarySearchTree.h"	              //Binary Search Tree

//Load a HashDouble from a (.txt) file
BinarySearchTree<int> loadBinarySearchTree(std::string fName) {
  std::ifstream file(fName);
  int num;
  std::cout << "\n\nAttempting to create a binary search tree from table from file " << fName << "...";
  if (file.is_open()) {
    BinarySearchTree<int>* tree = new BinarySearchTree<int>();
    while(file >> num) tree->insert(num); //Load numbers to table.
    file.close();
    return *tree;
  } else return BinarySearchTree<int>();
}

//Main function
int main(int argc, char* argv[])
{
  if (!argv[1]) std::cout << "\nNo file arguments provided. Defaulting to 'data.txt'.";
	std::string fileName = (argv[1]) ? argv[1] : "data.txt"; //File name assignment

	BinarySearchTree<int> tree = loadBinarySearchTree(fileName);


  //Main IO loop - controls interaction Binary Search Tree.
	int choice = 0;
	do {
    std::cout << "\n\n................................................................"
									<< "\nPlease choose one of the following commands:"
									<< "\n1-	Insert"
                  << "\n2-	DeleteMin"
                  << "\n3-	DeleteMax"
                  << "\n4-	Delete"
                  << "\n5-	FindMin"
                  << "\n6-	FindMax"
                  << "\n7-	Preorder"
                  << "\n8-	Inorder"
                  << "\n9-	Postorder"
                  << "\n10-	Exit"
									<< "\n> ";
    std::cin >> choice;
		int num = 0; //Contains I/O responses
    switch(choice) {
      case 1: //Handle Insert
        std::cout << "\nEnter a number to be inserted: \n> ";
				std::cin >> num;
        tree.insert(num);
        break;
      case 2: //Handle DeleteMin
        std::cout << "\nDeleting the minimum value...";
        tree.deleteMin();
        break;
      case 3: //Handle DeleteMax
        std::cout << "\nDeleting the maximum value...";
        tree.deleteMax();
        break;
      case 4: //Handle Delete
        std::cout << "\nEnter a number to be deleted: \n> ";
        std::cin >> num;
        tree.eraseValue(num);
        break;
      case 5: //Handle FindMin
        std::cout << "\nFinding the minimum value...";
        tree.findMin();
        break;
      case 6: //Handle FindMax
        std::cout << "\nFinding the maximum value...";
        tree.findMax();
        break;
      case 7: //Handle Preorder
        std::cout << "\nPre-order traversal:";
        tree.preorder();
        break;
      case 8: //Handle Inorder
        std::cout << "In-order traversal";
        tree.inorder();
        break;
      case 9: //Handle Postorder
        std::cout << "\nPost-order traversal";
        tree.postorder();
        break;
      case 10: break; //Handle Exit
      default:
        std::cout << "\nThat option was not found. Please try again.";
        break;
    }

} while (choice != 10);
  std::cout << "\n\nExiting - dumping tree...\n";
}
