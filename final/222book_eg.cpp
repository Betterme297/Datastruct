#include<iostream>
#include<string.h>      
#include<stdlib.h>
#include<math.h>
using namespace std;
typedef enum{
    BITREE_NODE_LEFT = 0,
    BITREE_NODE_RIGHT = 1
}BiTreeNodeSide;
#define pi 3.14159267       //this is a test
typedef struct _BiTree BiTree;              //二叉树结构
typedef struct _BiTreeNode BiTreeNode;      //二叉树结点
typedef void * BiTreeValue;                 //二叉树中储存的数据
#define BITREE_NULL ((void *) 0)            //二叉树的空指针数据
struct _BiTreeNode{
    BiTreeNode * children[2];
    BiTreeNode * parent;
    BiTreeValue value;
};
struct _BiTree{
    BiTreeNode * rootnode;          //根节点
    int nodenum;                    //节点数目
};
string get_sub_str(char *str, int start, int len)
{
/*char* res = (char*)malloc(len + 1);
res[len] = 0;
memcpy(res, str + start - 1, len);*/
    string res(3,'\0');
    for(int i = start ;i< start+len; i++){
        res[i-start] = str[i];
    }
    //res[len] = '\0';
return res;
}
BiTreeNode *bitree_insert(BiTree *tree, BiTreeValue value,
						BiTreeNode *parent, BiTreeNodeSide side);
int create_expression_tree(BiTree * tree, BiTreeNode * parent, BiTreeNodeSide side, char *p, int l){    //构造表达式树
    int i = 0, lnum = 0, rpst1 = -1, rpst2 = -1, rpst3 = -1, pn = 0;
    //lnum记录 '(' 的未成对个数；
    //rpst1记录表达式中'*'、'/'、'%'、'^'的位置
    //rpst2记录表达式中'+'、'-'的位置
    //rpst3记录表达式中sin、cos、tan、exp的位置(最后一个字字母n\p)
    //pn记录操作数中'.'的个数，以判断输入操作数是否合法
    if(l == 0)
        return 1;
    //判断表达式是否正确
    if(*p == '+' || *p == '*' || *p == '/' || *p == '.' || *p == ')' ||*p == '%'||*p == '^'){
        //检验表达式开头的正确性
        cout<<"Wrong expression: not start with number or left bracket !"<<endl;
        return 0;
    }
    if(!(*(p+l-1) == ')' || *(p+l-1) >= '0' && *(p+l-1) <= '9')){
        //检验表达式结尾的正确性
        cout<<"Wrong expression:not end with number or right bracket!"<<endl;
        return 0;
    }
    if(*p == '(')
        lnum++;
    for(i = 1; i < l ; i++) {
        string s(3,'\0');
        if(*(p+i) == '.') {
            //检验小数点前面是否有数字
            if(!(*(p+i-1) >= '0' && *(p+i-1) <= '9')) {
                printf("Wrong expression: no number following dot(.)!\n");
                return 0;
            }
        }
        //tan、sin等运算符前面应有+ - * /等运算符或者左括号
        else if(*(p+i) == 'n' || *(p+i) == 'p' || *(p+i) == 's'){
        if(get_sub_str(p,i-2,3) == "tan" || get_sub_str(p,i-2,3) == "sin" || get_sub_str(p,i-2,3) == "cos" || get_sub_str(p,i-2,3) == "exp"){
            if(!(*(p+i-3) == '+' || *(p+i-3) == '-'||*(p+i-3) == '^'||*(p+i-3) == '*'||*(p+i-3) == '/'||*(p+i-3) == '%' || *(p+i-3) == '(' || i == 2)){
                cout<<"Wrong expression: unexpected char appears on the left of Sin/Cos!"<<endl;
            }
            //表达式合法，rspt3记录该运算符的位置
            if(lnum == 0){
                rpst3 = i;
            }
        }
        }
		else if(*(p+i) == '*' || *(p+i) == '/' || *(p+i) == '%'|| *(p+i) == '^') {
            //* / % ^运算符前面应有数字或者括号
            if(!(*(p+i-1) >= '0' && *(p+i-1) <= '9' || *(p+i-1) == ')')) {
                printf("Wrong expression: not number or right bracket on the left of (*)!\n");
                return 0;
            }
            //表达式合法，rspt1记录该运算符的位置
            if(lnum == 0)
                rpst1 = i;
        } 
		else if(*(p+i) == '(') {
            //左括号前是运算符，合法，lnum计数加1
            s = get_sub_str(p, i-3 ,3);
            if(*(p+i-1) == '+' || *(p+i-1) == '-' || *(p+i-1) == '*' || *(p+i-1) == '/' || *(p+i-1) == '%'|| *(p+i-1) == '^'|| *(p+i-1) == '(' ||
            s == "tan" || get_sub_str(p,i-3,3) == "sin" || get_sub_str(p,i-3,3) == "cos" || get_sub_str(p,i-3,3) == "exp")
                lnum++;
            else {
                printf("Wrong expression: unexpected char appears on the left of left bracket!\n");
                return 0;
            }
        } 
		else if(*(p+i) == ')') {
            //右括号前的字符合法，故括号成对，计数lunm减1
            
            if(*(p+i-1) == ')' || *(p+i-1) >= '0' && *(p+i-1) <= '9')
                lnum--;
            else {
                printf("Wrong expression: unexpected char appears on the left of right bracket!\n");
                return 0;
            }
            if(lnum < 0) {
                printf("Wrong expression: left bracket and right bracket not equal!\n");
                return 0;
            }
        } 
		else if(*(p+i) == '+' || *(p+i) == '-') {
            //+ - 运算符前面应为数字或者右括号
            if(*(p+i) == '+' && !(*(p+i-1) >= '0' && *(p+i-1) <= '9' || *(p+i-1) == ')')) {
                printf("Wrong expression: unexpected char appears on the left of (+)!\n");
                return 0;
            } 
			else if(*(p+i) == '-' && !(*(p+i-1) >= '0' && *(p+i-1) <= '9' || *(p+i-1) == ')' || *(p+i-1) == '(')) {
                printf("Wrong expression: unexpected char appears on the left of (-)!\n");
                return 0;
            }
            //若合法，则rspt2记录下该运算符的位置
            if(lnum == 0)
                rpst2 = i;
        }
    }
    //'('、')'未能完全配对，表达式输入不合法
    if(lnum != 0) {
        printf("Wrong expression: left bracket and right bracket not equal!\n");
        return 0;
    }
    if(rpst2 > -1) {    //存在正确的'+' '-'运算符，存入节点value中
        char *value = (char *)malloc(4*sizeof(char));
        strncpy(value, p+rpst2, 1);
        *(value + 1) = '\0';    //加上终止符
        BiTreeNode * newNode = bitree_insert(tree, value, parent, side);        //插入到二叉树中
        if(create_expression_tree(tree, newNode, BITREE_NODE_LEFT, p, rpst2))                       //rpst2是长度，'+'之前插入到左子树
            if(create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, p+rpst2+1, l-rpst2-1))      //'+'之后插入到右子树
                return 1;
        return 0;
    }
    /*if(rpst3 > -1){     //存在正确的sin cos运算符，存入节点value中
        char *value = (char *)malloc(4*sizeof(char));
        strncpy(value, p+rpst3-2, 3);
        *(value + 3) = '\0';
        BiTreeNode * newNode = bitree_insert(tree, value, parent, side);
        if(create_expression_tree(tree, newNode, BITREE_NODE_LEFT, p, rpst3-2)){
            if(create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, p+rpst3+1, l-rpst3-1))
                return 1;
        }
        return 0;
    }*/
    //此时表明表达式要么是一个数字，要么是整体被一对括号括起来
    if(rpst1 < 0) {     // 此时没有* / % ^等运算符
        if(*p == '(') { //此时表达式整体被括号括起来
            if(create_expression_tree(tree, parent, side, p+1, l-2))
                return 1;
            else
                return 0;
        }
		else {
            if(*(p+1) != '(') {//此时表达式是一个数字
                for(i = 0; i < l; i++) {
                    if(*(p+i) == '.')
                        pn++;
                    if(pn > 1) {
                        printf("Wrong expression: more than one dot(.) found in a number!\n");
                        return 0;
                    }
                }
                char *value = (char *)malloc((l+1)*sizeof(char));
                strncpy(value, p, l);
                *(value+l) = '\0';
                bitree_insert(tree, value, parent, side);
                return 1;
            } 
			else if(rpst3 < 0){	//此时表达式首一定是操作符'-'，其余部分被一对括号括起来
                char *value = (char *)malloc(4*sizeof(char));
                strncpy(value, p, 1);
                *(value+1) = '\0';
                BiTreeNode *newNode = bitree_insert(tree, value, parent, side);
                if(create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, p+2, l-3))
                    return 1;
                else
                    return 0;
            }
            else{
                char *value = (char *)malloc(4*sizeof(char));
                strncpy(value, p+rpst3-2, 3);
                *(value + 3) = '\0';
                BiTreeNode * newNode = bitree_insert(tree, value, parent, side);
                //if(create_expression_tree(tree, newNode, BITREE_NODE_LEFT, p, rpst3-2))
                if(create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, p+4, l-5))
                        return 1;
                return 0;
            }
        }
    } 
	else {	//表明表达式是几个因子相乘或相除而组成的
        char *value = (char *)malloc(4*sizeof(char));
        strncpy(value, p+rpst1, 1);
        *(value+1) = '\0';
        BiTreeNode *newNode = bitree_insert(tree, value, parent, side);
        if(create_expression_tree(tree, newNode, BITREE_NODE_LEFT, p, rpst1))
            if(create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, p+rpst1+1, l-rpst1-1))
                return 1;
        return 0;
    }
}  

BiTreeNode *bitree_insert(BiTree *tree, BiTreeValue value,
						BiTreeNode *parent, BiTreeNodeSide side) {
    BiTreeNode * newnode;
    if((newnode = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return NULL;
    //初始化
    newnode->children[BITREE_NODE_LEFT] = NULL;
    newnode->children[BITREE_NODE_RIGHT] = NULL;
    newnode->value = value;
    newnode->parent = parent;
    if(parent == NULL) { 
		//插入根节点
        if(tree->rootnode != NULL)
            tree->rootnode->parent = newnode;
        newnode->children[side] = tree->rootnode;
        tree->rootnode = newnode;
    } 
	else {
        if(parent->children[side] != NULL)
            parent->children[side]->parent = newnode;
        newnode->children[side] = parent->children[side];
        parent->children[side] = newnode;
    }
    tree->nodenum++;
    return newnode;
}
int calculate(BiTreeNode *node, double *rst) {
    double l = 0, r = 0;//l,r分别存放左右子树所代表的子表达式的值
    if(!node) {
		*rst = 0;
		return 1;
	}
    if(node->children[BITREE_NODE_LEFT] == NULL && node->children[BITREE_NODE_RIGHT] == NULL) {
		*rst = atof( (char *)node->value);
		return 1;
	} 
	else {
	    //先计算左子树和右子树
        if(calculate(node->children[BITREE_NODE_LEFT], &l))
            if(calculate(node->children[BITREE_NODE_RIGHT], &r)) {
                switch(((char *)node->value)[0]) {
                    case '+' :
						*rst = l+r;
						break;
                    case '-' :
						*rst = l-r;
						break;
                    case '*' :
						*rst = l*r;
						break;
                    case '%' :
                        *rst = fmod(l,r);
                        break;
                    case 'c':
                        *rst = cos(r/180.0*pi);
                        break;
                    case 's':
                        *rst = sin(r/180.0*pi);
                        break;
                    case '^' :
                        *rst = pow(l,r);
                        break;
                    case '/' :
						if(r == 0) {
							printf("Divided by 0!\n");	//error，除数为0
							return 0;
						} 
						else {
							*rst = l/r;
							break;
						}
                    default :
						return 0;
                }
                return 1;
            }
        return 0;
    }
}
int in_order_print(BiTreeNode *node) {      //将表达式树按照中序输出
    if(node) {
        if(in_order_print(node->children[BITREE_NODE_LEFT])) {
            printf("%s ", node->value);
            if(in_order_print(node->children[BITREE_NODE_RIGHT]))
				return 1;
            return 0;
        }
        return 0;
    }
    return 1;
}

BiTree * bitree_new() {
    BiTree *newtree;
    newtree = (BiTree *) malloc(sizeof(BiTree));
    if (newtree == NULL)
        return NULL;
    newtree->rootnode = NULL;
    newtree->nodenum = 0;
    return newtree;
}
int do_expression_calculate(char *exp, double *rst) {
    int l = strlen(exp);
    //修改sin cos等。。。。。
    BiTree *tree = bitree_new();
    create_expression_tree(tree, tree->rootnode, BITREE_NODE_LEFT, exp, l);
    in_order_print(tree->rootnode);
    cout<<endl;
    calculate(tree->rootnode, rst);
    //post_order_free(tree->rootnode);
    //bitree_free(tree);
}
/*int post_order_free(BiTreeNode *node) {         //销毁表达式树
    if(node) {
        if(post_order_free(node->children[BITREE_NODE_LEFT])) {
            if(post_order_free(node->children[BITREE_NODE_RIGHT])) {
                free(node->value);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 1;
}*/
int main(){
    char exp3[] = "-2+3/1.5-(10*3)+40%2";
    char exp4[] = "-(3+4*5)+1*2.5";
    char exp5[] = "sin(60)";
    double rst1,rst2,rst3;
    do_expression_calculate(exp3, &rst1);
    do_expression_calculate(exp4, &rst2);
    do_expression_calculate(exp5, &rst3);
    cout<<rst1<<endl<<rst2<<endl<<rst3<<endl;
    return 0;
}
