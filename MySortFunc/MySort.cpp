#include"MySort.h"
#include<iostream>
#include<time.h>
using namespace std;
#define MIN_LENGTH 20
ArrayList InitializeArray(int length){
    ArrayList A;
    if(length < 0)          //若数组长度不合法，则使用一个合理的默认值
        length = MIN_LENGTH;
    A = (ArrayList) malloc(sizeof(struct _arrayList));
    if(A == NULL)           //空间不足，初始化失败
        return NULL;
    A->MaxSize = length;    //设定数组的最大长度；
    A->ListSize = 0;        //当前数组大小为0
    A->Data = (int *)malloc(sizeof(int) * length);
    if(A->Data == NULL){
        free(A);
        return NULL;
    }
    return A;
}
void Build_Array(ArrayList A, int X){
    if(A->ListSize >= A->MaxSize){
        cout<<"The ArrayList is out of space!"<<endl;
    }
    else{                       //当数组未满时正常插入
    A->Data[A->ListSize] = X;   //插入完毕后ListSize加1
    A->ListSize += 1;
    //cout<<"The Number "<<X<<" is successfully Inserted"<<endl;
    }
}
void PrintArray(ArrayList A){
    int i;
    cout<<"The ArrayList is:"<<endl;
    for( i = 0; i < A->ListSize; i++){
        cout<<A->Data[i]<<' ';
    }
    cout<<endl;
}
void Insert_Sort_Array(ArrayList A){
    int i, j;
    for(i = 1; i < A->ListSize; i++){               //第一个数一定有序，故从第二个数开始遍历
        int temp = A->Data[i];                      //取出第i个数和前i-1个数比较，插入合适的位置
        j = i - 1;
        while(j >= 0 && A->Data[j] > temp){
            A->Data[j + 1] = A->Data[j];            //将大于temp的数据往后移
            j--;
        }
        A->Data[j + 1] = temp;
    }
}
void ArrayList_Free(ArrayList A){
    if(A != NULL){
        free(A->Data);
        free(A);
        cout<<"The ArrayList has been deleted"<<endl;
    }
}


void Build_List(List L, int X){
    List newcell = (List)malloc(sizeof(struct _list));
    if(newcell == NULL)
        cout<<"out of space!"<<endl;
    else{
        newcell->key = X;
        newcell->Next = NULL;
        List p = L;                             //遍历到链表尾部，在其后插入新的结点
        while(p->Next){
            p = p->Next;
        }
        p->Next = newcell;
    }
}
List GetPartion(List pBegin, List pEnd){
    int key = pBegin->key;          //取链表第一个结点的数为基准数
    List p = pBegin;                //p,q两个指针均从前向后遍历
    List q = p->Next;               //使p前面的key都小于基准数，p和q之间的key都大于基准数
    while(q != pEnd){               //这样最后的p就是基准数的位置
        if(q->key < key){           //当q的key小于基准数时，交换key值，使其位于p之前
            p = p->Next;            //因此p后移一位，与q的key值进行交换
            int temp1 = p->key;
            p->key = q->key;
            q->key = temp1;
        }
        q = q->Next;
    }
    int temp2 = p->key;             //遍历结束后，当前p的key值应为基准数，故与pBegin进行交换
    p->key = pBegin->key;
    pBegin->key = temp2;
    return p;                       //返回基准数位置的指针
}
void Quick_Sort_List(List pBegin, List pEnd){       //递归调用快速排序函数
    if(pBegin != pEnd){ 
        List partion = GetPartion(pBegin, pEnd);
        Quick_Sort_List(pBegin, partion);
        Quick_Sort_List(partion->Next, pEnd);
    }
}
void PrintList(List L){
    List p = L;
    cout<<"The List is:"<<endl;
    while(p->Next){
        cout<<p->Next->key<<' ';
        p = p->Next;
    }
    cout<<endl;
}