#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<vector<ll>> formas(3003, vector<ll> (3003,-1));
vector<vector<ll>> acum(3003, vector<ll> (3003,-1));
vector<vector<ll>> adj(3002,vector<ll>(0,{}));

ll mod = 1e9+7;
ll n;
ll calc(ll v, ll x);
ll power(ll a, ll b) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2) res = res * a % mod;
        a = a * a % mod;
        b = b/2;
    }
    return res;
}

ll lagrangeInt(vector<ll>& y, ll d, int n) {
    for(int i = 1; i <= n+1; i++)
        if(d == i) return y[i];
    
	vector<ll> fact(n+2), inv_fact(n+2);
    fact[0] = 1;
    for(int i = 1; i <= n+1; i++) fact[i] = fact[i-1] * i % mod;
    inv_fact[n+1] = power(fact[n+1], mod-2);
    for(int i = n; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % mod;

    vector<ll> pre(n+3), suf(n+3);
    pre[1] = 1;
    for(int i = 2; i <= n+2; i++)
        pre[i] = pre[i-1] * ((d - (i-1) + mod) % mod) % mod;
    suf[n+2] = 1;
    for(int i = n+1; i >= 1; i--)
        suf[i] = suf[i+1] * ((d - i + mod) % mod) % mod;

    ll res = 0;
    for(int i = 1; i <= n+1; i++) {
        ll num = pre[i] * suf[i+1] % mod;
        ll den = inv_fact[i-1] * inv_fact[n+1-i] % mod;
        if((n+1-i) % 2 == 1) den = (mod - den) % mod;
        res = (res + y[i] % mod * num % mod * den) % mod;
    }
    return res;
}


ll calcAcum(ll v, ll x){
    if(x == 0) return 0;
    if(acum[v][x] != -1) return acum[v][x];
    return acum[v][x] = (calcAcum(v, x-1) + calc(v, x)) % mod;
}
 
ll calc(ll v, ll x){
    if(formas[v][x]!=-1)return formas[v][x];
    if(!adj[v].size()) return formas[v][x]=1;
    ll res=1;
    for(auto r: adj[v]){
        res = res * calcAcum(r,x)%mod;
    }
    return formas[v][x]=res;
}


int main(){
    ll d;cin>>n>>d;
    for(int i = 2; i <= n; i++){;
        ll p;cin>>p;
        adj[p].push_back(i);
    }

    vector<ll> y={0};
    ll sumita = 0;
    for(int i = 1; i <= n+1; i++){
        sumita = (sumita + calc(1,i)) % mod;
        y.push_back(sumita);  
    }

    cout<<lagrangeInt(y,d,n)<<"\n";
}