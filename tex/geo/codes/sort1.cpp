bool N(point x){
    return prodCruz(v,x) > 0 || ( prodCruz(v,x) == 0 && prodPunto(v,x) > 0 );
}