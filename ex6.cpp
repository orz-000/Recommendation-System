/////////////////////////////////
//Ex6
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include <complex>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>
#include <utility>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Disjointset.h"

using namespace std;

vector< vector<int> > vec;

unordered_map<int,double> similarlity(unordered_map<int,int>,unordered_map<int,int>,unordered_map<string,double>,Disjointset);
unordered_map<int,double> recommend(unordered_map<int,int>, unordered_map<int,int>,unordered_map<string,double>,unordered_map<int,double>);
vector< pair<int,double> > map_sort(unordered_map<int,double>);

typedef pair<int,double> P;

bool pairCompare(const P& firstpair, const P& secondpair){
  return firstpair.second < secondpair.second;
}

int main(){
  int N,M,E,u,b;
  double p;
  cin >> N >> M >> E;

  int R,s,t;

  unordered_map<string, double> mp;
  unordered_map<int,int> user{};
  unordered_map<int,int> books{};
  unordered_map<int,double> sim{},reco{};
  vector< pair<int,double> > res;

  for(int i = 0;i < E;i++){
    cin >> u >> b >> p;
    user[u] = 1;
    books[b] = 1;
    stringstream ss;
    ss << u << ',' << b;
    mp[ss.str()] = p;
  }

  Disjointset uni(N);

  cin >> R;
  for(int i = 0;i < R;i++){
    cin >> s >> t;
    //define s and t are friend
    if(!uni.same(s-1,t-1))uni.unite(s-1,t-1);
  }

  for(auto u : user){
    if(user[u.first] == 0) continue;
    for(auto b : books){
      //a user who are not friend with user 1, delete him from mp
      if(!uni.same(0,u.first-1)){
        stringstream ss;
        ss << u.first << ',' << b.first;
        mp.erase(ss.str());
        user[u.first] = 0;
      }
    }
  }

  sim = similarlity(user,books,mp,uni);
  for(auto s : sim) cout << s.first << ' ' << s.second << endl;
  cout << endl;
  reco = recommend(user,books,mp,sim);
  cout << "score" << endl;
  for(auto s : reco){
      cout << s.first << ' ' << setprecision(9) << s.second << endl;
  }
  res = map_sort(reco);
  for(auto r : res) cout << r.first << ' ' << setprecision(9) << r.second << endl;
}

//calculate similarlity with union find tree
unordered_map<int,double> similarlity(unordered_map<int,int> user,unordered_map<int,int> books,unordered_map<string,double> mp,Disjointset uni){
  for(auto a : mp){
    //cout << "key = " << a.first << ", value = " << a.second << endl;
  }
  double sum = 0;
  unordered_map<int,double> res;
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
  return res;
}

//calculate recommendation
unordered_map<int,double> recommend(unordered_map<int,int> user, unordered_map<int,int> books,unordered_map<string,double> mp,unordered_map<int,double> sim){
  unordered_map<string,double> rec;
  unordered_map<int,double> score;
  double S,A;
  S = A = 0;

  for(auto b : books){
    stringstream ori;
    ori << 1 << ',' << b.first;
    if(mp.find(ori.str()) != mp.end()) continue;
    for(auto u : user){
      if(user[u.first] == 0) continue;
      stringstream ss;
      ss << u.first << ',' << b.first;
      if(mp.find(ss.str()) != mp.end()) A += sim[u.first];
      cout << ss.str() << ' ' << A << endl;
      rec[ss.str()] = mp[ss.str()] * sim[u.first];
      S += rec[ss.str()];
      cout << "rec,S = " << rec[ss.str()] << ',' << S << endl;
    }

    score[b.first] = S / A;
    S = A = 0;
  }
  return score;
}

vector< pair<int,double> > map_sort(unordered_map<int,double> score){
  vector< pair<int,double> > pairs;
  for(auto s : score){
    pairs.push_back(s);
  }
  sort(pairs.rbegin(),pairs.rend(),pairCompare);
  return pairs;
}
