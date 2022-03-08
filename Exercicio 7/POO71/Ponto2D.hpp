#ifndef PONTO2D_HPP
#define PONTO2D_HPP

#include<iostream> 

class Ponto2D{
    
     public:
        Ponto2D(int xx = 0.0, int yy = 0.0):x(xx),y(yy){ };
        friend std::ostream& operator<< (std::ostream &op, const Ponto2D &p);
        Ponto2D& operator= (const Ponto2D &p);
        ~Ponto2D(){};
        double get_x(void) { return x; }
        double get_y(void) { return y; }
        void set (double nx, double ny) { x=nx; y=ny; }
    
    private:                
        double x;
        double y;
};

#endif

std::ostream& operator<< (std::ostream &op, const Ponto2D &p){
            op << std::endl;
            op << "x = " << p.x << std::endl;
            op << "y = " << p.y << std::endl;
            return op;
}

Ponto2D& Ponto2D::operator= (const Ponto2D &p){
    x = p.x;
    y = p.y;
    return *this;
}
