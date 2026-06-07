#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
 
ll cross(pll O, pll A, pll B) {
    return (A.first-O.first)*(B.second-O.second)
         - (A.second-O.second)*(B.first-O.first);
}
 
ll cross2(pll a, pll b) {
    return a.first*b.second - a.second*b.first;
}
 
pll sub(pll a, pll b) { return {a.first-b.first, a.second-b.second}; }
 
bool segmentsIntersect(pll A, pll B, pll C, pll D) {
    ll d1 = cross(C, D, A);
    ll d2 = cross(C, D, B);
    ll d3 = cross(A, B, C);
    ll d4 = cross(A, B, D);
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    return false;
}
 
int windingNumber(pll p, vector<pll>& poly) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        pll a = poly[i], b = poly[(i+1)%n];
        if (a.second <= p.second) {
            if (b.second > p.second) {
                if (cross(a, b, p) > 0) wn++;
            }
        } else {
            if (b.second <= p.second) {
                if (cross(a, b, p) < 0) wn--;
            }
        }
    }
    return wn;
}
 
bool isInside(vector<pll>& inner, vector<pll>& outer) {
    int n = inner.size(), m = outer.size();
    for (auto& p : inner) {
        if (windingNumber(p, outer) == 0) return false;
    }
    for (int i = 0; i < n; i++) {
        pll a = inner[i], b = inner[(i+1)%n];
        for (int j = 0; j < m; j++) {
            pll c = outer[j], d = outer[(j+1)%m];
            if (segmentsIntersect(a, b, c, d)) return false;
        }
    }
    return true;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n; cin >> n;
    vector<vector<pll>> polys(n);
 
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        polys[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> polys[i][j].first >> polys[i][j].second;
    }
 
    vector<bool> conquered(n, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && isInside(polys[i], polys[j]))
                conquered[i] = true;
 
    int survivors = count(conquered.begin(), conquered.end(), false);
    cout << survivors << "\n";
}