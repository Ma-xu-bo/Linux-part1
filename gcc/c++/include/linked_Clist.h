//linked_Clist.h
#include<iostream>
using namespace std;
template<class T>
struct node
{
  T d;
  node * next;
};
template<class T>
class linked_Clist
{
 private:
  node<T> *head;
 public:
  linked_Clist();
  void prt_linked_Clist();
  void ins_linked_Clist(T, T);
  int del_linked_Clist(T);
};
template<class T>
linked_Clist<T>::linked_Clist()
{
  node<T> *p;
  p = new node<T>;
  p->d = 0;
  p->next = p;
  head = p;
  return;
}
template<class T>
void linked_Clist<T>::prt_linked_Clist()
{
  node<T> *p;
  p = head->next;
  if (p == head) { cout<<"空循环列表!"<<endl; return;}
  do { cout<<p->d<<endl;
    p=p->next;}
  while (p!=head);
  return;
}
template<class T>
void linked_Clist<T>::ins_linked_Clist(T x,T b)
{
  node<T> *p, *q;
  p = new node<T>;
  p->d = b;
  q = head;
  while ((q->next!=head)&&(((q->next)->d)!=x))
    q = q->next;
  while ((q->next!=head)&&(((q->next)->d)!=x))
    q = q->next;
  p->next = q->next; q->next = p;
  return;
}
template <class T>
int linked_Clist<T>::del_linked_Clist(T x)
{
  node<T> *p, *q;
  q = head;
  while ((q->next!=head)&&(((q->next)->d)!=x))
    q = q->next;
  if (q->next==head) return(0);
  p=q->next;
  q->next=p->next;
  delete p;
  return(1);
}

  
