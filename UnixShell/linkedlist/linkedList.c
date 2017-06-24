#include "linkedList.h"


LinkedList * linkedList(int mSize)
{
	LinkedList * list = (LinkedList *)malloc(sizeof(LinkedList));
	list->head = (Node *)malloc(sizeof(Node));
	list->head->next = NULL;
	list->head->prev = NULL;
	list->size = 0;
	list->maxSize = mSize;
	return list;
}
void insert(LinkedList * theList, int dataa, char * str)
{
		Node * nn = (Node*)malloc(sizeof(Node));
		nn -> name = (char*)malloc(sizeof(char*));
		strcpy(nn->name,str);
		nn -> data = dataa;
		
		if(theList->head->next == NULL)
		{
			theList->head->next = nn;
			nn->prev = theList->head;
			nn->next = NULL;
		}
		else {
			Node * temp;
			temp = theList->head->next;
			
			while(temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = nn;
			nn->prev = temp;
			nn->next = NULL;
			theList->size++;
		}
		return;
}
char* find(LinkedList * theList, int key) // searchs linkedlist for command via ID- if found then return char* name via pass by value
{
        Node *pointer = theList->head->next; //First node is dummy node.
		char * str;
        /* Iterate through the entire linked list and search for the key. */
        while(pointer!=NULL)
        {
                if(pointer->data == key) //key is found.
                {
						strcpy(str,pointer->name);
                        return str;
                }
                pointer = pointer -> next;//Search in the next node.
        }
        /*Key is not found */
        str = NULL;
		return str;
}

void findLast(LinkedList * theList, char * strr)
{
	Node *pointer = theList->head->next;
	char * str = "";
	
	while(pointer -> next != NULL)
	{
		pointer = pointer->next;		
	}
	
	
	if(pointer->name != NULL)
	{
		strcpy(strr,pointer->name);
	}
	
	
	
	
	
}


void delete(LinkedList * theList, int data)
{
		Node * pointer = theList->head->next;
        /* Go to the node for which the node next to it has to be deleted */
        while(pointer->next!=NULL && (pointer->next)->data != data)
        {
                pointer = pointer -> next;
        }
        if(pointer->next==NULL)
        {
                printf("Element %d is not present in the list\n",data);
                return;
        }
        /* Now pointer points to a node and the node next to it has to be removed */
        Node *temp;
        temp = pointer -> next;
        /*temp points to the node which has to be removed*/
        pointer->next = temp->next;
        temp->prev =  pointer;
        /*We removed the node which is next to the pointer (which is also temp) */
        free(temp);
		theList->size--;
        /* Beacuse we deleted the node, we no longer require the memory used for it . 
           free() will deallocate the memory.
         */
        return;
}
void print(LinkedList * theList)
{
	Node * temp;
	if(theList->head->next != NULL)
	{
		temp = theList->head->next;
		while(temp != NULL)
		{
			printf("%d ", temp->data);
			printf(" %s \n",temp->name);
			
			temp = temp->next;
		}
	}
}



void clearList(LinkedList * theList)
{
	Node * temp;
	Node * cur;
	temp = theList->head->next;

	while(temp != NULL)
	{
		Node * cur = temp;
		temp = temp->next;
		free(cur->name);
		free(cur);
	}
	free(theList->head);
}




