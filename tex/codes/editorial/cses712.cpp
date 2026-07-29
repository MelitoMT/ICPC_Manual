#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll expo(ll a, ll b, ll MOD){
    if(b==0){
        return 1;
    }
    ll temp=expo(a,(b%MOD)/2,MOD)%MOD;
    temp=(temp*temp)%MOD;
    if(b%2==1){
        temp=(temp*a)%MOD;
    }
    return temp;
}
int main(){
    int n;cin>>n;
    for(int i=0;i<n;i++){
        ll a,b,c;cin>>a>>b>>c;
        ll temp=expo(b,c,1e9 + 6);
        cout<<expo(a,temp,1e9 + 7)<<"\n";
    }
