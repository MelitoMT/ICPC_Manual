#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll n;cin>>n;
    vector<int> piedras(n);
    vector<int> congruencias(3,0);
    for(ll i=0;i<n;i++){
        ll a;cin>>a;a%=3;
        piedras[i]=a;
        congruencias[a]++;
    }
    ll z;
    if(congruencias[0]<=n/2){
        cout<<0<<"\n";
        ll cuenta=0,count=n/2-congruencias[0];
        string res="";
        for(ll i=0;i<n;i++){
            if(piedras[i]==0){
                res.push_back('1');
            }
            else if(cuenta<count){
                res.push_back('1');
                cuenta++;
            }else res.push_back('0');

        }
        cout<<res<<"\n";
    }
    else{
        cout<<2<<"\n";
        ll cuenta=0;
        string res="";
        for(ll i=0;i<n;i++){
            if(piedras[i]==0&&cuenta<n/2){
                res.push_back('1');
                cuenta++;
            }
            else res.push_back('0');
        }
        cout<<res<<"\n";
    }
}    
