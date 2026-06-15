#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
 
ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
 
ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}
 
vector<ll> divisores(ll m) {
    vector<ll> divs;
    for (ll i = 1; i * i <= m; i++) {
        if (m % i == 0) {
            divs.push_back(i);
            if (i != m / i) divs.push_back(m / i);
        }
    }
    return divs;
}
 
int main() {
    ll n, m, c;
    cin >> n >> m >> c;
 
    vector<ll> divs = divisores(m);
 
    ll ans = 0;
    for (ll d : divs) {
        ll ph = phi(m / d);
        ll exp = (n % (MOD-1)) * (n % (MOD-1)) % (MOD-1) * (d % (MOD-1)) % (MOD-1);
        ll contrib = ph % MOD * power(c, exp) % MOD;
        ans = (ans + contrib) % MOD;
    }
 
    ans = ans % MOD * power(m, MOD - 2) % MOD;
    cout << ans << "\n";
}
 