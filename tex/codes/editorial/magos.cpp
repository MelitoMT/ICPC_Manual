#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll MOD = 998244353;
 
int n, m;
int w[9];       
int r[9][11];      
 
vector<vector<pii>> particiones;
 
void genParticiones(int fila, vector<pii>& actual) {
    if (fila > n) {
        particiones.push_back(actual);
        return;
    }
    actual.push_back({fila, 1});
    genParticiones(fila + 1, actual);
    actual.pop_back();
    if (fila + 1 <= n) {
        actual.push_back({fila, 2});
        genParticiones(fila + 2, actual);
        actual.pop_back();
    }
}
 
int getMago(int perm, int f) {
    for (int i = 1; i < f; i++) perm /= 10;
    return perm % 10;
}
 
int swapF(int perm, int f) {
    int mf = getMago(perm, f);
    int mf1 = getMago(perm, f + 1);
    int factor_f = 1;
    for (int i = 1; i < f; i++) factor_f *= 10;
    int factor_f1 = factor_f * 10;
    perm -= mf * factor_f;
    perm -= mf1 * factor_f1;
    perm += mf1 * factor_f;
    perm += mf * factor_f1;
    return perm;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> r[i][j];
 
    vector<pii> tmp;
    genParticiones(1, tmp);
    int permInit = 0;
    int factor = 1;
    for (int i = 1; i <= n; i++) {
        permInit += i * factor;
        factor *= 10;
    }
    map<int, ll> dp;
    dp[permInit] = 1;
    for (int j = 1; j <= m; j++) {
        map<int, ll> ndp;
        for (auto& [perm, cnt] : dp) {
            for (auto& part : particiones) {
                bool valida = true;
                int nperm = perm;
                for (auto& [f, sz] : part) {
                    if (sz == 1) {
                        int mago = getMago(perm, f);
                        if (r[f][j] > w[mago]){
                            valida = false;
                            break;
                        }
                    } else {
                        int m1 = getMago(perm, f);
                        int m2 = getMago(perm, f + 1);
                        int criatura = max(r[f][j], r[f+1][j]);
                        if (criatura > min(w[m1], w[m2])) {
                            valida = false;
                            break;
                        }
                        nperm = swapF(nperm, f);
                    }
                }
                if (valida) {
                    ndp[nperm] = (ndp[nperm] + cnt) % MOD;
                }
            }
        }
        dp = ndp;
    }
 
    ll ans = 0;
    for (auto& [perm, cnt] : dp) ans = (ans + cnt) % MOD;
    cout << ans << "\n";
}
 