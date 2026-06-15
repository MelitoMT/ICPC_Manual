#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 10005;
const int LOG = 14;
int n;
vector<pair<int,int>> adj[MAXN]; 
int up[MAXN][LOG];
int depth_[MAXN];  
ll distRoot[MAXN];  

void dfs(int u, int p, int d, ll dist) {
    up[u][0] = p;
    depth_[u] = d;
    distRoot[u] = dist;
    for (auto [v, w] : adj[u])
        if (v != p)
            dfs(v, u, d+1, dist+w);
}

void buildLift() {
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++)
            up[i][j] = (up[i][j-1] == 0) ? 0 : up[up[i][j-1]][j-1];
}

int lca(int a, int b) {
    if (depth_[a] < depth_[b]) swap(a,b);
    int diff = depth_[a] - depth_[b];
    for (int j = 0; j < LOG; j++)
        if ((diff >> j) & 1) a = up[a][j];
    if (a == b) return a;
    for (int j = LOG-1; j >= 0; j--)
        if (up[a][j] != up[b][j]) { a = up[a][j]; b = up[b][j]; }
    return up[a][0];
}

int kthAncestor(int u, int k) {
    for (int j = 0; j < LOG; j++)
        if ((k >> j) & 1) u = up[u][j];
    return u;
}

int main() {
    int t; cin>>t;
    while (t--) {
        cin>>n;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < n-1; i++) {
            int a,b,c;cin>>a>>b>>c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
        }
        up[1][0] = 0; 
        dfs(1, 0, 0, 0);
        buildLift();

        for (int j = 0; j < LOG; j++) up[0][j] = 0;

        char op[10];
        while (true) {
            cin>>op;
            if (op[0] == 'D' && op[1] == 'O') break; 
            int a,b; cin>>a>>b;
            if (op[0] == 'D') {
                int l = lca(a,b);
                cout<<distRoot[a] + distRoot[b] - 2*distRoot[l]<<"\n";
            } else {
                int k; cin>>k;
                int l = lca(a,b);
                int lenA = depth_[a] - depth_[l]; 
                if (k-1 <= lenA) {
                    cout<<kthAncestor(a, k-1)<<"\n";
                } else {
                    int lenB = depth_[b] - depth_[l];
                    int stepsFromB = lenA + lenB - (k-1);
                    cout<<kthAncestor(b, stepsFromB)<<"\n";
                }
            }
        }
    }
}