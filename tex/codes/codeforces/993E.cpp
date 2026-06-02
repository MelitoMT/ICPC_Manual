#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using ld = long double ;
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
    ll n,x;cin>>n>>x;
    vector<ll> a(n,0);
    for(int i = 0; i < n; i++){
        ll tmp;cin>>tmp;
        a[i] = (tmp < x) ? 1 : 0;
    }
    vector<ll> prefix(n+1,0);
    vector<ll> f(n+1,0);
    vector<ll> fInv(n+1,0);
    for(int i = 1; i <=n; i++){
        prefix[i] = a[i-1] + prefix[i-1];
    }
    for(int i = 0; i <= n; i++){
        if(!i)f[i]++;
        else f[prefix[i]]++;
        fInv[n-prefix[i]]++;
    }
    vector<ll> conv=multiply_fft(f,fInv);
    for(int i = 0; i <= n; i++){
        cout << (!i ? (conv[n]-(n+1))/2 : conv[n-i]); 
        if(i < n)cout<< " ";
    }
    cout<<"\n";
}