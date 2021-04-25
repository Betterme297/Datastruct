#include<iostream>
#include<cmath>
#include"HashSep.h"
using namespace std;

int a[] = {23,15,56,48,78,89,51,46,38,56,56,32,12,78,-1};   //待输入的关键字
int dele[]= {23,15,56,78,11,-1};                            //待删除的关键字

struct ListNode{
    int key;        //关键字
    List Next;      //指向下一个结点的指针
};
struct HashTbl{
    int TableSize;    //散列表的大小
    List* TheLists;    //存放链表头节点的数组
};
int main(){
    HashTable H = InitializeTable(5);
    BuildHashTable(H);
    PrintHashTable(H);
    int i = 0;
    while(dele[i] > 0){
        Delete(H, dele[i]);
        i++;
    }
    H = ReHash(H);
    DestroyHashTable(H);
    return 0;
}
HashTable ReHash(HashTable H){
    int i, oldsize;
    List * oldLists;
    Position p;
    oldLists = H->TheLists;
    oldsize = H->TableSize;

    HashTable H_new = InitializeTable(2 * oldsize);       //创建一个新的空表,大小翻倍
    
    //扫描旧的Hash表，移动到新的表里面
    for(i = 0;i < oldsize; i++){
        p = H->TheLists[i]->Next;
        while(p){
            Insert(H_new, p->key);
            p = p->Next;
        }
    }
    free(oldLists);
    free(p);
    cout<<"After Rehash:"<<endl;
    PrintHashTable(H_new);
    return H_new;
}
int NextPrime(int N){
    int i,p;
    p = (N%2)? N+2 : N+1;       //获得大于N的最小奇数，初步进行素数的判断
    while(p < MaxTableSize){  
        for(i = p-1; i > 2; i--){
            if(!(p%i))
                //若P不是素数，则break
                break;
        }
        if(i == 2)
            break;
        else 
            p+=2;       //查找下一个奇数是否为素数
    }
    if(p > MaxTableSize) cout<<"no suitable TableSize"<<endl;
    else return p;
}
HashTable InitializeTable(int TableSize){
    HashTable H;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = NextPrime(TableSize);    //使散列表长度为素数
    H->TheLists = (List*)malloc(H->TableSize * sizeof(List));   //初始化每个单元格单链表的头节点
    for(int i = 0; i < H->TableSize; i++){
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        if(H->TheLists[i] == NULL)  cout<<"out of space"<<endl;
        else 
            H->TheLists[i]->Next = NULL;
    }
    return H;
}
void BuildHashTable(HashTable H){
    int i = 0;
    while(1){
        /*int a;
        cin>>a;*/
        if(a[i] >= 0){
            Insert(H, a[i]);
            i++;
        }
        else break;
    }
}
void PrintHashTable(HashTable H){
    float count = 0;
    Position p;
    p = (Position)malloc(sizeof(struct ListNode));
    cout<<"The Hash Table is: "<<endl;
    for(int i = 0; i < H->TableSize; i++){
        p = H->TheLists[i]->Next;
        cout<<"S["<<i<<"]:";
        while(p){
            cout<<p->key<<' ';
            count++;
            p = p->Next;
        }
        cout<<endl;
    }
    //cout<<"Capacity is "<<count/H->TableSize<<endl;
}
int Hash(int key, int TableSize){
    return key%TableSize;
}
Position Find(HashTable H, int key){
    Position p;
    int index;                          //散列链表的地址
    index = Hash(key, H->TableSize);    //获得初始散列地址
    p = H->TheLists[index]->Next;       //从计算出的散列链表的头结点的Next开始查找
    while(p && p->key != key)
        p = p->Next;
    return p;
}
void Insert(HashTable H, int key){
    Position p, newcell;
    int index;
    p = Find(H, key);
    if(!p) {                //若表中没有这个key，正常插入
        newcell = (Position)malloc(sizeof(struct ListNode));    //插入新结点
        newcell->key = key;
        index = Hash(key, H->TableSize);            //获得该插入元素的插入地址
        newcell->Next = H->TheLists[index]->Next;   //将newcell插入到链表的第一个结点
        H->TheLists[index]->Next = newcell;
    }
    else    cout<<"The key "<<key<<" is already in the HashTable"<<endl;
}
void Delete(HashTable H, int key){
    Position p, q;
    int index;
    /*int a;
    cin>>a;  */                           //输入要删除的元素
    index = Hash(key, H->TableSize);      //获得待删除元素的初始散列地址
    p = H->TheLists[index]->Next;       //从该散列地址的头结点的Next开始查找
    if(p && p->key == key){             //对于待删除元素位于头结点的特殊情况
        H->TheLists[index]->Next = p->Next;
        free(p);
        cout<<"The key "<<key<<" is Successfully Deleted"<<endl;
        PrintHashTable(H);              //删除完成后再输出一遍散列表
    }
    else{
        while(p->Next && p->Next->key != key){
            p = p->Next;
        }
        if(!p->Next){       //若散列表中没有待删除的元素
            cout<<"The key "<<key<<" isn`t in this HashTable"<<endl;
        }
        else{
            q = p->Next;    //q为待删除结点
            p->Next = q->Next;
            free(q);
            cout<<"The key "<<key<<" is Successfully Deleted"<<endl;
            PrintHashTable(H);
        }
    }
}
void DestroyHashTable(HashTable H){
    Position p, temp;
    for(int i = 0;i<H->TableSize; i++){
        p = H->TheLists[i]->Next;
        while(p){
            temp = p->Next;
            free(p);
            p = temp;
        }
    }
    free(H->TheLists);
    free(H);
}