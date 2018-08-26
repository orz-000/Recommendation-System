//Ex10 and Ex11
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
#include <boost/python.hpp>
#include <complex>
#include <algorithm>
#include <string>
#include <sstream>
#include <utility>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Disjointset.h"
#include "SCC.h"
#include <map>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
using namespace std;

typedef pair<int,double> P;

map<string, double> mp{};
map<int,int> user{};
map<int,int> books{};
map<int,double> sim{},reco{}; // result od similarlity and recommend
vector< pair<int,double> > res;
int N,M;

void input_init(int n,int m){
  N = n;
  M = m;
}
//get union find
Disjointset get_uni(){
  Disjointset uni(N);
  return uni;
}

void input_phase1(int u,int b,float p){
  user[u] = 1;
  books[b] = 1;
  stringstream ss;
  ss << u << ',' << b;
  mp[ss.str()] = p;
}
//input data into union find tree
Disjointset input_relation(int s,int t, Disjointset uni){
  cout << "s,t = " << s << ',' << t << endl;
  if(!uni.same(s-1,t-1))uni.unite(s-1,t-1);
  return uni;
}
//erase user who are not friend with user 1 from mp
void uni_init(Disjointset uni){
  for(auto u : user){
    if(user[u.first] == 0) continue;
    for(auto b : books){
      if(!uni.same(0,u.first-1)){
        stringstream ss;
        vector<int> parents;
        ss << u.first << ',' << b.first;
        mp.erase(ss.str());
        user[u.first] = 0;
      }
    }
  }
}
//class of union find
Disjointset::Disjointset(){};
Disjointset::Disjointset(int size){
  Disjointset::rank.resize(size, 0);
  Disjointset::p.resize(size, 0);
  for(int i = 0;i < size;i++) Disjointset::makeset(i);
}

void Disjointset::makeset(int x){
  Disjointset::p[x] = x; //p[x] is parent of x
  Disjointset::rank[x] = 0; //height of x's tree
}

bool Disjointset::same(int x, int y){
  return Disjointset::findset(x) == Disjointset::findset(y);
}

void Disjointset::unite(int x,int y){
  Disjointset::link(Disjointset::findset(x),Disjointset::findset(y));
}

void Disjointset::link(int x,int y){
  if(Disjointset::rank[x] > Disjointset::rank[y]){
    Disjointset::p[y] = x;
  }
  else {
    Disjointset::p[x] = y;
    if(Disjointset::rank[x] == Disjointset::rank[y]){
      Disjointset::rank[y]++;
    }
  }
}
int Disjointset::findset(int x){
  if(x != Disjointset::p[x]){
    Disjointset::p[x] = Disjointset::findset(p[x]);
  }
  return Disjointset::p[x];
}
vector<int> Disjointset::get_p(void){
  return Disjointset::p;
}
//calculate similarlity with union find
void similarlity_uni(Disjointset uni){
  //cout << "similarlity" << endl;
  //for(auto a : mp){
    //cout << "key = " << a.first << ", value = " << a.second << endl;
  //}

  double sum = 0;
  map<int,double> res;
  for(auto u : user){
    if(user[u.first] == 0) continue;
    if(u.first == 1){
      res[u.first] = 1;
      continue;
    }
    if(!uni.same(0,u.first-1)){
      res[u.first] = 0;
      continue;
    }
    for(auto b : books){
      stringstream ss,ori;
      ss << u.first <<  "," << b.first;
      ori << 1 << "," << b.first;
      if(mp.find(ori.str()) == mp.end() || mp.find(ss.str()) == mp.end()) continue;
      sum += pow(fabs(mp[ori.str()] - mp[ss.str()]),2);
    }
    if(sum != 0) res[u.first] = 1.0 / (sqrt(sum)+1.0);
    else res[u.first] = 0;
    sum = 0;
  }
  sim = res;
}
//calculate similarlity
void similarlity(){
  double sum = 0;
  map<int,double> res;
  for(auto u : user){
    for(auto b : books){
      stringstream ss,ori;
      ss << u.first <<  "," << b.first;
      ori << 1 << "," << b.first;
      if(mp[ori.str()] == 0 || mp[ss.str()] == 0) continue;
      sum += pow(fabs(mp[ori.str()] - mp[ss.str()]),2);
    }
    if(sum != 0) res[u.first] = 1.0 / (sqrt(sum)+1.0);
    else res[u.first] = 0;
    sum = 0;
  }
  sim = res;
}
//calculate similarlity with scc
void similarlity_scc(SCC scc){
  scc.show_path();
  double sum = 0;
  map<int,double> res;
  for(auto u : user){
    cout << "u = " << u.first << endl;
    if(user[u.first] == 0) continue;
    if(u.first == 1){
      res[u.first] = 1;
      continue;
    }
    cout << "same = " << scc.same(1,u.first) << endl;
    if(scc.same(1,u.first) == 0){
      cout << "same = " << u.first << endl;
      res[u.first] = 0;
      continue;
    }
    for(auto b : books){
      cout << "b = " << b.first << endl;
      stringstream ss,ori;
      ss << u.first <<  "," << b.first;
      ori << 1 << "," << b.first;
      if(mp.find(ori.str()) == mp.end() || mp.find(ss.str()) == mp.end()) continue;
      sum += pow(fabs(mp[ori.str()] - mp[ss.str()]),2);
    }
    if(sum != 0) res[u.first] = 1.0 / (sqrt(sum)+1.0);
    else res[u.first] = 0;
    sum = 0;
  }
  sim = res;
}
//calculate recommendation
map<int,double> recommend(){
  map<string,double> rec;
  double S,A;
  map<int,double> score;
  S = A = 0;

  for(auto b : books){
    stringstream ori;
    ori << 1 << ',' << b.first;
    if(mp[ori.str()] != 0) continue;
    for(auto u : user){
      if(user[u.first] == 0) continue;
      stringstream ss;
      ss << u.first << ',' << b.first;
      if(mp[ss.str()] != 0) A += sim[u.first];
      rec[ss.str()] = mp[ss.str()] * sim[u.first];
      S += rec[ss.str()];
    }
    score[b.first] = S / A;
    S = A = 0;
  }
  return score;
}

bool pairCompare(const P& firstpair, const P& secondpair){
  return firstpair.second < secondpair.second;
}

vector< pair<int,double> > map_sort(map<int,double> score){
  vector< pair<int,double> > pairs;
  for(auto s : score){
    pairs.push_back(s);
  }
  sort(pairs.rbegin(),pairs.rend(),pairCompare);
  return pairs;
}

void show(vector< pair<int,double> > res){
  for(auto r : res) cout << r.first << ' ' << setprecision(9) << r.second << endl;
}

//get scc
SCC get_scc(int e){
  SCC scc(N+e);
  return scc;
}
//input data into scc
SCC input_graph(int s,int t, SCC scc){
  scc.addEdge(s,t);
  return scc;
}
//define class of SCC
SCC::SCC(int _n) : n(_n), path(_n), rpath(_n), used(_n), cmp(_n) {}
//add edge into graph
void SCC::addEdge(int from, int to) {
  cout << "from,to = " << from << ',' << to << endl;
  path[from].emplace_back(to);
  rpath[to].emplace_back(from);
}
//execute dfs
void SCC::dfs(int v) {
  used[v] = true;
  for (auto&& nxt : path[v]) {
    if (!used[nxt]) dfs(nxt);
  }
  vs.emplace_back(v);
}
//execute reverse dfs
void SCC::rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  for (auto&& nxt : rpath[v]) {
    if (!used[nxt]) rdfs(nxt, k);
  }
  vs.emplace_back(v);
}
//execute strong connected component
int SCC::scc() {
  for(int v = 0;v < n;v++){
    if (!used[v]) dfs(v);
  }
  used.assign(n, false);
  int k = 0;
  for (int i = vs.size() - 1; i >= 0; i--) {
    int v = vs[i];
    if (!used[v]) rdfs(v, k++);
  }
  return k;
}
// if a are belong in same scc with b, return True.else return false
bool SCC::same(int a, int b) {
  return cmp[a] == cmp[b];
}
void SCC::show_path(){
  for(int i = 0;i < path.size();i++){
    cout << "from = " << i << endl;
    for(int j = 0;j < path[i].size();j++){
      cout << "to = " << path[i][j] << endl;
    }
  }
}

//wrapper of c++ module using boost python
BOOST_PYTHON_MODULE(phase1_func){
  using namespace boost::python;
  def( "similarlity",similarlity);
  def( "similarlity_uni", similarlity_uni);
  def( "similarlity_scc", similarlity_scc);
  def( "recommend",recommend);
  def( "map_sort",map_sort);
  def( "input_init",input_init);
  def( "input_phase1",input_phase1);
  def( "input_relation",input_relation);
  def( "uni_init",uni_init);
  def( "show",show);
  def( "get_uni",get_uni);
  def( "input_graph",input_graph);
  def( "get_scc",get_scc);
  boost::python::class_<SCC>("SCC", boost::python::init<int>())
  .def(boost::python::init<int>())
  .def("SCC",&SCC::addEdge)
  .def("SCC",&SCC::dfs)
  .def("SCC",&SCC::rdfs)
  .def("SCC",&SCC::scc)
  .def("SCC",&SCC::same)
  .def("SCC",&SCC::show_path);
  boost::python::class_<Disjointset>("Disjointset", boost::python::init<int>())
  .def(boost::python::init<int>())
  .def("Disjointset",&Disjointset::makeset)
  .def("Disjointset",&Disjointset::same)
  .def("Disjointset",&Disjointset::unite)
  .def("Disjointset",&Disjointset::link)
  .def("Disjointset",&Disjointset::findset)
  .def("Disjointset",&Disjointset::get_p);
  class_<map<int,int> >("map<int,int>")
  .def(map_indexing_suite<map<int,int> >());
  class_<map<int,double> >("map<int,double>")
  .def(map_indexing_suite<map<int,double> >());
  class_<std::pair<int, double> >("pair<int,double>")
  .def_readwrite("first", &std::pair<int, double>::first)
  .def_readwrite("second", &std::pair<int, double>::second);
  class_<vector< pair<int,double> >>("vector<int>")
  .def(vector_indexing_suite<vector< pair<int,double> > >());

}
