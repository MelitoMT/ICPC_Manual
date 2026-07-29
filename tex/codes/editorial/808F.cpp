#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef tuple<ll,ll,ll> tll;
typedef vector<tll> vtl;
 
#define all(v) v.begin(),v.end()
#define pb(x) push_back(x)
 
const ll inf = 1e17;
 
struct flowEdge {
    int u,v;
    ll cap,flow = 0; 
    flowEdge(int u, int v, ll cap) : u(u), v(v), cap(cap) {};
};
 
struct Dinic{
    vector<flowEdge> edges; 
    vector<vi> adj; 
    int n,s,t; 
    int id = 0;
    vi level, next; 
    
    queue<int> q;
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        next.resize(n);
        fill(all(level),-1); 
        level[s] = 0; 
        q.push(s);
    }
 
    void add(int u, int v, ll cap){
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0);
        adj[u].pb(id++); 
        adj[v].pb(id++); 
    }
 
    bool bfs(){
        while (!q.empty()){
            int curr = q.front();
            q.pop();
            for (auto e : adj[curr]){
                if (edges[e].cap - edges[e].flow  < 1) continue; 
                if (level[edges[e].v] != -1) continue; 
                level[edges[e].v] = level[edges[e].u] + 1; 
                q.push(edges[e].v);
            }
        }
        return level[t] != -1; 
    }
 
    ll dfs(int u, ll flow){
        if (flow == 0) return 0;
        if (u == t) return flow;
        for (auto& cid = next[u]; cid < adj[u].size(); cid++){ 
            int e = adj[u][cid]; 
            int v = edges[e].v; 
 
            if (level[edges[e].u] + 1 != level[v] || edges[e].cap - edges[e].flow < 1) continue;
            ll f = dfs(v,min(flow,edges[e].cap - edges[e].flow)); 
            if (f == 0) continue; 
            edges[e].flow += f; 
            edges[e ^ 1].flow -= f;
            return f;
        }
        return 0;
    }
 
    ll maxFlow(){
        ll flow = 0;
        while (bfs()){
            fill(all(next),0);
            for (ll f = dfs(s,inf); f != 0ll; f = dfs(s,inf)) flow += f;
            fill(all(level),-1); 
            level[s] = 0;
            q.push(s);
        }
        return flow;
    }
};
 
vi sieve(){
    ll n = 2e5+1;
    vi nums(n), primes;
    for(int i = 2 ; i*i < n ; i++){
        if(nums[i])
            continue;
        for(int j = i*2 ; j < n ; j += i)
            nums[j] = 1;
    }
    for(int i = 2 ; i < n ; i++)
        if(nums[i] == 0)
            primes.push_back(i);
    return primes;
}
 
bool check(vtl &ones, vtl &odd, vtl &even, set<ll> &primes, ll level, ll k, ll n){
    Dinic dinic(n+2,n,n+1);
    ll n1 = ones.size(), n2 = odd.size(), n3 = even.size();
    ll sum = 0;
    for(int i = 0 ; i < n2 ; i++){
        auto [p,c,l] = odd[i];
        if(l <= level){
            sum += p;
            dinic.add(n,n1+i,p);
        }
    }
    for(int i = 0 ; i < n3 ; i++){
        auto [p,c,l] = even[i];
        if(l <= level){
            sum += p;
            dinic.add(n1+n2+i,n+1,p);
        }
    }
    ll onep = 0;
    for(auto [p,c,l] : ones){
        if(l <= level)
            onep = max(onep,p);
    }
    if(n1 != 0){
        dinic.add(n,0,onep);
        sum += onep;
        for(int i = 0 ; i < n3 ; i++){
            auto [p,c,l] = even[i];
            if(primes.count(c+1))
                dinic.add(0,n1+n2+i,inf);
        }
    }
    for(int i = 0 ; i < n2 ; i++){
        auto [p,c,l] = odd[i];
        for(int j = 0 ; j < n3 ; j++){
            auto [tp,tc,tl] = even[j];
            if(primes.count(c+tc))
                dinic.add(n1+i,n1+n2+j,inf);
        }
    }
    return (sum - dinic.maxFlow()) >= k;
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    ll n,k; cin >> n >> k;
    vtl odd, even, ones;
    for(int i = 0 ; i < n ; i++){
        ll p,c,l; cin >> p >> c >> l;
        if(c == 1)
            ones.emplace_back(p,c,l);
        else if(c%2)
            odd.emplace_back(p,c,l);
        else
            even.emplace_back(p,c,l);
    }
    vi primes = sieve();
    set<ll> s(primes.begin(),primes.end());
 
    ll l = 1, r = n, ans = -1;
    while(l <= r){
        ll m = (l + r)/2;
        if(check(ones,odd,even,s,m,k,n)){
            ans = m;
            r = m-1;
        }else{
            l = m+1;
        }
    }
    cout << ans << '\n';
}