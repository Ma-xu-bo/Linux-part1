//ch2_18.cpp
#include<linked_Clist.h>
int main()
{
  linked_Clist<int> s;
  cout<<"第一次扫描输出循环链表s中的元素："<<endl;
  s.prt_linked_Clist();
  s.ins_linked_Clist(10, 10);
  s.ins_linked_Clist(10, 20);
  s.ins_linked_Clist(10, 30);
  s.ins_linked_Clist(40, 40);
  cout<<"第二次扫描输出循环链表s中的元素："<<endl;
  s.prt_linked_Clist();
  if (s.del_linked_Clist(30))
    cout<<"删除元素30"<<endl;
  else
    cout<<"循环链表中五元素：30"<<endl;
  if (s.del_linked_Clist(50))
    cout<<"删除元素50"<<endl;
  else
    cout<<"循环链表中五元素：50"<<endl;
  cout<<"第三次扫描输出链表s中的元素："<<endl;
  s.prt_linked_Clist();
  return 0;
  
}
