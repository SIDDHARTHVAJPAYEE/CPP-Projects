#include<iostream>
using namespace std;
template<class T>
class TMStack
{
T x[10];
int top;
public:
TMStack();
TMStack(const TMStack &other);
TMStack & operator=(const TMStack &other);
virtual ~TMStack();
void push(T data);
T pop();
int isEmpty();
int isFull();
};
template<class T>
TMStack<T>::TMStack()
{
cout<<"Default"<<endl;
this->top=10;
}
template<class T>
TMStack<T>::TMStack(const TMStack<T> &other)
{
cout<<"Copy "<<endl;
int e;
e=9;
while(e>=other.top)
{
this->x[e]=other.x[e];
e--;
}
this->top=other.top;
}
template<class T>
TMStack<T> & TMStack<T>::operator=(const TMStack<T> &other)
{
cout<<"operator ="<<endl;
int e;
e=9;
while(e>=other.top)
{
this->x[e]=other.x[e];
e--;
}
this->top=other.top;
return *this;
}
template<class T>
TMStack<T>::~TMStack()
{
//donothing
}
template<class T>
void TMStack<T>::push(T data)
{
if(top==0) return;
this->x[--top]=data;
}
template<class T>
T TMStack<T>::pop()
{
if(top==10) return 0;
T data=this->x[top++];
return data;
}
template<class T>
int TMStack<T>::isEmpty()
{
return this->top==10;
}
template<class T>
int TMStack<T>::isFull()
{
return this->top==0;
}
int main()
{
TMStack<float> s1;
s1.push(10.4);
s1.push(20.2);
s1.push(30.3);
TMStack<int> s2;
s2.push(100);
s2.push(200);
s2.push(300);
TMStack<int> s3=s2;
s3.push(5054);
cout<<"Popping from s1"<<endl;
while(!s1.isEmpty()) cout<<s1.pop()<<endl;
cout<<"popping from s2"<<endl;
while(!s2.isEmpty()) cout<<s2.pop()<<endl;
cout<<"popping from s3"<<endl;
while(!s3.isEmpty()) cout<<s3.pop()<<endl;
return 0;
}