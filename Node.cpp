// corresponding Node.cpp file
#include "Node.h"
#include <cstddef>

Node::Node() {
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node::~Node() {
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getParent() {
  return parent;
}

int Node::getValue() {
  return value;
}

void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

void Node::setRight(Node* newRight) {
  right = newRight;
}

void Node::setParent(Node* newParent) {
  parent = newParent;
}

void Node::setValue(int newValue) {
  value = newValue;
}
