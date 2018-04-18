/*
 * main.cpp
 * Author: Aryan Gupta
 * Date: 3/23/18
 * This program takes in an integer from user input and places it into a binary search tree and allows the user to
 * remove a node or print the whole tree.
 */

#include "Node.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

// function prototypes

// adds node to tree
void add(Node* &head, int value);

// removes a node from the tree
Node* deleteNode(Node* root, int value);

// prints the tree
void print(Node* head, int distance);

// finds smallest node
Node* smallestNode(Node* head);

int main() {

  //intro
  cout << "To create a binary search tree from the console..." << endl;
  cout << "Type INSERT to put an integer (from 1-1000 inclusive) in the tree." << endl;
  cout << "Type REMOVE to remove a particular number from the tree." << endl;
  cout << "Type PRINT to see a visual representation of the current tree." << endl;
  cout << "Type QUIT to terminate the program." << endl;
  cout << "------------------------------------------------------------------" << endl;
  cout << "To create a binary search tree from a file..." << endl;
  cout << "Just type FILE to create a tree from a file." << endl;
  cout << "\n";
  cout << "\n";

  // program terminate 'checker'
  bool quit = false;

  Node* head = NULL;
  
  while(quit == false) {

    //Node* head = NULL;
    
    // stores what user wants to do with the BST
    char option[10];

    // ask user what the want to do
    cout << "What would you like to do (FILE, INSERT, REMOVE, PRINT, QUIT): ";
    cin.getline(option, 10);

    // if the user wants to use a file
    if(strcmp(option, "FILE") == 0) {
      ifstream inFile;
      char input[500];
      
      
      char file[100];
      cout << "Enter the name of the file: ";
      cin.getline(file, 100);
      inFile.open(file);
      if(!inFile) {
	cout << "File does not exist." << endl;
	//return 0;
      }
      else {
	inFile.getline(input, 1000);
	
	int values[100];
	int count = 0;
	// split input by spaces
	char* split;
	split = strtok(input, " ");
	while(split != NULL) {
	  values[count] = atoi(split);
	  count++;
	  split = strtok(NULL, " ");
	} 
	// now adds all the values to the tree
	for(int i = 0; i < count; i++) {
	  add(head, values[i]);
	}
	cout << "Numbers are in the tree." << endl;
      }
    } // if(strcmp(option, "FILE") == 0) '}'
    // if the user wants to insert a number
    if(strcmp(option, "INSERT") == 0) {
      
      // valid input 'checker'
      bool validInput = false;
      
      while(validInput == false) {
	// number from user input
	int numInput;
	
	// prompt user for input
	cout << "Enter a number (from 1-1000 inclusive) you want inserted: ";
	cin >> numInput;
	
	// check if they entered a valid type or number
	if(cin.fail()) {
	  cout << "Invalid input type, please enter an integer." << endl;
	  cin.clear();
	  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if(numInput < 1 || numInput > 1000) {
	  cout << "The number you entered is outside the specified range (1-1000 inclusive). Try again." << endl;
	}
	// otherwise
	else {
	  // insert the number into the tree here
	  add(head, numInput);
	  validInput = true;
	}
      } // while(validInput == false) '}'
    } // if(strcmp(option, "INSERT") == 0) '}'
    // if the user wants to remove a number from the tree
    else if(strcmp(option, "REMOVE") == 0) {

      // valid input 'checker'
      bool validInput = false;
      
      while(validInput == false) {
	// number the user wants to remove
	int numInput;
	
	// prompt user for input
	cout << "Enter the number you want to remove that exists in the tree: ";
	cin >> numInput;
	
	// check if the user entered a valid number
	if(cin.fail()) {
	  cout << "Invalid input type, please enter an integer." << endl;
	  cin.clear();
	  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	// otherwise
	else {
	  // remove the number from the tree here
	  deleteNode(head, numInput);
	  validInput = true;
	}
      }
    } // else if(strcmp(option, "REMOVE") == 0) '}'
    // if the user wants to print the tree
    else if(strcmp(option, "PRINT") == 0) {
      cout << "Printing the tree." << endl;
      print(head, 0);
    } // else if(strcmp(option. "PRINT") == 0) '}'
    // if the user wants to terminate the program
    else if(strcmp(option, "QUIT") == 0) {
      cout << "Terminating program." << endl;
      quit = true;
    }
    // the user entered an invalid command
    else {
      cout << "Invalid command try again." << endl;
    }
  } // while(quit == false) '}'

  // return 0;
} // int main() '}'


// functions

// add node to tree
void add(Node* &head, int value) {
  // if there is only 1 node
  if(head == NULL) {
    // give it a value
    head = new Node();
    head->setValue(value);
    return;
  }
  // if the value is larger than the root go right
  if(value > head->getValue()) {
    if(head->getRight() != NULL) {
      // recursively add node if there is one to the right
      Node* next = head->getRight();
      add(next, value);
    }
    else {
      // if there is no node, add a node
      Node* temp = new Node();
      temp->setValue(value);
      head->setRight(temp);
      return;
    }
  }
  // otherwise if the value is smaller than root go left
  else {
    if(head->getLeft() != NULL) {
      // recursively add node if there is one to left
      Node* next = head->getLeft();
      add(next, value);
    }
    else {
      // if there is no node, add a node
      Node* temp = new Node();
      temp->setValue(value);
      head->setLeft(temp);
      return;
    }
  }
} // void add(Node* head, int value) '}'

// delete a node from the tree
Node* deleteNode(Node* root, int value) {
  if(root == NULL) {
    return root;
  }
  if(value < root->getValue()) {
    root->setLeft(deleteNode(root->getLeft(), value));
  }
  else if(value > root->getValue()) {
    root->setRight(deleteNode(root->getRight(), value));
  }
  else {
    if(root->getLeft() == NULL) {
      Node* temp = root->getRight();
      free(root);
      return temp;
    }
    else if(root->getRight() == NULL) {
      Node* temp = root->getLeft();
      free(root);
      return temp;
    }
    Node* temp = smallestNode(root->getRight());
    root->setValue(temp->getValue());
    root->setRight(deleteNode(root->getRight(), temp->getValue()));
  }
  return root;
} // Node* deleteNode(Node* head, int value) '}'

// prints the tree
void print(Node* head, int distance) {
  if(head == NULL) {
    return;
    distance += 10;
    print(head->getRight(), distance);
    cout << "\n";
    for(int i = 10; i < distance; i++) {
      cout << " ";
      cout << head->getValue();
      print(head->getLeft(), distance);
    }
  }
}


// finds the smallest node in tree
Node* smallestNode(Node* head) {
  Node* current = head;
  // go all the way left
  while(current->getLeft() != NULL) {
    current = current->getLeft();
  }
  return current;
}
