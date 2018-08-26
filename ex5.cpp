/////////////////////////////////
//Ex5
//ID: s1240148
//Name: Shigeki Kobayashi
//Date: 07/25/2018
/////////////////////////////////
#include "Disjointset.h"

vector< vector<int> > vec;

int main(){

  int R,N,Q,s,t,p,q;

  cin >> N >> R;
  //declare Disjointset
  Disjointset uni(N);
  cout << vec.size();


  for(int i = 0;i < R;i++){
    cin >> s >> t;
    //we define s is t's friend
    if(!uni.same(s-1,t-1))uni.unite(s-1,t-1);
  }

  cin >> Q;
  for(int i = 0;i < Q;i++){
    cin >> p >> q;
    if(uni.same(p-1,q-1)) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
