/////////////////////////////////
//Ex2
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
vector<double> recommend(int,int,vector< vector<double> >,vector<double>);

int main(){
  int N,M;
  cin >> N >> M;
  vector<vector<double> > vec;
  vector<double> sim,reco;
  vec = vector<vector<double> >(N,vector<double>(M,0));
  //cout << vec.size();
  //cout << vec.front().size();
  for(int i = 0;i < N;i++){
    for(int j = 0;j < M;j++){
      cin >> vec[i][j];
    }
  }
  sim = similarlity(N,M,vec);
  reco = recommend(N,M,vec,sim);
  for(int i = 0;i < M;i++) cout << reco[i] << ' ' ;
  cout << endl;
}
//calculate simulality
vector<double> similarlity(int N,int M,vector<vector<double> > vec){
  double sum = 0;
  vector<double> res;
  res = vector<double>(N,0);
  for(int i = 1;i < N;i++){
    for(int j = 0;j < M;j++){
      if(vec[0][j] == -1 || vec[i][j] == -1) continue;
      sum += pow(abs(vec[0][j] - vec[i][j]),2);
    }
    res[i] = 1.0 / (sqrt(sum)+1.0);
    sum = 0;
  }
  //sort(res.rbegin(),res.rend());
  return res;
}

//calculate recommendation
vector<double> recommend(int N, int M,vector< vector<double> > vec,vector<double> sim){
  vector< vector<double> > rec;
  rec = vector< vector<double> >(N,vector<double>(M,0));
  vector<double> score;
  score = vector<double>(M,0);
  double S,A;
  S = A = 0;

  for(int j = 0;j < M;j++){
    if(vec[0][j] != -1) continue;
    for(int i = 1;i < N;i++){
      if(vec[i][j] != -1) A += sim[i];
      if(vec[i][j] == -1) vec[i][j] = 0;
      rec[i][j] = vec[i][j] * sim[i];
      S += rec[i][j];
    }

    score[j] = S / A;
    S = A = 0;
  }
  return score;
}
