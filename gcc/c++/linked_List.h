//linked_List.h
#include<iostream>
using namespace std;
template<class T>
struct node
{
  T d;
  node * next;
};
template<class T>
class linked_List
{
 private:
  node<T> * head;
 public:
  linked_List();
  void prt_linked_List();
  void ins_linked_List(T, T);
  int del_linked_List(T);
};
template<class T>
linked_List<T>::linked_List()
{
  head = NULL; return;
}
template<class T>
void linked_List<T>::prt_linked_List()
{
  node<T> * p;
  p=head;
  if (p=NULL) { cout<<"空链表！"<<endl; return; }
  do {
    cout<<p->d<<endl;
    p=p->next;
      }
  while (p!=NULL);
  return;
}
template<class T>
void linked_List<T>::ins_linked_List(T x,T b)
{
  node<T> * p, * q;
  p = new node<T>;
  p->d = b;
  if (head==NULL)
    {
      head = p; p->next=NULL; return;
    }
  if (head->d == x)
    {
      p->next=head; head = p; return;
      q = head;
      while ((q->next!=NULL)&&(((q->next)->d)!=x))
	q=q->next;
      p->next=q->next; q->next=p;
      return;
    }
}
template<class T>
    int linked_List<T>::del_linked_List(T x)
    {
      node<T> * p,* q;
      if (head==NULL) return(0);
      if ((head->d) == x)
	{
	  p=head->next; delete head; head=p; return(1);}
      q = head;
      while ((q->next!=NULL)&&(((q->next)->d)!=x))
	    q=q->next;
	if (q->next==NULL) return(0);
	p=q->next; q->next=p->next;
	delete p;
	return(1);
    }

    
