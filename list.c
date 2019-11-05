#include <stdlib.h>
#include <stddef.h>
#include "list.h"

static void freeNodes(ListNode *node, FreeFunc freeFunc);

static void nop(void *data);

static void nop(void *data)
{
  //non-free
}

void List_reverse(List *list)
{ //may be a faster way to do this which doesn't require nop
  List *temp = List_init();
  ListNode *iter = list->head;

  while(iter != NULL)
  {
    List_append(temp, ListNode_iterate(iter));
  }

  List_free(list, &nop); //do not destroy data, only structure

  list = temp;
}

unsigned int List_length(List *list)
{
  unsigned int length = 0;
  ListNode *iter = list->head;

  while(iter != NULL)
  {
    iter = iter->next;
    length++;
  }

  return length;
}

int List_isEmpty(List *list)
{
  return list->head == NULL;
}

unsigned int List_toArray(List *list, void **array)
{
  ListNode *iter;
  unsigned int i = 0;
  unsigned int len = List_length(list);

  if(len == 0)
  {
    return 0;
  }

  array = malloc(sizeof(void*)*len);
  iter = list->head;

  while(iter != NULL)
  {
    array[i] = ListNode_iterate(iter);
  }

  return len;
}

void* ListNode_iterate(ListNode *node)
{
  void *temp = node->data;
  node = node->next;

  return temp;
}

void List_free(List *list, FreeFunc freeFunc)
{ //wrapper to recursive freeNodes()
  freeNodes(list->head, freeFunc);
}

static void freeNodes(ListNode *node, FreeFunc freeFunc)
{
  if(node->next != NULL)
    freeNodes(node->next, freeFunc);

  if(node->data != NULL)
    (*freeFunc)(node->data);

  free(node);
}

//linkedness and endedness specific functions beyond here

#ifdef List_DENDED
//double-ended generic

List* List_init()
{
  List *list;
  list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

#ifdef List_DLINKED
//double-ended, double-linked

void List_attach(List *list, List *tailList)
{ //attaches tail to list, does not destroy tail but is not a copy
  tailList->head->prev = list->tail;
  list->tail->next = tailList->head;
  list->tail = tailList->tail;
}

void List_insert(List *list, void *data)
{
  ListNode *node = ListNode_initNode(void *data);
  node->next = list->head;
  list->head = node;
  node->next->prev = node;

  if(list->tail == NULL)
  {
    list->tail = node;
  }
}

void List_append(List *list, void *data)
{
  list->tail->next = ListNode_initNode(data);

  list->tail->next->prev = list->tail;
  list->tail = list->tail->next;
}

#else
//double-ended, single-linked

void List_attach(List *list, List *tailList)
{ //attaches tail to list, does not destroy tail but is not a copy
  list->tail->next = tailList->head;
  list->tail = tailList->tail;
}

void List_append(List *list, void *data)
{
  list->tail->next = ListNode_initNode(data);

  list->tail = list->tail->next;
}

void List_insert(List *list, void *data)
{
  ListNode *node = ListNode_initNode(void *data);
  node->next = list->head;
  list->head = node;

  if(list->tail == NULL)
  {
    list->tail = node;
  }
}

#endif
#else
//single-ended generic

List* List_init()
{
  List *list;
  list = malloc(sizeof(List));
  list->head = NULL;

  return list;
}

#ifdef List_DLINKED
//single-ended, double-linked

void List_append(List *list, void *data)
{
  if(list->head == NULL)
  {
    list->head = ListNode_initNode(data);
  }
  else
  {
    ListNode *iter = list->head;

    while(iter->next != NULL)
    {
      iter = iter->next;
    }

    iter->next = ListNode_initNode(data);
    iter->next->prev = iter;
  }
}

void List_attach(List *list, List *tailList)
{ //attaches tail to list, does not destroy tail but is not a copy
  ListNode *iter = list->head;

  while(iter->next != NULL)
  {
    iter = iter->next;
  }

  iter->next = tailList->head;
  tailList->head->prev = iter;
}

void List_insert(List *list, void *data)
{
  ListNode *node = ListNode_initNode(data);
  node->next = list->head;
  list->head = node;
  node->next->prev = node;
}

#else
//single-ended, single-linked

void List_append(List *list, void *data)
{
  if(list->head == NULL)
  {
    list->head = ListNode_initNode(data);
  }
  else
  {
    ListNode *iter = list->head;

    while(iter->next != NULL)
    {
      iter = iter->next;
    }

    iter->next = ListNode_initNode(data);
  }
}

void List_attach(List *list, List *tailList)
{ //attaches tail to list, does not destroy tail but is not a copy
  ListNode *iter = list->head;

  while(iter->next != NULL)
  {
    iter = iter->next;
  }

  iter->next = tailList->head;
}

void List_insert(List *list, void *data)
{
  ListNode *node = ListNode_initNode(data);
  node->next = list->head;
  list->head = node;
}

#endif
#endif
#ifdef List_DLINKED
//double-linked generic

ListNode* ListNode_initNode(void *data)
{
  ListNode *node = malloc(sizeof(ListNode));
  node->next = NULL;
  node->prev = NULL;

  return node;
}

#else
//single-linked generic

ListNode* ListNode_initNode(void *data)
{
  ListNode *node = malloc(sizeof(ListNode));
  node->next = NULL;

  return node;
}

#endif
