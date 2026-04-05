
/*
*  CSCI251ProjFive.cpp
*  CSCI251ProjFive. This is an interactive file designed for Binary Search Trees
*
*	Add the following data nodes one-by-one to a binary search tree, then print out the tree
* 	65, 23, 45, 76, 54, 55, 98, 86
*
* 	@author Mike Mireku Kwakye
* 	@version March 28, 2026
*/

#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

void menu(){
    cout << "********************\n";
    cout << "*      MENU        *\n";
    cout << "* 1. Add a node    *\n";
    cout << "* 2. Remove a node *\n";
    cout << "* 3. Search a data *\n";
    cout << "* 4. Tree property *\n";
    cout << "* 5. Quit          *\n";
    cout << "********************\n";
}

int main(){
	
    int data;
    int choice;
    BinarySearchTree<int> tree;
    
    do{
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
		
        switch(choice){
			
            case 1:
                cout << "Enter an integer data that you will add to tree: ";
                cin >> data;
                tree.insert(data);
                cout << "The tree is: " << tree << endl;
                break;
				
            case 2:
                cout << "Enter an integer data that you will remove from tree: ";
                cin >> data;;
                if(tree.remove(data))
                    cout << "Remove operation successfully done. Now the tree is: " << tree << endl;
                else
                    cout << "No such data in tree\n";
                break;
				
            case 3:
                cout<< "Enter the integer data that you want to search for: \n";
                cin >> data;
                if(tree.search(data) == NULL)
                    cout << "No such data in tree\n";
                else
                    cout << "The tree is: " << tree << ". Data found in tree\n";
                break;
				
            case 4:
                if(tree.isEmpty())
                    cout << "Tree is empty\n" ;
                else{
                    cout << "The tree is: " << tree <<  "." << endl;
                    cout << "Tree size: " << tree.size() << endl;
                    cout << "Tree height: " << tree.height() << endl ;
                }
                break;
				
            case 5:
                cout << "Make sure you run enough test before you turn it in\n";
                break;
				
            default:
                cout << "Wrong option. Please choose from menu\n";
                break;
				
        }
		
    }while(choice != 5);
    
}
