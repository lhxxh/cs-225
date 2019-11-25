/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]<second[curDim])
    return true;
    else if(first[curDim]>second[curDim])
    return false;
    else
    return first<second;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currentdis=0.0,potentialdis=0.0;
     for(int i=0;i<Dim;++i){
       currentdis+=pow(target[i]-currentBest[i],2);
       potentialdis+=pow(target[i]-potential[i],2);
     }
     if(potentialdis<currentdis)
     return true;
     else if(potentialdis>currentdis)
     return false;
     else{return potential<currentBest;}
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     int dimension=0;
     vector<Point<Dim>> myvector=newPoints;

     root=KDtree_helper(myvector,0,newPoints.size()-1,dimension);
     size=newPoints.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   root=nullptr;
   size=0;
   root=copy_(other.root);
   size=other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this!=rhs){
  destroy_(root);
  root=nullptr;
  size=0;
  root=copy_(rhs.root);
  size=rhs.size;
}
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroy_(root);
   root=nullptr;
   size=0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int dimension=0;
    return findsmallerstrec(root,query,dimension);
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDtree_helper(vector<Point<Dim>>& newPoints,int left,int right,int dimension){
  if(newPoints.size()==0){return nullptr;}
  if(left==right){
   KDTreeNode* leafnode=new KDTreeNode(newPoints[left]);
   return leafnode;
}
  if(left>right){return nullptr;}

  int median=(left+right)/2;
  KDTreeNode* newnode=new KDTreeNode(selectmedian(newPoints,left,right,median,dimension%Dim));
  dimension+=1;

  KDTreeNode* leftnode=KDtree_helper(newPoints,left,median-1,dimension);
  KDTreeNode* rightnode=KDtree_helper(newPoints,median+1,right,dimension);
  newnode->left=leftnode;
  newnode->right=rightnode;
  return newnode;
}

template<int Dim>
Point<Dim> KDTree<Dim>::selectmedian(vector<Point<Dim>>& newPoints,int left,int right,int median,int dimension){
  if(left==right)
  return Point<Dim>(newPoints[left]);
  int idx=partition(newPoints,left,right,dimension);
  if(idx==median){return newPoints[idx];}
  else if(idx<median){return selectmedian(newPoints,idx+1,right,median,dimension);}
  else{return selectmedian(newPoints,left,idx-1,median,dimension);}
}

template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints,int left,int right,int dimension){
  Point<Dim> paritionpoint=newPoints[left];
  int storeindex=left;
  iter_swap(newPoints.begin()+left,newPoints.begin()+right);

  for(int i=left;i<right;++i){
    if(smallerDimVal(newPoints[i],paritionpoint,dimension)==true){
    iter_swap(newPoints.begin()+storeindex,newPoints.begin()+i);
    storeindex+=1;
    }
}
iter_swap(newPoints.begin()+right,newPoints.begin()+storeindex);
return storeindex;
}

template<int Dim>
void KDTree<Dim>::destroy_(KDTreeNode* node){
  if(node==nullptr){return;}
  destroy_(node->left);
  destroy_(node->right);
  delete node;
  return;
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy_(const KDTreeNode* node){
  if(node==nullptr)return nullptr;
  KDTreeNode* leftnode=copy_(node->left);
  KDTreeNode* rightnode=copy_(node->right);
  KDTreeNode* newnode=new KDTreeNode(node->point);
  newnode->left=leftnode;
  newnode->right=rightnode;
  return newnode;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findsmallerstrec(KDTreeNode* node,const Point<Dim>& query,int dimension)const{
  if(node->left==nullptr&&node->right==nullptr){
    return node->point;
  }

  Point<Dim> currentbest;
  int hasvisleft=0,hasvisright=0;

  if(smallerDimVal(query,node->point,dimension)==true){
    if(node->left!=nullptr){
    currentbest=findsmallerstrec(node->left,query,(dimension+1)%Dim);
    hasvisleft=1;
  }
  else {
  currentbest=findsmallerstrec(node->right,query,(dimension+1)%Dim);
  hasvisright=1;
   }
  }

  else {
    if(node->right!=nullptr){
    currentbest=findsmallerstrec(node->right,query,(dimension+1)%Dim);
    hasvisright=1;
  }
  else{
    currentbest=findsmallerstrec(node->left,query,(dimension+1)%Dim);
    hasvisleft=1;
  }
  }

  if(shouldReplace(query,currentbest,node->point)==true){currentbest=node->point;}
  double currentdis=twopointdis(currentbest,query);
  double toparitiondis=abs(query[dimension]-node->point[dimension]);
  if(currentdis>=toparitiondis){
    if(hasvisleft==1){
      if(node->right!=nullptr){
     Point<Dim> possiblepoint=findsmallerstrec(node->right,query,(dimension+1)%Dim);
     if(shouldReplace(query,currentbest,possiblepoint)==true){currentbest=possiblepoint;}
   }
    }
    else if(hasvisright==1){
      if(node->left!=nullptr){
    Point<Dim> possiblepoint=findsmallerstrec(node->left,query,(dimension+1)%Dim);
    if(shouldReplace(query,currentbest,possiblepoint)==true){currentbest=possiblepoint;}
  }
    }
   }

  return currentbest;
}

template<int Dim>
double KDTree<Dim>::twopointdis(const Point<Dim>& first,const Point<Dim>& second)const{
  double retval=0.0;
  for(int i=0;i<Dim;++i){
    retval+=pow(first[i]-second[i],2);
  }
  return sqrt(retval);
}
