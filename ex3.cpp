/////////////////////////////////
//Ex3
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>
#include <utility>

using namespace std;


unordered_map<int,double> similarlity(unordered_map<int,int>,unordered_map<int,int>,unordered_map<string,double>);
unordered_map<int,double> recommend(unordered_map<int,int>, unordered_map<int,int>,unordered_map<string,double>,unordered_map<int,double>);
vector< pair<int,double> > map_sort(unordered_map<int,double>);

typedef pair<int,double> P;

//define pair compare
bool pairCompare(const P& firstpair, const P& secondpair){
  return firstpair.second < secondpair.second;
}

int main(){
  int N,M,E,u,b;
  double p;
  cin >> N >> M >> E;


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
cout << "sim" << endl;
  sim = similarlity(user,books,mp);
  cout << "reco" << endl;
  reco = recommend(user,books,mp,sim);
  res = map_sort(reco);
  for(auto r : res) cout << r.first << ',' << r.second << endl;
}

//calculate simularlity
unordered_map<int,double> similarlity(unordered_map<int,int> user,unordered_map<int,int> books,unordered_map<string,double> mp){
  double sum = 0;
  unordered_map<int,double> res;
  for(auto u : user){
    for(auto b : books){
      stringstream ss,ori;
      ss << u.first <<  "," << b.first;
      ori << 1 << "," << b.first;
      if(mp[ori.str()] == 0 || mp[ss.str()] == 0) continue;
      sum += pow(abs(mp[ori.str()] - mp[ss.str()]),2);
    }
    res[u.first] = 1.0 / (sqrt(sum)+1.0);
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
  cout << "sim" << endl;
  for(auto s : sim){
    cout << s.first << ',' << s.second << endl;
  }
  cout << endl;
  for(auto b : books){
    stringstream ori;
    ori << 1 << ',' << b.first;
    if(mp[ori.str()] != 0) continue;
    for(auto u : user){
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
//sort map by value
vector< pair<int,double> > map_sort(unordered_map<int,double> score){
  vector< pair<int,double> > pairs;
  for(auto s : score){
    pairs.push_back(s);
  }
  sort(pairs.rbegin(),pairs.rend(),pairCompare);
  return pairs;
}
