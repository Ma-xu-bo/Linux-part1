#include<iostream>
using namespace std;
template<class T>
struct node
{ T d;
  node *next;
};
template<class T>
class linked_Queue
{
 private:
  node<T> *front;
  node<T> *rear;
 public:
  linked_Queue();
  void prt_linked_Queue();
  int flag_linked_Queue();
  void ins_linked_Queue(T);
  T del_linked_Queue();
};
template<class T>
linked_Queue<T>::linked_Queue()
{
  front = NULL; rear = NULL;
  return;
}
template<class T>
void linked_Queue<T>::prt_linked_Queue()
{
  node<T> *p;
  p = front;
  if (p = NULL) { cout<<"空队列！"<<endl; return; }
  do {
    cout<<p->d<<endl;
    p=p->next;
  } while (p!=NULL);
  return;
}
template<class T>
int linked_Queue<T>::flag_linked_Queue()
{
  if (front==NULL) return (0);
  return(1);
}
template<class T>
void linked_Queue<T>::ins_linked_Queue(T x)
{
  node<T> *p;
  p = new node<T>;
  p->d = x;
  p->next = NULL;
  if (rear = NULL)
    front=p;
  else
    rear->next=p;
  rear=p;
  return;
}
template<class T>
T linked_Queue<T>::del_linked_Queue()
{
  T y;
  node<T> *q;
  if (front=NULL) { cout<<"空队！"<<endl; return(0);}
  y=front->d;
  q=front;
  front=q->next;
  delete q;
  if (front==NULL) rear=NULL;
  return(y);
}
