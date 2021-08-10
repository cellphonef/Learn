#include <stdlib.h> /* for malloc free */
#include <stdio.h> /* for printf */

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

typedef int ElemType;
typedef struct Node {
    ElemType value;
    struct Node* next;
}Node;

typedef struct Node* SingleLinkList;

Status InitSingleLinkList(SingleLinkList* s)
{
    *s = (SingleLinkList)malloc(sizeof(Node));
    if (!(*s))
        return ERROR;
    (*s)->next = NULL;
    return OK;
}

Status ListInsert(SingleLinkList* s, int pos, ElemType e)
{
    SingleLinkList p, newNode;
    p = *s;
    int i = 1;
    while (p && i < pos) {
        p = p->next;
        i++;
    }

    if (!p || i > pos)
        return ERROR;

    newNode = (SingleLinkList)malloc(sizeof(Node));
    newNode->value = e;
    newNode->next = p->next;
    p->next = newNode;
    return OK;
}

Status ListDelete(SingleLinkList* s, int pos, ElemType* e)
{
    SingleLinkList p, q;
    p = *s;
    int i = 1;
    while (p && i < pos) {
        p = p->next;
        i++;
    }

    if (!p || i > pos)
        return ERROR;

    q = p->next;
    p->next = q->next;
    *e = q->value;
    free(q);
    return OK;
}


Status ListTraverse(SingleLinkList s)
{
    SingleLinkList p = s->next;
    while (p) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int ListEmpty(SingleLinkList s)
{
    return s->next ? FALSE : TRUE;
}

Status ClearList(SingleLinkList* s)
{
    SingleLinkList p, q;
    p = (*s)->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    (*s)->next = NULL;
    return OK;

}



int main()
{
    SingleLinkList s;
    InitSingleLinkList(&s);
    printf("��ʼ��������s��ListEmpty(s)=%d\n", ListEmpty(s));
    printf("��ʼ��������s��ListTraverse(s)�������:\n");
    ListTraverse(s);

    for (int i = 1; i <= 5; i++)
        ListInsert(&s, i, i);

    printf("����1-5Ԫ�غ�ListEmpty(s)=%d\n", ListEmpty(s));
    printf("����1-5Ԫ�غ�ListTraverse(s)�������:\n");
    ListTraverse(s);

    int temp;
    ListDelete(&s, 1, &temp);
    printf("ɾ����һ��Ԫ�غ�ListEmpty(s)=%d\n", ListEmpty(s));
    printf("temp=%d\n", temp);
    printf("ɾ����һ��Ԫ�غ�ListTraverse(s)�������:\n");
    ListTraverse(s);

    ClearList(&s);
    printf("��������ListEmpty(s)=%d\n", ListEmpty(s));
    printf("��������ListTraverse(s)�������:\n");
    ListTraverse(s);
}