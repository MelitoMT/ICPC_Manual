#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

 
ll S(ll x) {
    ll s = 0;
    while (x > 0){
        s += x % 10; x /= 10;
    }
    return s;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll p[4];
    for (ll i = 0; i < 4; i++) cin >> p[i];
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> f(4);
    for (ll i = 0; i < 4; i++) f[i].assign(p[i], 0);
 
    for (ll i = 0; i < n; i++){
        ll x, t; cin >> x >> t; t--;
        f[t][S(x) % p[t]]++;
    }
    ll L = 1;
    for (ll i = 0; i < 4; i++) L = lcm(L,p[i]);
    vector<ll> acum(L), m(L), ind(L);
    for (ll d = 0; d < L; d++) {
        acum[d] = 1;
        for (ll t = 0; t < 4; t++) acum[d] *= f[t][d % p[t]];
    }
    m[0] = acum[0]; ind[0] = 0;
    for (ll d = 1; d < L; d++) {
        if (acum[d] > m[d-1]){
            m[d] = acum[d];
            ind[d] = d;
        }
        else{
            m[d] = m[d-1];
            ind[d] = ind[d-1];
        }
    }
    while (q--) {
        ll k; cin >> k;
        ll id = min(k, L) - 1;
        cout << ind[id] << " " << m[id] << "\n";
    }
}