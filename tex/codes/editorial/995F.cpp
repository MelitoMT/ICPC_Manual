#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<vector<ll>> formas(3003, vector<ll> (3003,0));
vector<vector<ll>> acum(3003, vector<ll> (3003,0));
vector<vector<ll>> adj(3002,vector<ll>(0,{}));
vector<int> order;
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

void topito(){
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int v = q.front(); q.pop();
        order.push_back(v);
        for(auto c : adj[v]) q.push(c);
    }
    reverse(order.begin(), order.end());
}

int main(){
    ll d;cin>>n>>d;
    for(int i = 2; i <= n; i++){;
        ll p;cin>>p;
        adj[p].push_back(i);
    }
    
    topito();

    for(auto v :order){
        for(int x = 1; x <= n+1; x++){
            if(!adj[v].size()){
                formas[v][x]= 1;
            } else {
                ll res = 1;
                for(auto c : adj[v])
                    res = res * acum[c][x] % mod;
                formas[v][x] = res;
            }
            acum[v][x] = (acum[v][x-1] + formas[v][x]) % mod;
        }
    }

    vector<ll> y={0};
    ll sumita = 0;
    for(int i = 1; i <= n+1; i++){
        sumita = (sumita + formas[1][i]) % mod;
        y.push_back(sumita);  
    }

    cout<<lagrangeInt(y,d,n)<<"\n";
}