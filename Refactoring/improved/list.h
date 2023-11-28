#ifndef LIST_H_
#define LIST_H_

typedef struct Node{
    struct Contact* contact;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List{
    unsigned int size;
    struct Node* head;
    struct Node* last;
} List;

List* createList();
int insert(List *, Contact*);
List* fromArray(Contact*, int, int);
void deleteList(List **);
int printList(List *);
int printListSmall(List *);
int swapContact(Node*, Node*);
int inserting(List *, Contact*);
int deleteContact(List* , int);
int changeContactName(List*, int, char*);
Contact* _deleteNodeSaveCont(List*, int);
Contact* getContact(List* list, int index);
int updateIndexContact(List* list);


#endif
