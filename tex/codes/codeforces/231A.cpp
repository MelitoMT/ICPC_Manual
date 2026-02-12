#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n;
    int implementados = 0;
    for(int i = 0; i < n; i++){
        int contador = 0;
        for(int j = 0; j < 3; j++){
            int temp; cin>>temp;
            if(temp == 1){
                contador++;
            }
        }
        if(contador >= 2){
            implementados++;
        }
    }
    cout<<implementados<<"\n";
}