#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll power(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod; b >>= 1;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    int N = 2*n;
    vector<ll> fact(N+1), inv_fact(N+1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++){
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[N] = power(fact[N], MOD-2, MOD);
    for (int i = N-1; i >= 0; i--){
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
    ll binom = fact[2*n] % MOD * inv_fact[n] % MOD * inv_fact[n] % MOD;
    ll ans = binom * power(n+1, MOD-2, MOD) % MOD;
    cout << ans << "\n";
}