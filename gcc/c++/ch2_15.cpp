#include<linked_List.h>
int main()
{
  linked_List<int> s;
  cout<<"第一次扫描输出链表s中的元素："<<endl;
  s.prt_linked_List();
  s.ins_linked_List(10,10);
  s.ins_linked_List(10,20);
  s.ins_linked_List(10,30);
  s.ins_linked_List(40,40);
  cout<<"第二次扫描输出链表s中的元素："<<endl;
  s.prt_linked_List();
  if (s.del_linked_List(30))
    cout<<"删除元素：30"<<endl;
  else
    cout<<"链表中无元素：30"<<endl;
  if (s.del_linked_List(50))
    cout<<"删除元素：50"<<endl;
  else
    cout<<"第三次输出的链表s中的元素："<<endl;
  s.prt_linked_List();
  return 0;
}
