/* Your code here! */
#ifndef DisjointSets_h_
#define DisjointSets_h_
#include <vector>
using namespace std;

class DisjointSets{
public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a,int b);
    int size(int elem);
private:
    vector<int> array;
};

#endif
