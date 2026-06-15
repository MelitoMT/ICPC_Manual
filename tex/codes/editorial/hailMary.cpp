#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using ld = double ;
using cd = complex <ld>;
const ld PI = acosl(-1.0L) ;

void fft(vector< cd >& a , bool inv){
    int n = a . size ();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a [ i ], a [ j ]);
    }
    for (int len = 2; len <= n; len <<= 1){
        ld ang = 2 * PI / len *(inv ? -1 : 1) ;
        cd wlen (cosl(ang), sinl (ang)) ;
        for (int i = 0; i < n; i += len){
            cd w(1);
            for(int j = 0; j < len / 2; j ++){
                cd u = a[i + j];
                cd v = a[i + j + len / 2]*w;
                a[i + j] = u+v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if(inv)
    for(auto & x : a)x /= n;
}

vector<ll> multiply_fft(vector<ll> &a, vector<ll>&b){
    int sz1 = a.size(), sz2 = b.size();
    int n = 1;
    while (n < sz1+sz2) n <<= 1;

    vector<cd> fa(n,0), fb(n,0);
    for(int i = 0; i < sz1 ; i++) {
        fa [i] = a[sz1-1-i];
    }
    for(int i = 0; i < sz2 ; i++) {
        fb [i] = b[i];
    }

    fft(fa, false); fft(fb, false);
    for(int i = 0; i < n ; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true) ;

    vector<ll> res(sz2-sz1+1);
    for(int i = 0; i <= sz2-sz1; i++){
        res[i] = llroundl(fa[sz1-1+i].real());
    }
    return res;
}

int main(){
    ll m,n;cin>>m>>n;
    vector<ll> s(m), r(n);
    for(int i = 0; i < m; i++)cin>>s[i];
    for(int i = 0; i < n; i++)cin>>r[i];
    ll e,f;cin>>e>>f;

    vector<ll> score = multiply_fft(s,r);
    ll feliz=0,enojado=0;
    for(int i = 0; i<= n-m; i++){
        if(score[i]>=f)feliz++;
        else if(score[i] <= e)enojado++;
    }
    
    cout<<feliz<<" "<<enojado<<"\n";

}