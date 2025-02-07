#include <stdio.h>
#include <stdlib.h>
/* 定义树结点 */
typedef struct Tree
{
    struct Tree *lchild;
    char data;
    struct Tree *rchild;
} Tree;
/* 定义栈结点 */
typedef struct Stack
{
    Tree *data; /* 结点的前面指向->压入栈内的树结点，因为不可能把整个树结点压入，故采用指针指向树结点 */
    struct Stack *next;
} Stack;
/* 初始化树,最后返回树的头指针。需注意，树头指针直接指向第一个结点，无头结点*/
Tree *initTree()
{
    Tree *T = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->data = ch;
        T->lchild = initTree();
        T->rchild = initTree();
    }
    else
    {
        T = NULL;
    }
    return T;
}
/* 建立栈,栈的头指针指向头结点，具有头结点 */
Stack *initStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack)); /* 头指针和头结点已出现 */
    S->data = NULL;                            /* 头结点的data没有指向任何树结点 */
    S->next = NULL;
    return S;
}

/* 入栈。参数为 1：指向树结点的指针，要压入栈的树结点。2：传入栈的头指针 */
void push(Tree *treenode, Stack *S)
{
    Stack *node = (Stack *)malloc(sizeof(Stack)); /* 新生栈结点 */
    node->data = treenode;
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
/* 出栈。要返回整个栈结点，因此要返回指向栈结点的指针，要出栈的栈结点 */
Stack *pop(Stack *S)
{
    if (isEmpty(S))
    {
        return NULL; /* 栈为空，则没啥返回的 */
    }
    else
    {
        Stack *node = S->next; /* 新建指向栈结点的指针，指向要出栈的栈结点 */
        S->next = node->next;
        return node;
    }
}

/* 前序遍历 */
void preOrder(Tree *T)
{
    Tree *node = T;             /* 因为要对树结点进行操作，就需要一个指向树结点的指针。因为头指针不能动，故需要重新接受一下 */
    Stack *S = initStack();     /* 遍历的时候才需要建立栈 */
    while (node || !isEmpty(S)) /* 当不是最后一个树结点时候，进行遍历。而访问最后一个树结点的特点是：结点为空且当前栈也为空 */
    {
        if (node)
        {
            printf("%c ", node->data);
            push(node, S);       /* 压入栈内 */
            node = node->lchild; /* 有则进，且下一个被访问的是：进来的树结点的左结点 */
        }
        else
        {
            /* 下一个被访问是:出去的树结点的右结点 */
            /* 这里因为写node=pop(S)->data容易报错,故这里多写了两行 */
            Stack *p = pop(S);   /* 接受弹出来的栈结点 */
            node = p->data;      /* 指向出去的树结点 */
            node = node->rchild; /* 指向出去的树结点的右边结点 */
        }
    }
}

/* 中序遍历——与前序遍历相同，只不过是在弹出栈的时候，进行打印 */
void inOrder(Tree *T)
{
    Tree *node = T;             /* 因为要对树结点进行操作，就需要一个指向树结点的指针。因为头指针不能动，故需要重新接受一下 */
    Stack *S = initStack();     /* 遍历的时候才需要建立栈 */
    while (node || !isEmpty(S)) /* 当不是最后一个树结点时候，进行遍历。而访问最后一个树结点的特点是：结点为空且当前栈也为空 */
    {
        if (node)
        {
            /*  printf("%c ", node->data); */
            push(node, S);       /* 压入栈内 */
            node = node->lchild; /* 有则进，且下一个被访问的是：进来的树结点的左结点 */
        }
        else
        {
            /* 下一个被访问是:出去的树结点的右结点 */
            /* 这里因为写node=pop(S)->data容易报错,故这里多写了两行 */
            Stack *p = pop(S); /* 接受弹出来的栈结点 */
            node = p->data;    /* 指向出去的树结点 */
            printf("%c ", node->data);
            node = node->rchild; /* 指向出去的树结点的右边结点 */
        }
    }
}
int main()
{
    Tree *T = initTree();
    printf("前序遍历结果是:\n");
    preOrder(T);
    printf("\n");
    printf("中序遍历结果是:\n");
    inOrder(T);
}
