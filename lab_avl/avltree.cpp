/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* rotatepoint=t->right;
    Node* temp=t;
    temp->right=rotatepoint->left;
    rotatepoint->left=temp;
    t=rotatepoint;

    rotatepoint->height=updateHeight(rotatepoint);
    temp->height=updateHeight(temp);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp=t;
    Node* rotatepoint=t->left;
    temp->left=rotatepoint->right;
    rotatepoint->right=temp;
    t=rotatepoint;

    rotatepoint->height=updateHeight(rotatepoint);
    temp->height=updateHeight(temp);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==nullptr){return;}
    Node* left=subtree->left;
    Node* right=subtree->right;
    int leftheight,rightheight;
    if(left!=nullptr){leftheight=left->height;}else{leftheight=-1;}
    if(right!=nullptr){rightheight=right->height;}else{rightheight=-1;}
    int balancefactor=rightheight-leftheight;
    if(balancefactor<=1&&balancefactor>=-1){subtree->height=updateHeight(subtree);return;}
    else if(balancefactor>1){
      Node* right_right=right->right;
      Node* right_left=right->left;
      int right_right_height,right_left_height;
      if(right_right!=nullptr){right_right_height=right_right->height;}else{right_right_height=-1;}
      if(right_left!=nullptr){right_left_height=right_left->height;}else{right_left_height=-1;}
      int rightbalancefactor=right_right_height-right_left_height;
      if(rightbalancefactor==1){rotateLeft(subtree);}
      else if(rightbalancefactor==-1){rotateRightLeft(subtree);}
    }
    else if(balancefactor<-1){
      Node* left_left=left->left;
      Node* left_right=left->right;
      int left_left_height,left_right_height;
      if(left_left!=nullptr){left_left_height=left_left->height;}else{left_left_height=-1;}
      if(left_right!=nullptr){left_right_height=left_right->height;}else{left_right_height=-1;}
      int leftbalancefactor=left_right_height-left_left_height;
      if(leftbalancefactor==1){rotateLeftRight(subtree);}
      else if(leftbalancefactor==-1){rotateRight(subtree);}
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==nullptr){
      Node* newNode=new Node(key,value);
      subtree=newNode;
      return;
    }

    if(key==subtree->key){std::cout << "invalid input" << '\n';return;}
    else if(key>subtree->key){insert(subtree->right,key,value);}
    else if(key<subtree->key){insert(subtree->left,key,value);}
    rebalance(subtree);
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree=nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node*& iop=findIOP(subtree->left);
            swap(iop,subtree);
            remove(subtree->left,iop->key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right!=nullptr){Node* temp=subtree;subtree=subtree->right;delete temp;}
            else if(subtree->left!=nullptr){Node* temp=subtree;subtree=subtree->left;delete temp;}
        }
        // your code here
    }
       rebalance(subtree);
}

template <class K,class V>
int AVLTree<K,V>::updateHeight(Node* node){
  if(node==nullptr)
  return -1;

  return 1+max(updateHeight(node->right),updateHeight(node->left));
}

template<class K,class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::findIOP(Node*& node){
  if(node->right==nullptr)
  {return node;}

  return findIOP(node->right);
}
