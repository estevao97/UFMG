#ifndef POINT_H
#define POINT_H

class Point {
  private:
    double x;
    double y;

  public:

    Point(double,double);
    Point();
    double getX() const;
    double getY() const;
    friend std::ostream & operator << (std::ostream &out, const Point &c);
    friend std::istream & operator >> (std::istream &in,  Point &c);
    Point operator + (const Point &p);
    Point& operator += (const Point &p);
};

#endif