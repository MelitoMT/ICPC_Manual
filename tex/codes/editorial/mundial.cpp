#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vll;
const ll MOD = 998244353;
const ll PRIM = 3;
 
ll power(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod; b >>= 1;
    }
    return res;
}
 
void ntt(vl& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = inv ? power(PRIM, MOD-1-(MOD-1)/len, MOD)
                          : power(PRIM, (MOD-1)/len, MOD);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len/2; j++) {
                ll u = a[i+j], v = a[i+j+len/2] * wn % MOD;
                a[i+j]       = (u+v) % MOD;
                a[i+j+len/2] = (u-v+MOD) % MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (inv) {
        ll ni = power(n, MOD-2, MOD);
        for (auto& x : a) x = x * ni % MOD;
    }
}
 
vl multiply(vl a, vl b) {
    int result_size = a.size() + b.size() - 1;
    int n = 1;
    while (n < result_size) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(result_size);
    return a;
}
 
vl multPair(vll& polys) {
    if (polys.empty()) return {1};
    if (polys.size() == 1) return polys[0];
    auto cmp = [](const vl& a, const vl& b){
        return a.size() > b.size();  
    };
    priority_queue<vl,vll,decltype(cmp)> pq(cmp);
 
    for (auto& p : polys) pq.push(p);
    while (pq.size() > 1) {
        auto a = pq.top(); pq.pop();
        auto b = pq.top(); pq.pop();
        pq.push(multiply(a, b));
    }
    return pq.top();
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll m,t; cin >> m >> t;
    vll sem(m);
    ll total = 1;  
    for (int i = 0; i < m; i++) {
        ll t;cin >> t;
        sem[i].assign(t, 1);
        total = total % MOD * t % MOD;
    }
    vl prod = multPair(sem);
    ll suma = 0;
    for (ll k = 0; k <= t && k < prod.size(); k++)
        suma = (suma + prod[k]) % MOD;
    ll ans = (total - suma % MOD + MOD) % MOD;
    cout << ans << "\n";
}