//linked_Stack.h
#include<iostream>
using namespace std;
template<class T>
struct node
{
  T d;
  node *next;
};
template<class T>
class linked_Stack
{
 private:
  node<T> *top;
 public:
  linked_Stack();
  void prt_linked_Stack();
  int flag_linked_Stack();
  void ins_linked_Stack(T);
  T del_linked_Stack();
  T read_linked_Stack();
};
template<class T>
linked_Stack<T>::linked_Stack()
{
  top=NULL;
  return;
}
template<class T>
void linked_Stack<T>::prt_linked_Stack()
{
  node<T> *p;
  p=top;
  if (p==NULL) { cout<<"空栈！"<<endl; return;}
  do { cout<<p->d<<endl;
    p=p->next;}
  while (p!=NULL);
  return;
}
template<class T>
int linked_Stack<T>::flag_linked_Stack()
{
  if (top==0) return(0);
  return (1);
}

template<class T>
void linked_Stack<T>::ins_linked_Stack(T x)
{
  node<T> *p;
  p = new node<T>;
  p->d=x;
  p->next=top;
  top=p;
  return;
}

template<class T>
T linked_Stack<T>::del_linked_Stack()
{
  T y;
  node<T> *q;
  if (top==NULL) { cout<<"空栈！"<<endl; return (0);}
  q=top;
  y=q->d;
  top=q->next;
  delete q;
  return(y);
    }
template<class T>
T linked_Stack<T>::read_linked_Stack()
{
  if (top==NULL) { cout<<"空栈！"<<endl; return(0);}
  return(top->d);
}
