#include<iostream>
#include<string>

using std::cout;
using std::string;

class Figure
{
public:
    Figure() = default;
    ~Figure() = default;
    virtual void display() = 0;
    virtual double area() = 0;
};

class Rectangle:public Figure
{
public:
    Rectangle(double len,double width)
    :_len(len)
    ,_width(width)
    {
    }

    virtual void display() override
    {
        cout<<"I am rectangle\n";
    }
    virtual double area() override
    {
        return _len * _width;
    }
private:
    double _len;
    double _width;
};

class Circle:public Figure
{
public:
   Circle(double r)
    :_r(r)
    {}

    virtual void display() override
    {
        cout<<"I am Circle\n";
    }
    virtual double area() override
    {
        return _r*_r*3.14;
    }
private:
    double _r;
};

class SimpleFactory
{
public:
    static Figure * create(const string & name)
    {
        if(name == "rectangle")
        {
            Rectangle *pRec = new Rectangle(10,20);
            return pRec;
        }
        else
        {
            Circle *pCir = new Circle(10);
            return pCir;
        }
    }
};

int main(void)
{
    Figure * fig = SimpleFactory::create("rectangle");
    fig->display();
    cout<<"area = "<<fig->area()<<"\n";

    delete fig;
    return 0;
}
