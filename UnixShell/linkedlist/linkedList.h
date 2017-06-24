
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Node 
{
        int data;// COMMAND ID
		char *name;
        struct Node *next;
        struct Node *prev;
}Node;


/**
 * @brief The linked list structure.
 *
 * The linked list structure is an attempt to emulate what we know from
 * how we did things in java.
 *
 * @note I prefer named structures and then the typedef after the structure
 * @note In true C fashion the structures will not contain function prototypes
 * or function pointer prototypes.
 */
struct linkedlist
{
    Node * head;
    int size; // current size of list
	int maxSize; // user specified MAX SIZE OF LIST
};
typedef struct linkedlist LinkedList;

/**
 * @brief The so called "constructor" for the linked list
 *
 * The linked list constructor builds a non circular linked list that
 * contains a dummy head node.  This is meant to be similar to a Java
 * linked list constructor.
 *
 * @return LinkedList * - The linked list pointer that contains a dummy head node but is NOT circular.
 */
LinkedList * linkedList(int maxSize);

void insert(LinkedList * theList, int dataa, char * str);

char* find(LinkedList * theList, int key); // searchs linkedlist for command via ID- if found then return char* name via pass by value

void findLast(LinkedList * theList, char * strr);

void delete(LinkedList * theList, int data);

void print(LinkedList * theList);

void clearList(LinkedList * theList);

#endif // LINKEDLIST_H
