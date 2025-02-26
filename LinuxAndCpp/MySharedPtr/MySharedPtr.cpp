#include <iostream>

using std::cout;

template<typename T>
class ControlBlock
{
public:
    ControlBlock(T * ptr)
    :_ptr(ptr)
    ,_count(1)
    {

    }

    ~ControlBlock()
    {
        delete _ptr;
    }

    T * getPtr() const
    {
        return _ptr;
    }

    int getCount() const
    {
        return _count;
    }

    void increment()
    {
        ++_count;
    }

    void decrement()
    {
        --_count;
    }
private:
    T * _ptr;
    int _count;
};

template<typename T>
class MySharedPtr
{
public:
    explicit MySharedPtr(T * ptr = nullptr)
    :_control_block(ptr?new ControlBlock<T>(ptr):nullptr)
    {

    }

    ~MySharedPtr()
    {
        if(_control_block)
        {
            _control_block->decrement();
            if(_control_block->getCount() == 0)
            {
                delete _control_block;
            }
        }
    }

    MySharedPtr(const MySharedPtr & rhs)
    :_control_block(rhs._control_block)
    {
        if(_control_block)
        {
            _control_block->increment();
        }
    }

    MySharedPtr & operator=(const MySharedPtr & rhs)
    {   
        //考虑自复制
        if(this != &rhs)
        {
            if(_control_block)
            {
                _control_block->decrement();
                if(_control_block->getCount() == 0)
                {
                    delete _control_block;
                }
            }

            _control_block = rhs._control_block();
            if(_control_block)
            {
                _control_block->increment();
            }
        }

        return *this;
    }

    T * operator->() const
    {
        if(_control_block)
        {
            return _control_block->getPtr();
        }

        return nullptr;
    }

    T & operator*() const
    {
        return *_control_block->getPtr();
    }

    int use_count() const
    {
        if(_control_block)
        {
            return _control_block->getCount();
        }

        return 0;
    }

private:
    ControlBlock<T> * _control_block;
};

int main()
{
    MySharedPtr<int> ptr1(new int(10));

    cout<<"use_count = "<<ptr1.use_count()<<"\n";

    cout<<"*ptr1 = "<<*ptr1<<"\n";

    {
        MySharedPtr<int> ptr2 = ptr1;

        cout<<"use_count = "<<ptr1.use_count()<<"\n";
    }
    cout<<"use_count = "<<ptr1.use_count()<<"\n";

    {
        MySharedPtr<int> ptr3(ptr1);
        cout<<"use_count = "<<ptr1.use_count()<<"\n";
    }
    cout<<"use_count = "<<ptr1.use_count()<<"\n";


    return 0;
}