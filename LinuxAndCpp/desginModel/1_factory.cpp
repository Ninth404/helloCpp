#include<iostream>
#include<string>

using std::cout;
using std::string;

class Product
{
public:
    virtual void show() = 0;
    virtual ~Product() = 0;
};

class ProductA:public Product
{
public:
    ProductA(string name)
    :_name(name)
    {
    }

    virtual void show() override
    {
        cout<<"i am "<<_name<<"\n";
    }

private:
    string _name;
};

class ProductB:public Product
{
public:
    ProductB(string name)
    : _name(name)
    {
    }

    virtual void show() override
    {
        cout<<"i am "<<_name<<"\n";
    }

private:
    string _name;
};

class Factory
{
public:
    virtual Product * create() = 0;
    virtual ~Factory() = 0;
};

class FactoryForA : public Factory
{
public:
    virtual Product * create() override
    {
        ProductA * productA = new ProductA("A");
        return productA;
    }
};

class FactoryForB : public Factory
{
public:
    virtual Product * create() override
    {
        ProductB * productB = new ProductB("B");
        return productB;
    }
};

Product::~Product()
{}

Factory::~Factory()
{}

int main(void)
{
    Factory *factoryA = new FactoryForA();
    Product *pA = factoryA->create();
    pA->show();

    Factory *factoryB = new FactoryForB();
    Product *pB = factoryB->create();
    pB->show();

    delete factoryA;
    delete pA;
    delete factoryB;
    delete pB;
    return 0;
}
