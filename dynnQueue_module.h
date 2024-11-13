#ifndef DYNNQUEUE_MODULE_H
#define DYNNQUEUE_MODULE_H

/**
 * @file dynnQueue_module.h
 * @author EM2
 * @brief 
 * @version 1.0
 * @date 2024-11-13
 * 
 * @code
    #include "dynnQueue_module.h"

    int main(int argc, char const *argv[])
    {
        dynnQueue_t *myQueue = create_dynnQueue();
        
        qData_t item[6] = {{.data.i = 7, .type = T_INT}, {.data.c = 'Q', .type = T_CHAR}, \
        {.data.f = 10.7, .type = T_FLOAT}, {.data.u8 = 254, .type = T_U8T},\
        {.data.str = "hola", .type = T_STRING},  {.data.u16 = 1024, .type = T_U16T}};

        for(int i = 0; i < 6; i++)
            myQueue->put(myQueue, item[i]);
        
        for(int i = 0; i < 6; i++)
        {
            printf("Peek: " );
            myQueue->print(myQueue->peek(myQueue));

            printf("Dequeued: " );
            myQueue->print(myQueue->pop(myQueue));
        } 
        
        return 0;
    }

    Output
    Peek: 7
    Dequeued: 7
    Peek: Q
    Dequeued: Q
    Peek: 10.70
    Dequeued: 10.70
    Peek: 254
    Dequeued: 254
    Peek: hola
    Dequeued: hola
    Peek: 1024
    Dequeued: 1024
    @endcode
 * @copyright Copyright (c) 2024
 * 
 */

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
/**
 * @brief This MACRO is the size of array type char
 * 
 */
#define SIZE_STR 10 

/** 
 * @brief This is the types enum definition for identify each item in the queue
 */
typedef enum
{
    T_INT,
    T_CHAR,
    T_FLOAT,
    T_U8T,
    T_U16T,
    T_U32T,
    T_STRING,
    T_UNSUPPORTED
}typeData_t;

/** 
 * @brief This is the union definition to create a data variable to support different data types
 */
typedef union
{
    int i;
    char c;
    float f;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    char str[SIZE_STR];
}varData_t;

/**
 * @brief This is the struct definition to define the type of item data for the queue
 * 
 */
typedef struct 
{
    /**
     * @brief this is the type of the item data
     * 
     */
    typeData_t type;

    /**
     * @brief this is the variable to allocate the value of item data
     * 
     */
    varData_t data;
}qData_t;


/**
 * @brief This is the dynamic queue typedef
 * 
 */
typedef struct dynnQueue dynnQueue_t;

/**
 * @brief This is the node queue typedef
 * 
 */
typedef struct node node_t;

/**
 * @brief This is the definition for a function pointer with Cola_t parameter and return of void type
 * 
 */
typedef void(* tf0_t)(dynnQueue_t *dynnQ);

/**
 * @brief This is the definition for a function pointer with Cola_t parameter and return of int type
 * 
 */
typedef int(* tf1_t)(dynnQueue_t *dynnQ);

/**
 * @brief This is the definition for a function pointer with Cola_t and qData_t parameters and return of int type
 * 
 */
typedef void(* tf2_t)(dynnQueue_t *dynnQ, qData_t value);

/**
 * @brief This is the definition for a function pointer with Cola_t parameter and return of qData_t type
 * 
 */
typedef qData_t(* tf3_t)(dynnQueue_t *dynnQ);

/**
 * @brief This is the definition for a function pointer with Cola_t parameter and return of void type
 * 
 */
typedef void(* tf4_t)(qData_t item);

struct node 
{
    /**
     * @brief This is the next pointed node in the queue
     * 
     */
    node_t *Next;

    /**
     * @brief This is the data item in the queue
     * 
     */
    qData_t item;
};

struct dynnQueue
{
    node_t *front;
    node_t *rear;
    /**
     * @brief Puts a new item or element in the queue
     * 
     * @param dynnQ queue instance (dynnQueue_t)
     * @param value item value (qData_t)
     * 
     */
    tf2_t put;

    /**
     * @brief pulls an item from the queue
     * 
     * @param  dynnQ queue instance (dynnQueue_t)
     * @return If the queue is empty returns a qData_t value with type T_UNSUPORTED otherwise returns the item value
     */
    tf3_t pop;
    
    /**
     * @brief Shows the last item of the queue and it does not pull the last item from the queue
     * 
     * @param  dynnQ queue instance (dynnQueue_t)
     * @return If the queue is empty returns a qData_t value with type T_UNSUPORTED otherwise returns the item value
     */
    tf3_t peek;

    /**
     * @brief print the queue item 
     * @param data item value which is printed (qData_t)
     */
    tf4_t print;

};

/**
 * @brief this function create and initializes a dynamic queue
 * 
 * @return dynnQueue_t* return a pointer to the created queue
 */
dynnQueue_t *create_dynnQueue(void);

static void _put_(dynnQueue_t *dynnQ, qData_t value);
static qData_t _pop_(dynnQueue_t *dynnQ);
static qData_t _peek_(dynnQueue_t *dynnQ);
static void _print_(qData_t data);

#endif //_DYNNQUEUE_MODULE_H 