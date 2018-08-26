/////////////////////////////////
//Ex5
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include <iostream>
#include <vector>
using namespace std;
class Disjointset {
public:
  Disjointset();
  Disjointset(int );
  void makeset(int );
  bool same(int ,int );
  void unite(int ,int );
  void link(int ,int);
  int findset(int);
  vector<int> get_p(void);
private:
    vector<int> p,rank;
};
