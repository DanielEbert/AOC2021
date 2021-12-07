
#include <map>

struct Point {
  int x, y;
};

bool operator< (const Point& a, const Point& b) {
  return a.x < b.x || (p1.x == p2.x && p1.y < p2.y);
}

int main() {
  map<Point, int> m;

}