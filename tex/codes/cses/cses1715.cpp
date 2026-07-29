#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
 
ll power(ll a, ll b) {
    ll res = 1; a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return res;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    string s; cin >> s;
    int n = s.size();
 
    // Contar frecuencias
    int freq[26] = {};
    for (char c : s) freq[c - 'a']++;
 
    // Calcular n! mod p
    ll num = 1;
    for (int i = 1; i <= n; i++) num = num * i % MOD;
 
    // Dividir entre freq[i]! para cada letra
    // Usando inverso modular: a / b mod p = a * b^(p-2) mod p
    ll den = 1;
    for (int i = 0; i < 26; i++) {
        ll fact = 1;
        for (int j = 1; j <= freq[i]; j++) fact = fact * j % MOD;
        den = den * fact % MOD;
    }
 
    cout << num * power(den, MOD - 2) % MOD << "\n";
}