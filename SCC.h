//Ex11 declare scc class
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
#include <vector>
using namespace std;

class SCC {
private:
  const int n;
  vector< vector<int> > path;
  vector< vector<int> > rpath;
  vector<int> vs;
  vector<bool> used;
  vector<int> cmp;
public:
  SCC(int);
  void addEdge(int,int);
  void dfs(int);
  void rdfs(int,int);
  int scc();
  bool same(int,int);
  void show_path();
};
