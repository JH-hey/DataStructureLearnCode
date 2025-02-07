#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct Node
{
    /* 结构体的第一个数据项为int类型的data */
    int data;
    /* 结构体的第二个数据项为指针，存储的地址是下一个结构体的地址 */
    struct Node *next;
} Node;

// 创建头结点，头指针L，并返回头指针
Node *inilist() /* 由于要返回头指针，因此函数的类型为"Node *" */
{
    /* 为头节点分配空间，并把头节点的地址给头指针L */
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = NULL;
    return L; // 返回头指针
}
// 头插法：不需要额外指针
void headinsert(Node *L, int data)
{
    /* 新建一个结构体，存储要插入的数据 */
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 进行插入 */
    node->next = L->next;
    L->next = node;
    /* 链表的个数增加1 */
    L->data++;
}
// 尾插法：需要一个指针找到最后一个结点
void tailinsert(Node *L, int data)
{
    // 新建指针p，用来寻找最后一个结点
    Node *p = L;
    for (int i = 0; i < L->data; i++)
    {
        p = p->next;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    /* 进行插入，尾结点连接到新建结点前面，尾指针再变成指向新建结点 */
    p->next = node;
    p = node;
    L->data++;
}
/*删除操作，此时需要三个指针。
一个指针指向当前需要“被删除的结点”，另一个指针指向“被删除结点”前的结点
由于指向"被删除结点"的指针也要继续往后移动，所以再需要一个指针来帮他脱身。
*/
int deletelist(Node *L, int data)
{
    Node *pre = L;        // pre指向“被删除结点”的前一个结点
    Node *node = L->next; // node指向“被删除的结点”
    while (node)          // 遍历结点
    {
        if (node->data == data)
        {
            Node *q = node;      // 新建结点，指向目标结点，进行帮助node指针脱身
            pre->next = q->next; // “被删除结点”前的结点重新建立关系
            node = q->next;      // 指针node脱身
            free(q);             // 在新建指针的帮助下，删除目标结点
            L->data--;
        }
        else // 如果没有遇到删除情况时，指针移动采用此方式
        {
            pre = node;
            node = node->next;
        }
    }
    // 验证是否删除干净
    Node *p = L; // 新建指针，进行遍历
    for (int i = 0; i < L->data; i++)
    {
        p = p->next;
        if (p->data == data)
        {
            return FALSE; // 一旦遇到目标数据，则没删干净，立即退出，返回FALSE值
        }
    }

    return TRUE; // 返回TRUE说明删除完毕
}

void printList(Node *L)
{
    Node *node = L->next;
    while (node)
    {
        printf("node=%d\n", node->data);
        node = node->next;
    }
}
int main()
{
    Node *L = inilist();
    headinsert(L, 3);
    headinsert(L, 2);
    headinsert(L, 1);
    tailinsert(L, 3);
    tailinsert(L, 5);
    tailinsert(L, 6);
    tailinsert(L, 7);
    tailinsert(L, 8);
    tailinsert(L, 7);
    tailinsert(L, 9);
    tailinsert(L, 10);
    printList(L);

    if (deletelist(L, 3))
    {
        printf("delete success\n");
    }
    else
    {
        printf("ERROR\n");
    }
    printList(L);

    if (deletelist(L, 7))
    {
        printf("delete success\n");
    }
    else
    {
        printf("ERROR\n");
    }
    printList(L);
    return 0;
}