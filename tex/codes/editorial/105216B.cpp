#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cross(pair<ll,ll> o, pair<ll,ll> a, pair<ll,ll> b) {
    return (a.first-o.first)*(b.second-o.second) - (a.second-o.second)*(b.first-o.first);
}

vector<pair<ll,ll>> convexHull(vector<pair<ll,ll>> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    int n = pts.size();
    if (n <= 2) return pts;
    vector<pair<ll,ll>> hull;
    for (auto& p : pts) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    int lower = hull.size()+1;
    for (int i = n-2; i >= 0; i--) {
        while ((int)hull.size() >= lower && cross(hull[hull.size()-2], hull.back(), pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    hull.pop_back();
    return hull;
}

ll divNeg(ll a, ll b) {
    ll q = a / b, r = a % b;
    if (r != 0 && ((r < 0) != (b < 0))) q--;
    return q;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, N; cin >> P >> N;
    vector<pair<ll,ll>> raw(P);
    for (auto& p : raw) cin >> p.first >> p.second;

    vector<pair<ll,ll>> poly = convexHull(raw);
    P = poly.size();

    int m = N - 1;
    const int MAXX = 5001;

    if (m > 5000) {
        cout << 0 << "\n";
        return 0;
    }

    ll area2 = 0;
    for (int i = 0; i < P; i++) {
        auto& a = poly[i]; auto& b = poly[(i+1)%P];
        area2 += a.first*b.second - b.first*a.second;
    }
    bool ccw = area2 > 0;

    vector<ll> yLo(MAXX), yHi(MAXX);
    vector<bool> has(MAXX, false);

    for (ll x = 0; x <= 5000; x++) {
        ll lo = -1e9, hi = 1e9;
        bool valid = true;
        for (int i = 0; i < P; i++) {
            ll x1=poly[i].first, y1=poly[i].second;
            ll x2=poly[(i+1)%P].first, y2=poly[(i+1)%P].second;
            ll dx = x2-x1, dy = y2-y1;
            if (dx == 0) {
                if (x1 != x) {
                    ll s = -dy*(x-x1);
                    if (ccw && s < 0) valid = false;
                    if (!ccw && s > 0) valid = false;
                }
                continue;
            }
            ll num = dy*(x-x1);
            ll yfloor = y1 + divNeg(num, dx);
            ll yceil = (num % dx == 0) ? yfloor : yfloor + 1;

            bool wantGE = ccw ? (dx > 0) : (dx < 0);
            if (wantGE) lo = max(lo, yceil);
            else hi = min(hi, yfloor);
        }
        if (valid && lo <= hi) {
            yLo[x] = lo; yHi[x] = hi; has[x] = true;
        }
    }

    vector<vector<int>> classCount(m, vector<int>(m, 0));
    for (ll x = 0; x <= 5000; x++) {
        if (!has[x]) continue;
        for (ll y = yLo[x]; y <= yHi[x]; y++)
            classCount[x % m][y % m]++;
    }

    ll ans = 0;
    for (ll x = 0; x <= 5000; x++) {
        if (!has[x]) continue;
        for (ll y = yLo[x]; y <= yHi[x]; y++)
            if (classCount[x % m][y % m] >= 2) ans++;
    }

    cout << ans << "\n";
}