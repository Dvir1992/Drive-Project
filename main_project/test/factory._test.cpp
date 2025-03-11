
#include "factory.hpp"
#include <iostream>
#include <memory>

using namespace std;

class shape
{
    public:
        virtual void print_shape() = 0;
};
class circle: public shape
{
    public:
        virtual void print_shape(){cout<<"circle\n";};
};
class square: public shape
{
    public:
        virtual void print_shape(){cout<<"square\n";};
};
class triangle: public shape
{
    public:
        virtual void print_shape(){cout<<"triangle\n";};
};

shape* create_circle()
{
    return new circle();
}
shape* create_square()
{
    return new square();
}
shape* create_triangle()
{
    return new triangle();
}
int main()
{
    Factory<int, shape*> factory;
    factory.Add(1,create_circle);
    factory.Add(2,create_square);
    factory.Add(3,create_triangle);
    std::shared_ptr<shape> circle(factory.Create(1));
    std::shared_ptr<shape> square(factory.Create(2));
    std::shared_ptr<shape> triangle(factory.Create(3));
    try
    {
        std::shared_ptr<shape> none(factory.Create(4));
    }
    catch(const std::exception& e)
    {
        std::cerr<<"out_of_range: "<<e.what()<<'\n';
    }
    
  
    circle->print_shape();
    square->print_shape();
    triangle->print_shape();
    return 0;
}