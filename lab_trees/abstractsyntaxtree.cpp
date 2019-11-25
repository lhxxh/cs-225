#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    double result=evalhelper(root);
    return result;
}

double AbstractSyntaxTree::evalhelper(Node* node)const {
if(node->left==NULL&&node->right==NULL){
  double x=stod(node->elem);
  return x;
}
  double left=evalhelper(node->left);
  double right=evalhelper(node->right);
  if(node->elem=="*")
  return left*right;
  else if(node->elem=="+")
  return left+right;
  else if(node->elem=="-")
  return left-right;
  else 
  return left/right;
}
