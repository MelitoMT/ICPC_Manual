#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> matrix;
ll mod=1e9+7;
ll n;

void matrixMult(const matrix& m1, const matrix& m2, matrix& res) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            res[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(!m1[i][j]) continue;
            for(int k = 0; k < n; k++)
                res[i][k] = (res[i][k] + m1[i][j] * m2[j][k]) % mod;
        }
}

matrix expBin (matrix m, ll pot){
    matrix res(n, vector<ll>(n,0));
    matrix tmp(n, vector<ll>(n,0));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    while(pot){
        if(pot&1){
            matrixMult(res, m, tmp);
            swap(res, tmp);
        }
        matrixMult(m, m, tmp);
        swap(m, tmp);
        pot >>= 1;
    }
    return res;
}

int main(){
    ll m,k;
    cin>>n>>m>>k;
    matrix res(n, vector<ll>(n,0));
    for(int i=0;i<m;i++){
        ll a,b;
        cin>>a>>b;
        res[a-1][b-1]++;
    }
    cout<<expBin(res,k)[0][n-1]<<"\n";
}