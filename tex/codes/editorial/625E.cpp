#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const long long MAX=400005;
vector<int> adj[MAX];
set<pair<int,int>> puentes;
int ini,fin;
vector<int> componentes(MAX,0);
vector<bool> compPremio(MAX,false);
set<pair<int,int>> puentes2;
vector<int> adj2[MAX];
bool oki=false;
void dfsBR(int u, int p,vector<int>&low,vector<int>&disc,int &Time,set<pair<int, int>> &br) {
  low[u] = disc[u] = ++Time;
  for (int& v : adj[u]) {
    if (v == p) continue; 
    if (!disc[v]) { 
      dfsBR(v, u,low,disc,Time,br);  
      if (disc[u] < low[v]){
        br.insert({u, v});
        br.insert({v, u});
      }
      low[u] = min(low[u], low[v]); 
    } else 
      low[u] = min(low[u], disc[v]); 
  }
}
void BR(int n,set<pair<int, int>> &br) {
  vector<int>low(n+1), disc(n+1,0);
  int Time = 0;
  for (int u = 1; u <= n; u++)
    if (!disc[u])
      dfsBR(u, u,low,disc,Time,br);    
}
void dfs(int padre,int node,bool premio){
      for(auto u:adj2[node]){
        if(u!=padre){
          bool aux=premio;
          if(!aux){
            if(compPremio[u]==true||compPremio[padre]==true)aux=true;
            else if(puentes2.count({u,node}))aux=true;
          }
          if(u==componentes[fin]){
            if(aux)oki=true;
            return;
          }
          dfs(node,u,aux);
        }
      }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,z;cin>>x>>y>>z;
        if(z==1){
          puentes.insert({x,y});
          puentes.insert({y,x});
        }
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    cin>>ini>>fin;
    set<pair<int, int>> br;
    BR(n,br);
    //////////
    int cont=1;
    queue<int> q;
    bool visited[n+1];
    memset(visited,false,sizeof visited);
    visited[1]=true;
    q.push(1);
    componentes[1]=1;
    while(!q.empty()){
      int s=q.front();q.pop();
      for(auto x:adj[s]){
        if(!visited[x]){
            visited[x]=true;
            if(!br.count({s,x})){
                componentes[x]=componentes[s];
                if(puentes.count({s,x})){
                    compPremio[componentes[x]]=true;
                }
            }else{
                cont++;
                componentes[x]=cont;
                adj2[componentes[s]].push_back(cont);
                adj2[cont].push_back(componentes[s]);
                if(puentes.count({s,x})){
                    puentes2.insert({componentes[s],cont});
                    puentes2.insert({cont,componentes[s]});
                }  
            }
            q.push(x);
        }else{
            if(componentes[x]==componentes[s]){
                if(puentes.count({s,x})){
                    compPremio[componentes[x]]=true;
                }
            }
        }
      }
    }
    if(componentes[ini]==componentes[fin]&&compPremio[componentes[ini]]==true)oki=true;
    else dfs(0, componentes[ini],false);
    if(oki)cout<<"YES"<<"\n";
    else cout<<"NO"<<"\n";
}