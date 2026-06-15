#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcdExt(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0; 
        return a;
    }
    ll x1, y1;
    ll g = gcdExt(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

pair<ll,ll> crt(ll a1, ll m1, ll a2, ll m2) {
    ll p, q;
    ll g = gcdExt(m1, m2, p, q); 
    if ((a2 - a1) % g != 0) return {-1, -1};
    ll lcm = m1 / g * m2;
    ll x = (a1 + m1 * ((a2 - a1) / g % (m2/g) * p % (m2/g))) % lcm;
    if (x < 0) x += lcm;
    return {x, lcm};
}

ll crtComb(vector<vector<int>> &cong){
    ll x=cong[0][0], mod = cong[0][1];
    for(int i=1;i<cong.size();i++){
        auto [x_t, mod_t] = crt(x,mod,cong[i][0], cong[i][1]);
        if(x_t==-1)return -1;
        x=x_t;
        mod=mod_t;
    }
    return x;
}

int main(){
    int t;cin>>t;
    for(int j=1;j<=t;j++){
        int n;cin>>n;
        vector<vector<int>> cong(n, vector<int>(2));
        for(int i=0;i<n;i++){
            cin>>cong[i][1]>>cong[i][0];
        }
        cout << "Case "<<j<<": "<<crtComb(cong)<<"\n";
    }
}