#include <stdio.h>
#include <stdlib.h>
typedef struct Tree
{
    struct Tree *lchild;
    char data;
    struct Tree *rchild;
    int flag; /* flag用来标记此树结点是否执行了被弹出操作 */
} Tree;

typedef struct Stack
{
    Tree *data;
    struct Stack *next;
} Stack;

/* 初始化树 */
Tree *initTree()
{
    Tree *T = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->data = ch;
        T->flag = 0;            /* 初始化为0 */
        T->lchild = initTree(); /* 去创立左边的根节点 */
        T->rchild = initTree(); /* 去创立右边的根结点 */
    }
    else
    {
        T = NULL;
    }
    return T;
}
/* 初始化栈 */
Stack *initStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->data = NULL;
    S->next = NULL;
    return S;
}

/* 入栈,头插法 */
void push(Tree *T, Stack *S)
{
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->data = T;
    node->next = S->next;
    S->next = node;
}
/* 判断栈是否为空 */
int isEmpty(Stack *S)
{
    if (S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/* 出栈,返回栈结点 */
Stack *pop(Stack *S)
{
    if (isEmpty(S))
    {
        return NULL;
    }
    else
    {
        Stack *node = S->next;
        S->next = node->next;
        return node;
    }
}
/* 取栈顶元素 */
Stack *gettop(Stack *S)
{
    if (isEmpty(S))
    {
        return NULL;
    }
    else
    {
        Stack *node = S->next;
        return node;
    }
}

/* 后序遍历 */
void PostOrder(Tree *T)
{
    Tree *node = T; /* 这里的node代表的是要入栈的node。每一个进栈的结点，在接下来操作就是根节点 */
    Stack *S = initStack();
    while (node || !isEmpty(S)) /* 当node为#且栈为空，说明没有要入栈的了，说明都遍历完了 */
    {
        /* 先一路向左走，先让左边的都入栈 ，直到到达尽头*/
        if (node)
        {
            push(node, S);
            node = node->lchild;
        }
        else /* 当左孩子没了，说明要出栈了。但是后序遍历的不同在于出栈前要判断栈顶结点的右孩子情况。符合情况则一直出栈，直到右孩子的情况符合进栈 */
        {
            Tree *top = gettop(S)->data; /* 拿到栈顶的结点所指向的树结点，便于操作 */
            /* 接下来就要判断栈顶结点的右孩子情况 */
            if (top->rchild && top->rchild->flag == 0) /* 栈顶结点所指向的树结点的右孩子存在且flag为0（没有被弹出去过） */
            {
                top = top->rchild;  /* 让top指针指向新的栈顶，即原先栈顶的右节点 */
                push(top, S);       /* 让此右结点进栈。*/
                node = top->lchild; /* 接着，此右节点作为根节点进行左找  */
            }
            else /* 右节点没有或者右节点被弹出去过，这就是栈顶结点弹出的条件 */
            {
                top = pop(S)->data;
                printf("%c", top->data);
                top->flag = 1; /* 被弹出了，就需要标记falg */
            }
        }
    }
}

int main()
{
    Tree *T = initTree();
    PostOrder(T);
    return 0;
}