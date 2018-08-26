/////////////////////////////////
//Ex1
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;


vector<double> similarlity(int,int,vector< vector<double> >);

int main(){
  int N,M;
  cin >> N >> M;
  vector<vector<double> > vec;
  vector<double> res;
  vec = vector<vector<double> >(N,vector<double>(M,0));
  //cout << vec.size();
  //cout << vec.front().size();
  for(int i = 0;i < N;i++){
    for(int j = 0;j < M;j++){
      cin >> vec[i][j];
    }
  }
  res = similarlity(N,M,vec);
  for(int i = 0;i < N;i++) cout << res[i] << ' ' ;
  cout << endl;
}

//calculate simularlity
vector<double>  similarlity(int N,int M,vector<vector<double> > vec){
  double sum = 0;
  vector<double> res;
  res = vector<double>(N,0);
  for(int i = 1;i < N;i++){
    for(int j = 0;j < M;j++){
      if(vec[0][j] == -1 || vec[i][j] == -1) continue;
      sum += pow(abs(vec[0][j] - vec[i][j]),2);
      cout << sum << endl;
    }
    res[i] = 1.0 / (sqrt(sum)+1.0);
    sum = 0;
    cout << endl;
  }
  sort(res.rbegin(),res.rend());
  return res;
}
