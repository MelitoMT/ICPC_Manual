int mcm(int a, int b){
    return (a/mcd(a,b))*b;
}