#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll const mod=998244353;
ll const MAXN=1e6;
ll fact[MAXN];
void prec(){
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
}   

ll modPow(ll a, ll b, ll m){
    if (b == 0) return 1;
    ll k = modPow(a, b / 2, m);
    k = k * k;
    k %= m;
    if (b & 1) k = (k * a) % m;
    return k;
}
ll inv(ll a){
    return modPow(a, mod-2, mod);
}
ll CnR(int n, int k) {
    return fact[n] * inv(fact[k] * fact[n - k] % mod) % mod;
}


int main(){
    prec();
    ll n;cin>>n;
    ll dif=1;
    ll cant=CnR(n/3,n/6);
    for(int i=1;i<=n/3;i++){
        vector<ll> nums;
        for(int j=1;j<=3;j++){
            ll a;cin>>a;
            nums.push_back(a);
        }
        sort(nums.begin(),nums.end());
        if(nums[0]==nums[1]){
            if(nums[1]==nums[2])dif*=3;
            else dif*=2;
        }
        dif%=mod;
    }   
    dif*=cant;dif%=mod;
    cout<<dif<<"\n";
    
}