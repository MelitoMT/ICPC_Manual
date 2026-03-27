#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int implementados = 0;

    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        // Si al menos dos estan seguros, se implementa el problema.
        if (a + b + c >= 2) {
            implementados++;
        }
    }

    cout << implementados << "\n";
}