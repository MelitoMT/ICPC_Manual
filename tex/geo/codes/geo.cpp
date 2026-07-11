#include <algorithm>
#include <cmath>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

struct Point {
    double x, y;

    Point operator+(Point other) {
        return {x + other.x, y + other.y};
    }

    Point operator-(Point other) {
        return {x - other.x, y - other.y};
    }

    Point operator*(double scalar) {
        return {x * scalar, y * scalar};
    }

    Point operator/(double scalar) {
        return {x / scalar, y / scalar};
    }
};

bool operator==(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(Point a, Point b) {
    return !(a == b);
}

double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// True si el punto esta en la region N respecto a v = (1, 0).
bool inNorthernHalf(Point x) {
    Point reference = {1, 0};
    return crossProduct(reference, x) > 0
        || (crossProduct(reference, x) == 0 && dotProduct(reference, x) > 0);
}

bool operator<(Point x, Point y) {
    return (inNorthernHalf(x) == inNorthernHalf(y) && crossProduct(x, y) > 0)
        || (inNorthernHalf(x) && !inNorthernHalf(y));
}

int windingNumber(std::vector<Point>& polygon, Point query) {
    int winding = 0;
    int n = polygon.size();

    for (int i = 0; i < n; i++) {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % n];

        if (a.y <= query.y) {
            // Arista cruza hacia arriba: b esta estrictamente sobre el rayo.
            if (b.y > query.y && crossProduct(b - a, query - a) > 0) {
                winding++;
            }
        } else {
            // Arista cruza hacia abajo: b esta sobre o bajo el rayo.
            if (b.y <= query.y && crossProduct(b - a, query - a) < 0) {
                winding--;
            }
        }
    }

    return winding;
}

bool isInside(std::vector<Point> polygon, Point query) {
    return windingNumber(polygon, query) != 0;
}

std::vector<Point> convexHull(std::vector<Point>& points) {
    int n = points.size();
    if (n < 2) {
        return points;
    }

    std::sort(points.begin(), points.end());
    std::vector<Point> hull;

    // Hull inferior: de izquierda a derecha.
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2
               && crossProduct(
                      hull.back() - hull[hull.size() - 2],
                      points[i] - hull[hull.size() - 2]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Hull superior: de derecha a izquierda.
    int lowerSize = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() >= lowerSize
               && crossProduct(
                      hull.back() - hull[hull.size() - 2],
                      points[i] - hull[hull.size() - 2]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Al cerrar el hull, el primer punto se repite.
    hull.pop_back();
    return hull;
}

// Representamos segmentos como pares de puntos.
using Segment = std::pair<Point, Point>;

bool segmentsIntersect(const Segment& a, const Segment& b) {
    return false;
    // Implementacion dejada como ejercicio en la seccion de intersecciones.
}

// Dado un segmento y una coordenada x, regresa la y correspondiente.
double getY(const Segment& segment, double x) {
    if (std::abs(segment.first.x - segment.second.x) < 1e-9) {
        return segment.first.y;
    }

    return segment.first.y
        + (segment.second.y - segment.first.y)
            * (x - segment.first.x)
            / (segment.second.x - segment.first.x);
}

double sweepX;

// Comparador para ordenar segmentos activos por su y en sweepX.
struct SegmentComparator {
    bool operator()(const Segment& a, const Segment& b) const {
        double ya = getY(a, sweepX);
        double yb = getY(b, sweepX);

        if (std::abs(ya - yb) > 1e-9) {
            return ya < yb;
        }
        return a < b;
    }
};

bool shamosHoey(std::vector<Segment> segments) {
    int n = segments.size();

    // Asegurar que cada segmento vaya de izquierda a derecha.
    for (Segment& segment : segments) {
        if (segment.first.x > segment.second.x) {
            std::swap(segment.first, segment.second);
        }
    }

    // Eventos: (x, tipo, indice). tipo = 1 inicio, tipo = -1 fin.
    std::vector<std::tuple<double, int, int>> events;
    for (int i = 0; i < n; i++) {
        events.push_back({segments[i].first.x, 1, i});
        events.push_back({segments[i].second.x, -1, i});
    }

    std::sort(events.begin(), events.end(),
              [](auto& a, auto& b) {
                  if (std::abs(std::get<0>(a) - std::get<0>(b)) > 1e-9) {
                      return std::get<0>(a) < std::get<0>(b);
                  }
                  return std::get<1>(a) > std::get<1>(b);
              });

    std::set<Segment, SegmentComparator> active;
    // Iteradores para borrar sin depender del comparador dinamico.
    std::vector<std::set<Segment, SegmentComparator>::iterator> position(
        n, active.end());

    for (auto& [x, eventType, id] : events) {
        sweepX = x;

        if (eventType == 1) {
            // Evento de inicio.
            auto it = active.insert(segments[id]).first;
            position[id] = it;
            auto nextIt = std::next(it);

            // Buscar interseccion con vecinos (ejercicio de intersecciones).
            if (nextIt != active.end() && segmentsIntersect(*it, *nextIt)) {
                return true;
            }

            auto prevIt = (it != active.begin()) ? std::prev(it) : active.end();
            if (prevIt != active.end() && segmentsIntersect(*it, *prevIt)) {
                return true;
            }
        } else {
            // Evento de fin.
            auto it = position[id];
            auto nextIt = std::next(it);
            auto prevIt = (it != active.begin()) ? std::prev(it) : active.end();

            if (nextIt != active.end() && prevIt != active.end()
                && segmentsIntersect(*nextIt, *prevIt)) {
                return true;
            }

            active.erase(it);
        }
    }

    return false;
}
