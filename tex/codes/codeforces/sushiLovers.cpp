#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

pii crt(vector<pii> &cong){
    ll tmpr=0,tmpd=0;
    bool comp=true;
    for(auto [r,d]: cong){
    }
    for(auto [r,d]: cong){
        if(tmpd<=d){
            tmpr=r;
            tmpd=d;
        }
    }
    for(auto [r,d]: cong){
        if(tmpr % d != r) comp=false;
    }
    return (comp ? pii{tmpr,tmpd} : pii{-1,-1});
}
 
int main() {
    ll k, m, q;cin >> k >> m >> q;
    vector<pii> chef;
    for (int i = 0; i < k; i++){
        ll r,d;cin>>r>>d;
        chef.push_back(pii{r,d});
    }
    for (auto [a,b]:chef){
    }
    map<ll, vector<ll>> rollos;
    for (int i = 0; i < m; i++) {
        int n; cin >> n;
        vector<pii> cong(n);
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            cong[j] = chef[c-1];
        }
        auto [t, L] = crt(cong);
        if (t == -1) continue;
        rollos[L].push_back(t);
    }
    for (auto& [L, times] : rollos){
        sort(times.begin(), times.end());
    }
 
    for (int i = 0; i < q; i++) {
        ll h, l; cin >> h >> l;
        ll suma = 0;
        for (auto& [L, times] : rollos) {
            if (l >= L) {
                suma += times.size();
            }
            else{
                ll hl = h % L;
                ll hr = (h + l) % L;
                if (hl <= hr) {
                    suma += upper_bound(times.begin(), times.end(), hr)
                                - lower_bound(times.begin(), times.end(), hl);
                } else {
                    suma += times.end() - lower_bound(times.begin(), times.end(), hl)
                        + upper_bound(times.begin(), times.end(), hr) - times.begin();
                }
            }
        }
        cout << suma << "\n";
    }
}