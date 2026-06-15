#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll cross(pll O, pll A, pll B) {
    return (A.first-O.first)*(ll)(B.second-O.second)
         - (A.second-O.second)*(ll)(B.first-O.first);
}

vector<int> convexHull(vector<pll>& pts, vector<int>& idx) {
    int n = idx.size();
    if (n < 3) return {};
    vector<int> order = idx;
    sort(order.begin(), order.end(), [&](int a, int b){
        return pts[a] < pts[b];
    });
    vector<int> hull;
    for (int i : order) {
        while (hull.size() >= 2 && 
               cross(pts[hull[hull.size()-2]], pts[hull.back()], pts[i]) < 0)
            hull.pop_back();
        hull.push_back(i);
    }
    int lower = hull.size() + 1;
    for (int i = (int)order.size()-2; i >= 0; i--) {
        while ((int)hull.size() >= lower && 
               cross(pts[hull[hull.size()-2]], pts[hull.back()], pts[order[i]]) < 0)
            hull.pop_back();
        hull.push_back(order[i]);
    }
    hull.pop_back();
    return hull;
}

// Calcular 2*area del poligono
ll area2(vector<pll>& pts, vector<int>& hull) {
    ll a = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i+1) % n;
        a += pts[hull[i]].first * pts[hull[j]].second;
        a -= pts[hull[j]].first * pts[hull[i]].second;
    }
    return abs(a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pll> pts(n);
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    
    vector<int> remaining(n);
    iota(remaining.begin(), remaining.end(), 0);
    
    int layers = 0;
    while (remaining.size() >= 3) {
        vector<int> hull = convexHull(pts, remaining);
        if (hull.size() < 3) break;
        // Verificar area positiva
        if (area2(pts, hull) == 0) break;
        layers++;
        set<int> hullSet(hull.begin(), hull.end());
        vector<int> next;
        for (int i : remaining)
            if (!hullSet.count(i)) next.push_back(i);
        remaining = next;
    }
    cout << layers << "\n";
}