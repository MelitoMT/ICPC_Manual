#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct point {
    ll x,y;
    point operator+(point p) {
        return {x + p.x, y + p.y};
    }
    point operator-(point p) {
        return {x - p.x, y - p.y};
    }
    point operator*(ll a) {
        return {x*a, y*a};
    }
    bool operator<(const point& p) const {
    return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const point& p) const {
        return x == p.x && y == p.y;
    }
};

ll prodCruz(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

vector<point> convexHull(vector<point> pts) {
    int n = pts.size();
    if (n < 2) return pts;
    sort(pts.begin(), pts.end());
    vector<point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
                prodCruz(hull.back()-hull[hull.size()-2], pts[i]-hull[hull.size()-2])<= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    int lower_size = hull.size();
    for (int i = n-2; i >= 0; i--) {
        while (hull.size() > lower_size &&
                prodCruz(hull.back()-hull[hull.size()-2], pts[i]-hull[hull.size()-2])<= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    hull.pop_back();
    return hull;
}
 
ll shoelace2(vector<point>& poly) {
    ll area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i+1) % n;
        area += poly[i].x * poly[j].y;
        area -= poly[j].x * poly[i].y;
    }
    return area;
}
 
ll borderPoints(vector<point>& poly) {
    ll b = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i+1) % n;
        ll dx = abs(poly[j].x - poly[i].x);
        ll dy = abs(poly[j].y - poly[i].y);
        b += __gcd(dx, dy);
    }
    return b;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n; cin >> n;
    vector<point> allPoints;
    
    for (int i = 0; i < n; i++) {
        ll x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        point p1 = {x1,y1}, p2 = {x2,y2};
        
        int k; cin >> k;
        vector<point> poly(k);
        for (int j = 0; j < k; j++) cin >> poly[j].x >> poly[j].y;
        for (auto& v : poly) {
            allPoints.push_back(v + p1);
            allPoints.push_back(v + p2);
        }
    }
    
    vector<point> hull = convexHull(allPoints);
    
    ll twoA = shoelace2(hull);
    ll B = borderPoints(hull);
    cout << (twoA - B + 2) / 2 << "\n";
}