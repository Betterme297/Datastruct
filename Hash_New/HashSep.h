#ifndef _HashSep_H
#define _HashSep_H


#define MaxTableSize 30                 //散列表的最大长度

struct ListNode;
typedef struct ListNode * Position;     //散列地址类型
typedef Position List;                  //链表
struct HashTbl;
typedef struct HashTbl * HashTable;     //散列表类型
int NextPrime(int N);                   //返回大于N且小于MaxTableSize的最小素数
HashTable InitializeTable(int TableSize);   //初始化散列表
void BuildHashTable(HashTable H);           //向散列表中输入数据
void PrintHashTable(HashTable H);           //输出散列表
int Hash(int key, int TableSize);             //hash函数
Position Find(HashTable H, int key);          //查找key的函数
void Insert(HashTable H, int key);            //插入key
void Delete(HashTable H, int key);            //删除key
void DestroyHashTable(HashTable H);           //释放一个散列表
HashTable ReHash(HashTable H);                 //再散列函数




#endif