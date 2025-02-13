#include<iostream>

using std::cout;

class AbstractProductA
{
public:
    virtual void show() = 0;
    virtual ~AbstractProductA() = 0;
};
AbstractProductA::~AbstractProductA(){};

class ProductA:public AbstractProductA
{
public:
    virtual void show() override
    {
        cout<<"i am product A\n";
    }
};

class AbstractProductB
{
public:
    virtual void show() = 0;
    virtual ~AbstractProductB() = 0;
};
AbstractProductB::~AbstractProductB(){};

class ProductB:public AbstractProductB
{
public:
    virtual void show() override
    {
        cout<<"i am product B\n";
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory() = 0;
    virtual ProductA* createProductA() = 0;
    virtual ProductB* createProductB() = 0;
};
AbstractFactory::~AbstractFactory(){};

class ConcreteFactory1 : public AbstractFactory
{
public:
virtual ProductA* createProductA() override
{
    ProductA *pA = new ProductA;
    return pA;
}

virtual ProductB* createProductB() override
{
    ProductB *pB = new ProductB;
    return pB;
}
};

class ConcreteFactory2 : public AbstractFactory
{
public:
virtual ProductA* createProductA() override
{
    ProductA *pA = new ProductA;
    return pA;
}

virtual ProductB* createProductB() override
{
    ProductB *pB = new ProductB;
    return pB;
}
};

int main(void)
{
    ConcreteFactory1 *f1 = new ConcreteFactory1;
    ProductA *pA_1 = f1->createProductA();
    ProductB *pB_2 = f1->createProductB();
    pA_1->show();
    pB_2->show();
    ConcreteFactory2 *f2 = new ConcreteFactory2;
    ProductA *pA_3 = f1->createProductA();
    ProductB *pB_4 = f1->createProductB();
    pA_3->show();
    pB_4->show();
    delete pA_1;
    delete pB_2;
    delete pA_3;
    delete pB_4;
    delete f1;
    delete f2;
    return 0;
}
