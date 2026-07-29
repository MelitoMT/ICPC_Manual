#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using ld = double ;
using cd = complex < ld >;
const ld PI = acosl ( -1.0L ) ;

void fft ( vector < cd >& a , bool inv ) {
    int n = a . size () ;
    for ( int i = 1 , j = 0; i < n ; i ++) {
        int bit = n >> 1;
        for (; j & bit ; bit >>= 1) j ^= bit ;
        j ^= bit ;
        if ( i < j ) swap ( a [ i ] , a [ j ]) ;
    }
    for ( int len = 2; len <= n ; len <<= 1) {
        ld ang = 2 * PI / len * ( inv ? -1 : 1) ;
        cd wlen ( cosl ( ang ) , sinl ( ang ) ) ;
        for ( int i = 0; i < n ; i += len ) {
            cd w (1) ;
            for ( int j = 0; j < len / 2; j ++) {
                cd u = a [ i + j ];
                cd v = a [ i + j + len / 2] * w ;
                a [ i + j ] = u + v ;
                a [ i + j + len / 2] = u - v ;
                w *= wlen ;
            }
        }
    }
    if ( inv )
    for ( auto & x : a ) x /= n ;
}

vector < ll > multiply_fft ( vector < ll > a , vector < ll > b ) {
    int result_size = a . size () + b . size () - 1;
    int n = 1;
    while ( n < result_size ) n <<= 1;
    vector < cd > fa ( n ) , fb ( n ) ;
    for ( int i = 0; i < ( int ) a . size () ; i ++) {
        fa [ i ] = a [ i ];
    }
    for ( int i = 0; i < ( int ) b . size () ; i ++) {
        fb [ i ] = b [ i ];
    }
    fft ( fa , false ) ; fft ( fb , false ) ;
    for ( int i = 0; i < n ; i ++) {
        fa [ i ] *= fb [ i ];
    }
    fft ( fa , true ) ;
    vector < ll > res ( result_size ) ;
    for ( int i = 0; i < result_size ; i ++) {
        res [ i ] = llroundl ( fa [ i ]. real () ) ;
    }
    return res ;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,x,y;cin>>n>>x>>y;
    vector<ll> a(n+1,0);
    vector<ll> f(x+1,0);
    vector<ll> fInv(x+1,0);
    for(int i=0;i<=n;i++){
        cin>>a[i];
        f[a[i]]++;
        fInv[x-a[i]]++;
    }
    ll q;cin>>q;
    vector<ll> conv=multiply_fft(f,fInv);
    vector<ll> divs;
    divs.reserve(1500);
    for(int i=0;i < q; i++){
        ll querie;cin>>querie;
        ll dif=-1;
        if(querie & 1)cout<< -1 << "\n";
        else{
            querie/=2;
            for(int i=1;i*i<=querie;i++){
                if(querie%i==0){
                    divs.push_back(i);
                    if(i != querie/i) divs.push_back(querie/i);
                }
            }
            sort(divs.begin(), divs.end(), greater<ll>());
            //cout<< "querie: "<<querie*2<< " ";
            for(int j=0; j< divs.size();j++){
                //cout<< divs[j]<< " ";
                ll d=divs[j]-y;
                if(divs[j]>y && d<=x && conv[x-d]){
                    dif=divs[j];
                    break;
                }
            }
            //cout<< "\n";
            cout<<(dif!=-1?2*dif:-1)<<" ";
        }
        divs.clear();
    }
    cout<< "\n";
}