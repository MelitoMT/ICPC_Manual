#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> matrix;
ll mod=1e9+7;
matrix dice(6,vector<ll>(6,1));
matrix ways={{1},{0},{0},{0},{0},{0}};
 
void create(){
    for(int i=1; i<6; i++){
        for(int j=0;j<6;j++){
            if(j!=i-1){
                dice[i][j]=0;
            }
        }
    }
}
 
matrix matrixMult (matrix m1, matrix m2){
    int sz1 = m1.size();
    int sz2 = m2.size();
    int sz3 = m2[0].size();
    matrix res(sz1, vector<ll>(sz3,0));
    for(int i = 0; i < sz1; i++){
        for(int j = 0; j < sz3; j++){
            for(int k = 0; k < sz2; k++){
                res[i][j]= (res[i][j] + m1[i][k] * m2[k][j])%mod;
            }
        }
    }
    return res;
}
 
matrix expBin (matrix m, ll pot){
    int sz = m.size();
    matrix res(sz, vector<ll>(sz,0));
    for (int i = 0; i < sz; i++) res[i][i] = 1;
    while(pot){
        if(pot&1) res=matrixMult(res,m);
        m = matrixMult(m,m);
        pot >>= 1;
    }
    return res;
}
 
int main(){
    create();
    ll n;cin>>n;
    cout << matrixMult(expBin(dice,n),ways)[0][0] << "\n";
}