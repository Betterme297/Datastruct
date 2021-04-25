#ifndef _MySort_h
#define _MySort_h

struct _arrayList{
    int *Data;              //数据的数据域
    int ListSize;           //当前数组已经存放的数据数
    int MaxSize;            //数组的最大长度
};
typedef struct _arrayList* ArrayList;
struct _list;
typedef struct _list* List;
struct _list{
    int key;                //链表的数据域
    List Next;              //指向下一个结点的指针
};

ArrayList InitializeArray(int length);              //初始创建一个新的可变数组  
void Build_Array(ArrayList A, int X);               //向可变数组尾部插入数据
void Insert_Sort_Array(ArrayList A);                //数组的直接插入排序
void PrintArray(ArrayList A);                       //打印数组
void Build_List(List L, int X);                     //向链表尾部插入数据
void ArrayList_Free(ArrayList A);                   //删除一个可变数组
void PrintList(List L);                             //打印链表
List GetPartion(List pBegin, List pEnd);            //获取基准数据
void Quick_Sort_List(List pBegin, List pEnd);       //递归快速排序


#endif