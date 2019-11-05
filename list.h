#ifndef LIST
#define LIST

#ifdef List_DLINKED
typedef struct ListNode
{
  struct ListNode *next;
  struct ListNode *prev;
  void *data;
} ListNode;
#else
typedef struct ListNode
{
  struct ListNode *next;
  void *data;
} ListNode;
#endif

#ifdef List_DENDED
typedef struct List
{
  struct ListNode *head;
  struct ListNode *tail;
} List;
#else
typedef struct List
{
  struct ListNode *head;
  struct ListNode *tail;
} List;
#endif

typedef void(*FreeFunc)(void*);

//list fuctions
void List_reverse(List *list);

unsigned int List_length(List *list);

int List_isEmpty(List *list);

unsigned int List_toArray(List *list, void **array);

void List_free(List *list, FreeFunc freeFunc);

void List_attach(List *list, List *tailList);

List* List_init();

void List_insert(List *list, void *data);

void List_append(List *list, void *data);

//node functions
void* ListNode_iterate(ListNode *node);

ListNode* ListNode_initNode(void *data);

#endif
