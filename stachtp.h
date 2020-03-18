#ifndef STACKTP_H_
#define STACKTP_H_

template <class T>
class Stack
{
private:
    enum {MAX=10};
    T items[MAX];
    int top;
public:
    Stack();
    bool isempty();
    bool isfull();
    void push(const T& item);
    T pop(T& item);
};

template <class T>
Stack<T>::Stack()
{
    top = 0;
}

template <class T>
Stack<T>::isempty()
{
    return top == 0;
}

template<class T>
Stack<t>::isfull()
{
    return top == MAX;
}

template<class T>
void Stack<T>::push(const T& item)
{
    if (top < MAX)
    {
        items[top++] = item;
    }
    else
        throw StackException ("Full!");
}

T Stack<T>::pop()
{
    if (top > 0)
    {
        T item = items[--top];
        return item;
    }
    else
        throw StackException ("Empty!");
}
    
#endif

    