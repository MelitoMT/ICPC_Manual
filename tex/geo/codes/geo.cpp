#include <bits/stdc++.h>
using namespace std;

typedef double db;
struct point {
    db x,y;
    point operator+(point p) {
        return {x + p.x, y + p.y};
    }
    point operator-(point p) {
        return {x - p.x, y - p.y};
    }
    point operator*(db a) {
        return {x*a, y*a};
    }
    point operator/(db a) {
        return {x/a, y/a};
    }

};

bool operator==(point a,point b) {
    return a.x==b.x && a.y==b.y;
}
bool operator!=(point a, point b) {
    return !(a==b);
}

bool N(point x){
    point v = {1,0};
    return prodCruz(v,x) > 0 || ( prodCruz(v,x) == 0 && prodPunto(v,x) > 0 );
}

bool operator <(point x, point y){
    return (N(x) == N(y) && prodCruz(x,y) > 0) || (N(x) && !N(x));
}

double prodPunto(point a, point b){
    return a.x*b.x + a.y*b.y;
}

double prodCruz(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

int winding_number(vector<point> poly, point q) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        point a = poly[i], b = poly[(i+1) % n];
        if (a.y <= q.y) {
            // arista cruza hacia arriba: b esta estrictamente sobre el rayo
            if (b.y > q.y && prodCruz(b-a,q-a) > 0)
                wn++;
        } else {
            // arista cruza hacia abajo: b esta sobre o bajo el rayo
            if (b.y <= q.y && prodCruz(b-a,q-a) < 0)
                wn--;
        }
    }
    return wn;
}

bool dentro(vector<point> poly, point q) {
    return winding_number(poly, q) != 0;
}

vector<point> convex_hull(vector<point> pts) {
    int n = pts.size();
    if (n < 2) return pts;
    sort(pts.begin(), pts.end());
    vector<point> hull;
    /*construimos hull inferior
    izquierda a derecha*/ 
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
                /*producto cruz entre
                B-A y C-A*/
                prodCruz(hull.back()-hull[hull.size()-2], pts[i]-hull[hull.size()-2])<= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
 
    /*construimos hull superior
    derecha a izquierda*/ 
    int lower_size = hull.size() + 1;
    for (int i = n-2; i >= 0; i--) {
        while (hull.size() >= lower_size &&
                /*producto cruz entre
                B-A y C-A*/
                prodCruz(hull.back()-hull[hull.size()-2], pts[i]-hull[hull.size()-2])<= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    
    //al cerrarlo este punto se repite
    hull.pop_back();
    return hull;
}

bool intersectan(const seg& a, const seg& b) {
    return false;
    /*ld o1 = orient(a.first, a.second, b.first);
    ld o2 = orient(a.first, a.second, b.second);
    ld o3 = orient(b.first, b.second, a.first);
    ld o4 = orient(b.first, b.second, a.second);
    return ((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
           ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0));*/
}

//representamos segmentos como pares de puntos
using seg = pair<point, point>;
//funcion que nos devuelve dado un segmento y un x, la y del segmento.
db getY(const seg& s, db x) {
    if (abs(s.first.x - s.second.x) < 1e-9){
        return s.first.y;
    } 
    return s.first.y + 
        (s.second.y - s.first.y)
        * (x - s.first.x)
        / (s.second.x - s.first.x);
}

db sweepX;
//Comparador para ordenar los segmentos por y
struct cmp {
    bool operator()(const seg& a, const seg& b) const {
        db ya = getY(a, sweepX);
        db yb = getY(b, sweepX);
        if (abs(ya - yb) > 1e-9){
            return ya < yb;
        }
        return a < b;
    }
};

bool shamos_hoey(vector<seg> segs) {
    int n = segs.size();
    /*asegurarse que los segmentos
    vayan de izquierda a derecha*/
    for (auto& s : segs){
        if (s.first.x > s.second.x){
            swap(s.first, s.second);
        }
    }
    /*
    eventos guardara la x del punto, 
    1 o -1 que nos indicara si es de inicio 
    o fin respectivamente,
    el indice en el vector original
    */
    vector<tuple<db,int,int>> eventos;
    for (int i = 0; i < n; i++) {
        eventos.push_back(
            {segs[i].first.x,   1, i}
        );
        eventos.push_back(
            {segs[i].second.x,  -1, i}
        );
    }
    sort(eventos.begin(), eventos.end(),
    [](auto& a, auto& b){
        if (abs(get<0>(a) 
        - get<0>(b)) > 1e-9){
            return get<0>(a) < get<0>(b);
        }
        return get<1>(a) > get<1>(b);
    });
 
    set<seg,cmp> activos;
    /*estructura que nos ayude
    a borrar sin depender del
    comparador que definimos*/
    vector<set<seg,cmp>::iterator> pos(n, activos.end());
    for (auto& [x, tipo, id] : eventos) {
        sweepX = x;
        //procesamos nodo de inicio
        if (tipo == 1) {
            auto it  = 
            activos.insert(segs[id]).first;
            pos[id]  = it;
            auto sig = next(it);
            auto ant = (it != activos.begin())
            ? prev(it)
            : activos.end();
            /*buscar interseccion con 
            vecinos, se dejo como ejercicio
            en intersecciones*/
            if (sig != activos.end()
            && intersectan(it, sig)){
                return true;
            } 
            if (ant != activos.end()
            && intersectan(it, ant)){
                return true;
            }
            //procesamos nodo de final
        } else {
            auto it  = pos[id];
            auto sig = next(it);
            auto ant = (it != activos.begin())
            ? prev(it)
            : activos.end();
            if (sig != activos.end()
            && ant != activos.end()
            && intersectan(*sig, *ant)){
                    return true;
            } 
            activos.erase(it);
        }
    }
    return false;
}