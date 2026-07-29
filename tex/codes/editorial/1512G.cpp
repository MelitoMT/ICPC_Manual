#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int a=10000005;
    int sumas[a]={0};
    int numis[a]={0};
    for(int i=1;i<=a-5;i++){
        for(int j=i;j<=a-5;j+=i){
            sumas[j]+=i;
            if(sumas[i]<=a-5){
                if(numis[sumas[i]]==0)numis[sumas[i]]=i;
            }
        }
    }
    int t;cin>>t;
    while(t--){
        int ok=-1;
        int c;cin>>c;
        if(numis[c]!=0)ok=numis[c];
        cout<<ok<<endl;
    }
}