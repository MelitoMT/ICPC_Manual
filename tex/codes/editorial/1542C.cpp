#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxi=60;
const ll mod=1e9+7;
vector<ll> fact={1,1};
ll gcd(ll a ,ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}
ll lcm(ll a,ll b){
    return (a*b)/gcd(a,b);
}
ll solve(){
    ll n;cin>>n;
    ll cont=0;
    for(ll i=0;i<fact.size()&&fact[i]<=n;i++){
        cont+=(n/fact[i])%mod;
        cont%=mod;
    }
    return cont;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t;cin>>t;
    for(int i=2;i<=40;i++){
        fact.push_back(lcm(fact[i-1],i));
    }
    while(t--){
        cout<<solve()<<"\n";
    }
}