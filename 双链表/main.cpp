#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef char DATA;

typedef void (*TVE_FUNC)(DATA);

typedef struct _NODE{
	DATA data;
	
	struct _NODE *next;
	struct _NODE *prev;
}NODE, *PNODE;

typedef struct _LIST{
	int size;
	
	PNODE head;
	PNODE tail;
}LIST, *PLIST;


void init_list(PLIST list){
	list->size = 0;
	list->head = list->tail = NULL;
}

static PNODE create_node(DATA data){
	PNODE node = (PNODE)malloc(sizeof(NODE));
	
	assert(node);
	
	node->data = data;
	node->prev = node->next = NULL;
	
	return node;
}

int empty(PLIST list){
	return !list->size;
}

void insert(PLIST list, DATA data){
	assert(list);
	
	PNODE node = create_node(data);
	
	if(empty(list)){
		list->head = list->tail = node;
		list->head->prev = NULL; // 非循环双链表
		// 其实这里head和tail的地址是相等的，而且prev指针已经默认为NULL了
		// 不过写出来看得清楚些
		list->tail->prev = NULL; 
	}else{
		PNODE prev = list->tail;
		list->tail->next = node;
		list->tail = node;
		list->tail->prev = prev;
	}
	
	list->size++;
}

void traverse_list(PLIST list, TVE_FUNC func){
	assert(list);
	PNODE curr = list->head;
	
	while(curr){
		func(curr->data);
		curr = curr->next;
	}
}

void re_traverse_list(PLIST list, TVE_FUNC func){
	assert(list);
	PNODE curr = list->tail;
	
	while(curr){
		func(curr->data);
		curr = curr->prev;
	}
}

void prt_data(DATA data){
	printf("%c ", data);
}

void test_list(){
	LIST list;
	init_list(&list);
	
	for(int i='A'; i<='Z'; i++){
		insert(&list, i);
	}
	
	traverse_list(&list, prt_data);
	puts("");
	re_traverse_list(&list, prt_data);
}

int judgeStr(){
	LIST list;
	init_list(&list);
	
	char str[] = "ABCBAD";
	int len = strlen(str);
	
	for(int i=0; i<len; i++){
		insert(&list, str[i]);
	}
	
	PNODE head = list.head, tail = list.tail;
	
	if(head == tail){
		return 1;
	}
	
	while(head != tail){
		DATA hd = head->data, td = tail->data;
		
		if(hd != td){
			return 0;
		}
		
		head = head->next;
		tail = tail->prev;
	}
	
	return 1;
}

int main(){
	printf("%d", judgeStr());
	
	return 0;
}
