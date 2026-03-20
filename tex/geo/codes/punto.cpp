typedef double db;
struct point {
    db x,y;
    point operator+(point p) {return {x + p.x, y + p.y};}
    point operator-(point p) {return {x - p.x, y - p.y};}
    point operator*(db a) {return {x*a, y*a};}
    point operator/(db a) {return {x/a, y/a};}
};