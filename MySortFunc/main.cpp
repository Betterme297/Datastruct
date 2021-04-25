#include"MySort.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
#define MIN_LENGTH 20
int a[] = {31,21,44,4,90,55,12,67,47,823,612,62,-23,-546,-21,0};
int main(){
    ArrayList A = InitializeArray(50);
    int i = 0;
    while(a[i] != '\0'){                //从设置好的数组中读入数据
        Build_Array(A, a[i]);
        i++;
    }
    PrintArray(A);
    Insert_Sort_Array(A);
    cout<<"After Sort:"<<endl;
    PrintArray(A);
    ArrayList_Free(A);

    List L = (List)malloc(sizeof(struct _list));
    List pEnd;
    L->key = 0;
    L->Next = NULL;
    int j = 0;
    while(a[j] !='\0'){
        Build_List(L, a[j]);
        j++;
    }
    List p = L->Next;
    while(p->Next != NULL)
        p = p->Next;
    pEnd = p;           //获取链表的尾部结点用于快速排序
    PrintList(L);
    Quick_Sort_List(L->Next, NULL);
    cout<<"After Sorted:"<<endl;
    PrintList(L);
    system("pause");
    return 0;
}