/////////////////////////////////
//Ex5
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include "Disjointset.h"
//define union-find tree class

Disjointset::Disjointset(){};
Disjointset::Disjointset(int size){
  rank.resize(size, 0);
  p.resize(size, 0);
  for(int i = 0;i < size;i++) makeset(i);
}

void Disjointset::makeset(int x){
  p[x] = x; //p[x] is parent of x
  rank[x] = 0; //height of x's tree
}
//if x is belong same group with y, return True, else return False
bool Disjointset::same(int x, int y){
  return findset(x) == findset(y);
}
//define x and y's parent are same
void Disjointset::unite(int x,int y){
  link(findset(x),findset(y));
}
//belong x in y's group
void Disjointset::link(int x,int y){
  if(rank[x] > rank[y]){
    p[y] = x;
  }
  else {
    p[x] = y;
    if(rank[x] == rank[y]){
      rank[y]++;
    }
  }
}
//find x's parent
int Disjointset::findset(int x){
  if(x != p[x]){
    p[x] = findset(p[x]);
  }
  return p[x];
}
