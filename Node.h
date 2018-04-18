// Node.h file
#ifndef NODE_H
#define NODE_H

class Node {

 public:

  ~Node();
  Node();
  
  // getters
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  int getValue();

  // setters
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  void setValue(int);

 private:
  Node* left;
  Node* right;
  Node* parent;
  int value;
};

#endif
