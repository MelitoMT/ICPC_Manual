#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int MAXN = 100005;

ll power(ll a, ll b) {
    ll res = 1; a %= MOD;
    while (b > 0) { if (b & 1) res = res * a % MOD; a = a * a % MOD; b >>= 1; }
    return res;
}
ll inv(ll a) { return power(a, MOD - 2); }

int n; ll k;
ll e[MAXN];
vector<int> g[MAXN];
ll ans[MAXN];

int sz[MAXN];
bool removed[MAXN];
int cpar[MAXN];

int calcSz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u])
        if (v != p && !removed[v])
            sz[u] += calcSz(v, u);
    return sz[u];
}

int centroid(int u, int p, int treeSz) {
    for (int v : g[u])
        if (v != p && !removed[v] && sz[v] > treeSz / 2)
            return centroid(v, u, treeSz);
    return u;
}

// Info de un nodo respecto al centroide actual
struct Info {
    ll sum;  // suma de espiritualidades en el camino c -> nodo
    ll pt;   // prob de nodo -> c (como nodo inicio)
    ll pf;   // prob de c -> nodo (como c inicio)
    int node;
};

// DFS desde hijo de centroide c
// fc: factor de continuacion = prod inv(deg-1) de intermedios hacia c
// pf: prob_from_start = inv(deg(c)) * prod inv(deg-1) de intermedios desde c
void dfs(int u, int p, ll sum, ll fc, ll pf, vector<Info>& paths) {
    if (sum > k) return;
    ll pt = inv((ll)g[u].size()) * fc % MOD;
    paths.push_back({sum, pt, pf, u});
    for (int v : g[u]) {
        if (v == p || removed[v]) continue;
        int ef = (int)g[u].size() - 1;
        dfs(v, u, sum + e[v], fc * inv(ef) % MOD, pf * inv(ef) % MOD, paths);
    }
}

// Query: suma de arr[i].second para arr[i].first <= thr
ll query(vector<pair<ll,ll>>& arr, vector<ll>& pre, ll thr) {
    int pos = upper_bound(arr.begin(), arr.end(),
                          make_pair(thr, (ll)2e18)) - arr.begin();
    return pre[pos];
}

void buildPre(vector<pair<ll,ll>>& arr, vector<ll>& pre) {
    sort(arr.begin(), arr.end());
    pre.assign(arr.size() + 1, 0);
    for (int i = 0; i < (int)arr.size(); i++)
        pre[i + 1] = (pre[i] + arr[i].second) % MOD;
}

void build(int u, int p) {
    int total = calcSz(u, -1);
    int c = centroid(u, -1, total);
    cpar[c] = p;
    removed[c] = true;

    int dc = (int)g[c].size();
    // factor para prob_from_mid: cuando c es intermedio tiene deg-1 opciones
    ll fm = (dc > 1) ? (ll)dc % MOD * inv(dc - 1) % MOD : 1;

    // Recolectar paths por subarbol
    vector<vector<Info>> subs;
    for (int v : g[c]) {
        if (removed[v]) continue;
        vector<Info> sp;
        dfs(v, c, e[c] + e[v], 1LL, inv(dc), sp);
        subs.push_back(move(sp));
    }

    // Caso u = c: Zuko empieza en c
    if (e[c] <= k) {
        ans[c] = (ans[c] + 1) % MOD;
        for (auto& sp : subs)
            for (auto& x : sp)
                ans[x.node] = (ans[x.node] + x.pf) % MOD;
    }

    // Caso v = c: contribucion de todos los u != c
    for (auto& sp : subs)
        for (auto& x : sp)
            ans[c] = (ans[c] + x.pt) % MOD;

    // Pares de subarboles distintos
    vector<Info> prev_all;
    vector<pair<ll,ll>> prev_pt_arr;
    vector<ll> prev_pt_pre;

    for (auto& sp : subs) {
        // Prefix sums de prob_to para sp
        vector<pair<ll,ll>> sp_pt_arr;
        vector<ll> sp_pt_pre;
        for (auto& x : sp)
            sp_pt_arr.push_back({x.sum, x.pt});
        buildPre(sp_pt_arr, sp_pt_pre);

        // v en sp, u en prev: ans[v] += pfm[v] * sum_pt(prev, threshold)
        for (auto& x : sp) {
            ll thr = k - x.sum + e[c];
            if (thr >= 0 && !prev_pt_arr.empty()) {
                ll spt = query(prev_pt_arr, prev_pt_pre, thr);
                ans[x.node] = (ans[x.node] + x.pf % MOD * fm % MOD * spt) % MOD;
            }
        }

        // v en prev, u en sp: ans[v] += pfm[v] * sum_pt(sp, threshold)
        for (auto& x : prev_all) {
            ll thr = k - x.sum + e[c];
            if (thr >= 0) {
                ll spt = query(sp_pt_arr, sp_pt_pre, thr);
                ans[x.node] = (ans[x.node] + x.pf % MOD * fm % MOD * spt) % MOD;
            }
        }

        // Agregar sp a prev
        for (auto& x : sp) {
            prev_all.push_back(x);
            prev_pt_arr.push_back({x.sum, x.pt});
        }
        buildPre(prev_pt_arr, prev_pt_pre);
    }

    // Recursar en cada componente
    for (int v : g[c])
        if (!removed[v])
            build(v, c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> e[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build(1, -1);
    ll inv_n = inv(n);
    for (int v = 1; v <= n; v++)
        cout << ans[v] * inv_n % MOD << " \n"[v == n];
}

/*#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const ll MOD = 998244353;
 
ll power(ll a, ll b) {
    ll res=1; a%=MOD;
    while(b>0){if(b&1)res=res*a%MOD;a=a*a%MOD;b>>=1;}
    return res;
}
ll inv(ll a){return power(a,MOD-2);}
 
int n; ll k;
ll e[100005];
vector<int> adj[100005];
ll ans[100005];
int sz[100005];
bool removed[100005];
 
int getSize(int u,int p){
    sz[u]=1;
    for(int v:adj[u]){
        if(v!=p&&!removed[v]){
            sz[u]+=getSize(v,u);
        }
    }
    return sz[u];
}

//obtiene centroide
int getCentroid(int u,int p,int treeSz){
    for(int v:adj[u]){
        if(v!=p&&!removed[v]&&sz[v]>treeSz/2){
            return getCentroid(v,u,treeSz);
        } 
    }
    return u;
}
 
struct acumV{ll sum,pt,pf;int node;};
 
void dfs(int u,int p,ll sum,ll fc,ll pf,vector<acumV>&paths){
    if(sum>k)return;
    ll pt=inv(adj[u].size())*fc%MOD;
    paths.push_back({sum,pt,pf,u});
    for(int v:adj[u]){
        if(v==p||removed[v])continue;
        int ef=adj[u].size()-1;
        dfs(v,u,sum+e[v],fc*inv(ef)%MOD,pf*inv(ef)%MOD,paths);
    }
}
 
// query: suma de arr[i].second para arr[i].first <= thr (arr sorted by first)
ll query(vector<pll>&arr, vector<ll>&pre, ll thr){
    int pos=upper_bound(arr.begin(),arr.end(),make_pair(thr,(ll)2e18))-arr.begin();
    return pre[pos];
}
 
void buildPre(vector<pll>&arr, vector<ll>&pre){
    sort(arr.begin(),arr.end());
    pre.assign(arr.size()+1,0);
    for(int i=0;i<arr.size();i++){
        pre[i+1]=(pre[i]+arr[i].second)%MOD;
    }
}
 
void solve(int u){
    int treeSz=getSize(u,-1);
    int c=getCentroid(u,-1,treeSz);
    removed[c]=true;
 
    int cDeg=adj[c].size();
    ll fm=1;
    //prob (opciones)
    if(cDeg>1){
        fm=cDeg%MOD*inv(cDeg-1)%MOD;
    }
 
    vector<vector<acumV>> subs;
    for(int v:adj[c]){
        if(removed[v])continue;
        vector<acumV> sp;
        dfs(v,c,e[c]+e[v],1,inv(cDeg),sp);
        subs.push_back(sp);
    }
 
    // u=c
    if(e[c]<=k){
        ans[c]=(ans[c]+1)%MOD;
        for(auto&sp:subs){
            for(auto&x:sp)
                ans[x.node]=(ans[x.node]+x.pf)%MOD;
        }
    }
    // v=c
    for(auto&sp:subs){
        for(auto&x:sp){
            ans[c]=(ans[c]+x.pt)%MOD;
        }
    }
 
    // pares de subárboles distintos
    vector<acumV> prev_all;
    vector<pll> prev_pt_arr, prev_pfm_arr;
    vector<ll> prev_pt_pre, prev_pfm_pre;
 
    for(auto&sp:subs){
        // construir prefix sums para sp
        vector<pll> sp_pt_arr, sp_pfm_arr;
        vector<ll> sp_pt_prefix, sp_pfm_prefix;
        for(auto&x:sp){
            sp_pt_arr.push_back({x.sum,x.pt});
            sp_pfm_arr.push_back({x.sum,x.pf*fm%MOD});
        }
        buildPre(sp_pt_arr,sp_pt_prefix);
        buildPre(sp_pfm_arr,sp_pfm_prefix);
 
        // v en sp, u en prev: ans[v] += pfm[v] * sum_pt(prev, k-sv+e[c])
        for(auto&x:sp){
            ll thr=k-x.sum+e[c];
            if(thr>=0&&!prev_pt_arr.empty()){
                ll spt=query(prev_pt_arr,prev_pt_pre,thr);
                ans[x.node]=(ans[x.node]+x.pf%MOD*fm%MOD*spt)%MOD;
            }
        }
 
        // v en prev, u en sp: ans[v] += pfm[v] * sum_pt(sp, k-sv+e[c])
        for(auto&x:prev_all){
            ll thr=k-x.sum+e[c];
            if(thr>=0){
                ll spt=query(sp_pt_arr,sp_pt_prefix,thr);
                ans[x.node]=(ans[x.node]+x.pf%MOD*fm%MOD*spt)%MOD;
            }
        }
 
        // agregar sp a prev
        for(auto&x:sp){
            prev_all.push_back(x);
            prev_pt_arr.push_back({x.sum,x.pt});
            prev_pfm_arr.push_back({x.sum,x.pf*fm%MOD});
        }
        buildPre(prev_pt_arr,prev_pt_pre);
        buildPre(prev_pfm_arr,prev_pfm_pre);
    }
 
    for(int v:adj[c]){
        if(!removed[v]){
            solve(v);
        }
    }
}
 
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>e[i];
    for(int i=0;i<n-1;i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(1);
    ll inv_n=inv(n);
    for(int v=1;v<=n;v++){
        cout<<ans[v]*inv_n%MOD<<" \n"[v==n];
    }
}*/