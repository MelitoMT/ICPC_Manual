#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 300009;
int nxt[MAXN];
int firstSeg[MAXN];

struct Point {
    ll x, y;
    int type, idx;
    Point operator-(const Point& o) const { return {x-o.x, y-o.y}; }
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        if (type != o.type) return type < o.type;
        return y < o.y;
    }
};
vector<Point> events;
typedef pair<Point,Point> Seg;
Seg segs[MAXN];
Point memo[MAXN];

ll cross(Point a, Point b) { return a.x*b.y - a.y*b.x; }

bool cmpHeight(int a, int b) {
    Point a1 = segs[a].first, a2 = segs[a].second;
    Point b1 = segs[b].first, b2 = segs[b].second;
    if (a1.x < b1.x) return cross(a1-b1, a2-b1) > 0;
    return cross(b1-a1, b2-a1) < 0;
}

set<int, bool(*)(int,int)> active(cmpHeight);

void sweep() {
    for (int i = 0; i < events.size(); i++) {
        int id = events[i].idx;
        if (events[i].type == 0) {
            active.insert(id);
            auto it = active.find(id);
            Point p1 = segs[id].first, p2 = segs[id].second;
            if (p1.y > p2.y) {
                ++it;
                nxt[id] = (it == active.end()) ? -1 : *it;
            }
        } else if (events[i].type == 1) {
            auto it = active.begin();
            firstSeg[id] = (it == active.end()) ? -1 : *it;
        } else {
            auto it = active.find(id);
            Point p1 = segs[id].first, p2 = segs[id].second;
            if (p1.y < p2.y) {
                ++it;
                nxt[id] = (it == active.end()) ? -1 : *it;
            } else if (p1.y == p2.y) {
                nxt[id] = -1; 
            }
            active.erase(id);
        }
    }
}

Point resolve(ll x, ll y, int id) {
    if (id == -1) return {x, y};
    Point p1 = segs[id].first, p2 = segs[id].second;
    if (p1.y == p2.y) return {x, p1.y};

    if (memo[id].x != -1) return memo[id];

    ll hx = (p1.y < p2.y) ? p2.x : p1.x;
    return memo[id] = resolve(hx, 0, nxt[id]);
}

int main(){
    int n,c;
    cin>>n>>c;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        int t1, t2;
        Point tmp = {x1,y1};
        Point tmp2 = {x2,y2};
        if (x1 < x2){
            t1 = 0; t2 = 2; 
            segs[i] = make_pair(tmp,tmp2); 
        }
        else{
            t1 = 2; t2 = 0;
            segs[i] = make_pair(tmp2,tmp); 
        }
        memo[i] = {-1, -1};
        tmp = {x1, y1, t1, i};
        tmp2 = {x2, y2, t2, i};
        events.push_back(tmp);
        events.push_back(tmp2);
    }

    vector<int> queryX(c);
    for (int i = 0; i < c; i++) {
        ll x; cin>>x;
        Point tmp = {x, 0, 1, i};
        events.push_back(tmp);
        queryX[i] = x;
    }

    sort(events.begin(),events.end());
    sweep();

    for (int i = 0; i < c; i++) {
        Point res = resolve(queryX[i], 0, firstSeg[i]);
        if (res.y == 0)cout<<res.x<<"\n";
        else cout<<res.x<<" "<<res.y<<"\n";
    }
}
