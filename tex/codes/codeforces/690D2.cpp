#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e6 + 3;
 
ll power(ll a, ll b) {
    ll res = 1; a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return res;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, c;
    cin >> n >> c;

    ll num = 1;
    for (ll i = 1; i <= n + c; i++) num = num * i % MOD;
    
    ll denN = 1;
    for (ll i = 1; i <= n; i++) denN = denN * i % MOD;
    
    ll denC = 1;
    for (ll i = 1; i <= c; i++) denC = denC * i % MOD;
    
    ll binom = num * power(denN, MOD - 2) % MOD * power(denC, MOD - 2) % MOD;
    ll ans = (binom - 1 + MOD) % MOD;
    
    cout << ans << "\n";
}