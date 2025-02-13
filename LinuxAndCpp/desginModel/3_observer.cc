#include <iostream>
#include <memory>
#include <list>
#include <string>

using std::cout;
using std::list;
using std::unique_ptr;
using std::string;

class Observer
{
public:
    virtual void update(int status) = 0;
    virtual ~Observer() = 0;
};
Observer::~Observer(){};

class ConcreteObserver1:public Observer
{
public:
    ConcreteObserver1(string name)
    :_name(name)
    {

    }
    virtual void update(int status) override
    {
        cout<<"now status = "<<status<<"\n";
    }
private:
    string _name;
};

class ConcreteObserver2:public Observer
{
public:
    ConcreteObserver2(string name)
    :_name(name)
    {
    }
    virtual void update(int status) override
    {
        cout<<"now status = "<<status<<"\n";
    }
private:
    string _name;
};

class Subject
{
public:
    virtual void attach(Observer * ob) = 0;
    virtual void detach(Observer * ob) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = 0;
};
Subject::~Subject(){};

class ConcreteSubject:public Subject
{
public:
    virtual void attach(Observer *ob) override
    {
        _myObservers.push_back(ob);   
    }
    
    virtual void detach(Observer *ob) override
    {
        if(ob)
        {
            _myObservers.remove(ob);
        }
    }

    virtual void notify() override
    {
        for(auto &ob : _myObservers)
        {
            ob->update(_status);
        }
    }

    void setStatus(int status)
    {
        _status = status;
    }

    int getStatus()
    {
        return _status;        
    }
private:
    list<Observer*> _myObservers;
    int _status;
};

int main()
{
    unique_ptr<ConcreteSubject> psub(new ConcreteSubject());
    unique_ptr<Observer> poa(new ConcreteObserver1("lili"));
    unique_ptr<Observer> pob(new ConcreteObserver2("lucy"));

    //将观察者添加到主题上
    psub->attach(poa.get());
    psub->attach(pob.get());
    //如果主题的状态发生变更
    psub->setStatus(2);
    //发通知
    psub->notify();

    cout << "\n";
    //加入某个观察者不想关注主题的变更
    psub->detach(pob.get());
    //如果主题的状态发生变更
    psub->setStatus(3);
    //发通知
    psub->notify();
    return 0;
}

