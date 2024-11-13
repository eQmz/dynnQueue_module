#include "dynnQueue_module.h"

dynnQueue_t *create_dynnQueue(void)
{
    dynnQueue_t *dynnQ = (dynnQueue_t * )malloc(sizeof(dynnQueue_t));
    dynnQ->front = dynnQ->rear = NULL;
    dynnQ->put = _put_;
    dynnQ->pop = _pop_;
    dynnQ->peek = _peek_;
    dynnQ->print = _print_;
    return dynnQ;
}

static void _print_(qData_t data)
{
    //printf("dequeue: ");
    switch (data.type)
    {
    case T_INT:
        printf("%d\n", data.data.i);
        break;

    case T_CHAR:
        printf("%c\n", data.data.c);
        break;

    case T_FLOAT:
        printf("%.2f\n", data.data.f);
        break;

    case T_U8T:
        printf("%d\n", data.data.u8);
        break;

     case T_U16T:
        printf("%ld\n", data.data.u16);
        break;

    case T_U32T:
        printf("%ld\n", data.data.u32);
        break;

    case T_STRING:
        printf("%s\n", data.data.str);
        break;
    
    default:
        printf("UNSUPPORTED\n");
        break;
    }
}

static void _put_(dynnQueue_t *dynnQ, qData_t value)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));

    if(new == NULL)
    {
        printf("\033[31mThere is no enough memory!\033[0m\n");
        return;
    }

    new->item = value;
    new->Next = NULL;

    if(dynnQ->rear == NULL)
        dynnQ->front = dynnQ->rear = new;
    
    dynnQ->rear->Next = new; 
    dynnQ->rear = new;
}

static qData_t _pop_(dynnQueue_t *dynnQ)
{
    qData_t auxItem = {.data.str = {'\0'}, .type = T_UNSUPPORTED};

    if(dynnQ->front == 0)
        return auxItem;

    auxItem = dynnQ->front->item;
    node_t *auxNode = dynnQ->front;

    dynnQ->front = dynnQ->front->Next;

    if(dynnQ->front== NULL)
        dynnQ->rear = NULL;


    free(auxNode);

    return auxItem;
}

static qData_t _peek_(dynnQueue_t *dynnQ)
{
    qData_t auxItem = {.data.str = {'\0'}, .type = T_UNSUPPORTED};

    if(dynnQ->front == 0)
        return auxItem;

    auxItem = dynnQ->front->item;

    return auxItem;
}

