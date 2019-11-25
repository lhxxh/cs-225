/* Your code here! */
#include "dsets.h"
#include <iostream>
void DisjointSets::addelements(int num){
  for(;num>0;num--)
  array.push_back(-1);
}

int DisjointSets::find(int elem){
  if(array[elem]<0){return elem;}
  int root=find(array[elem]);
  array[elem]=root;
  return root;
}

void DisjointSets::setunion(int a,int b){
if(find(a)==find(b))return;
int sizeofa=size(a);
int sizeofb=size(b);
int sizeofaplusb=-sizeofa-sizeofb;
int aroot=find(a);
int broot=find(b);
if(sizeofa<sizeofb){
array[aroot]=broot;
array[broot]=sizeofaplusb;
}
else{
array[broot]=aroot;
array[aroot]=sizeofaplusb;
}

}

int DisjointSets::size(int elem){
int root=find(elem);
return -array[root];
}
