#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcdExt(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0; 
        return a;
    }
    ll x1, y1;
    ll g = gcdExt(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

pair<ll,ll> crt(ll a1, ll m1, ll a2, ll m2) {
    ll p, q;
    ll g = gcdExt(m1, m2, p, q); 
    if ((a2 - a1) % g != 0) return {-1, -1};
    ll lcm = m1 / g * m2;
    ll diff = ((a2 - a1) / g) % (m2 / g);
    ll coef = (diff * p % (m2/g) + (m2/g)) % (m2/g); 
    ll x = (a1 % lcm + m1 % lcm * coef % lcm) % lcm;
    if (x < 0) x += lcm;
    return {x, lcm};
}

ll crtComb(vector<vector<int>> &cong){
    ll x=cong[0][0], mod = cong[0][1];
    for(int i=1;i<cong.size();i++){
        auto [x_t, mod_t] = crt(x,mod,cong[i][0], cong[i][1]);
        if(x_t==-1)return -1;
        x=x_t;
        mod=mod_t;
    }
    return x;
}

int main(){
    int b,z;cin>>b>>z;
    vector<vector<int>> zoo(b,vector<int> (z+1));
    for(int j=0;j<b;j++){
        for(int i=0;i<=z;i++){
            cin>>zoo[j][i];
        }
    }
    vector<vector<int>> startCycle(b,vector<int>(2));
    vector<vector<int>> locChecker(b,vector<int> (z+1,0));
    vector<int> loc(z+1);
    for(int j=0;j<b;j++){
        bool start=false;
        int pos;
        for(int i=0;i<=z;i++){
            if(!i){
                pos=zoo[j][0];
            }
            else{
                pos=zoo[j][pos];
            }
            if(!locChecker[j][pos]){
                locChecker[j][pos]=1;
            }
            else if(!start){
                startCycle[j][0]=pos;
                startCycle[j][1]=i;
                start=true;
            }
            if(!j)loc[i]=pos;
            else if(loc[i]!=-1&&loc[i] != pos){
                loc[i]=-1;
            }
        }
    }
    for(int i=0;i<z+1;i++){
       if(loc[i]!=-1){
            cout<<loc[i]<<" "<<i<<"\n";
            return 0;
        }
    }
    vector<vector<int>> zooCycleTime(b,vector<int>(z+1,-1));
    vector<vector<int>> cycle (b);
    for(int j=0;j<b;j++){
        int curPos = startCycle[j][0];
        cycle[j].push_back(curPos);
        int nxtPos = zoo[j][curPos];
        while(nxtPos != startCycle[j][0]){
            curPos = nxtPos;
            cycle[j].push_back(curPos);
            nxtPos = zoo[j][curPos];
        }
        
        int lambda = cycle[j].size();
        int t0 = startCycle[j][1] - lambda;
        
        for(int k = 0; k < lambda; k++){
            zooCycleTime[j][cycle[j][k]] = t0 + k;
        }
    }
    ll resTime=-1, resZoo=-1;
    for(int i=1;i<=z; i++){
        vector<vector<int>> cong(b,vector<int>(2));
        bool possible=true;
        
        for(int j=0;j<b;j++){
            if(zooCycleTime[j][i] ==-1){
                possible=false;
                break;
            }
            cong[j][1]=cycle[j].size();
            cong[j][0]=zooCycleTime[j][i];
        }
        if(possible){
            ll tmp = crtComb(cong);
            if(tmp!=-1){
                if(resZoo==-1){
                    resTime=tmp;
                    resZoo=i;
                }else{
                    if(tmp < resTime){
                        resTime=tmp;
                        resZoo=i;
                    }
                }
            }
        }
    }
    if(resTime!=-1){
        cout<< resZoo<<" "<<resTime<<"\n";
    }else{
        cout<<"*\n";
    }
}