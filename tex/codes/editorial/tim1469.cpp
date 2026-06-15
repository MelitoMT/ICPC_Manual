#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct point { // More like event
    ll x, y;
    bool start;  
    int segment; 
    point operator- (const point& b) const { return { x - b.x, y - b.y, start }; }
    ll operator% (const point& b) const { return x*b.y - b.x*y; } 
    bool operator< (const point& b) const {
        return make_tuple(x,!start,y,segment) < make_tuple(b.x,!b.start,b.y,b.segment);
    }
};
struct segment {
    point s, e; 
    int i; 
    bool operator<(const segment& b) const {
        if(b.s.x == s.x)
            return b.s.y > s.y;
        if(b.s.x < s.x)
            return (b.s-b.e)%(s-b.e) > 0;
        return (s-e)%(b.s-e) < 0;
    }
} segments[50001];

set<segment> segset;
set<point> events;

bool in(ll a, ll b, ll c) { 
    return std::min(a, b) <= c && c <= std::max(a, b);
}

bool intersects(const segment& a, const segment& b) { 
    auto x = (b.s - a.s) % (a.e - a.s);
    auto y = (b.e - a.s) % (a.e - a.s);
    auto z = (a.s - b.s) % (b.e - b.s);
    auto w = (a.e - b.s) % (b.e - b.s);
    if(x*y == 0 && z*w == 0)
        return in(a.s.x, a.e.x, b.s.x) && in(a.s.y, a.e.y, b.s.y) ||
               in(a.s.x, a.e.x, b.e.x) && in(a.s.y, a.e.y, b.e.y);
    return x*y <= 0 && z*w <= 0;
}

set<segment>::iterator prev(const set<segment>::iterator& it) {
    return it == segset.begin() ? segset.end() : std::prev(it);
}

set<segment>::iterator next(const set<segment>::iterator& it) {
    return it == segset.end() ? segset.end() : std::next(it);
}

pair<int, int> solve() {
    for(auto& e : events) {
        if(e.start) {
            auto s = e.segment;
            auto it = segset.lower_bound(segments[s]);
            auto it2 = prev(it);
            for(auto i : { it, it2 })
                if(i != segset.end())
                    if(intersects(*i, segments[s]))
                        return { i->i, s };
            segset.insert(segments[s]);
        } else {
            auto s = e.segment;
            auto it = segset.find(segments[s]);
            auto it2 = prev(it), it3 = next(it);
            if(it2 != segset.end() && it3 != segset.end())
                if(intersects(*it2, *it3))
                    return { it2->i, it3->i };
            segset.erase(segments[s]);
        }
    }
    return { -1, -1 };
}

segment make_segment(ll x1, ll y1, ll x2, ll y2, int i) {
    point s = { x1, y1, false, i }, e = { x2, y2, false, i };
    if(e < s)
        std::swap(s, e);
    s.start = true, e.start = false;
    return segment { s, e, i };
}

int main() {
    int N;
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);

        segments[i] = make_segment(x1, y1, x2, y2, i);
        events.insert(segments[i].s);
        events.insert(segments[i].e);
    }

    auto p = solve();
    if(p.first >= 0)cout<<"YES\n"<<p.first<<" "<<p.second<<"\n";
    else cout<<"NO\n";
}