#include <bits/stdc++.h>
using namespace std;
 
int n;
vector<int> adj[200005];
int sz[200005];
 
void calcSz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u])
        if (v != p) {
            calcSz(v, u);
            sz[u] += sz[v];
        }
}
 
int centroid(int u, int p) {
    for (int v : adj[u])
        if (v != p && sz[v] > n / 2)
            return centroid(v, u);
    return u;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    calcSz(1, -1);
    cout << centroid(1, -1) << "\n";
}