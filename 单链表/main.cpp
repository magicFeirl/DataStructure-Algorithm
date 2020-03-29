// 单链表练习，简单起见所有代码都放在一个文件里了，好孩子不要学我哦（迫真）
// 实现了插入和反转以及删除链表操作，
// 删除修改节点等操作无非就是找到结点然后进行修改，在单链表的情况下还是非常简单的
// 关于内存泄漏的问题没什么好的工具检测，所以删除链表函数可能存在Bug

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* 以下是链表函数 */


// 元素
typedef void * ITEM;

// 链表结点
typedef struct _NODE{
    ITEM item;
    struct _NODE *next;
    
}NODE, *PNODE;

// 遍历链表的函数
// 这部分由用户根据元素类型自己定义
typedef void (* TRAVERSE_FUNC)(PNODE node);
// 删除结点自定义函数，由于参数和遍历结点函数相同，所以这里就定义了一个别名
typedef TRAVERSE_FUNC DESTROY_FUNC;

// 链表
typedef struct _LIST{
    PNODE head;
    PNODE tail;
    
    size_t item_size;
    size_t size;
}LIST, *PLIST;

// 创建一个新的item，并将原先的item的值复制进来
// 由于这里是泛型版，所以会麻烦一点
// static 修饰符在这里表示函数仅当前文件作用域，你也可以理解为Java中的private修饰符
static ITEM copy(ITEM item, size_t size){
    ITEM temp = malloc(size);
    
    for(int i=0; i<size; i++){
        // 根据二进制位复制元素，无需知道元素的类型
        *((char *)temp + i) = *((char *)item + i);
    }
    
    return temp;
}

// 新建一个结点，这部分不对外部开放所以用static修饰
static PNODE create_node(ITEM item, size_t size){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    
    if(!node) return NULL;
    
    node->item = copy(item, size);
    node->next = NULL;
    
    return node;
}

//初始化链表
void init_list(PLIST list, size_t item_size){
    list->head = list->tail = NULL;
    list->item_size = item_size;
    list->size = 0;
}

// 判断链表是否为空
bool is_empty(PLIST list){
    return (list == NULL) || (list->size == 0);
}

// 获取链表长度
size_t get_size(PLIST list){
    assert(list != NULL);
    
    return list->size;
}

// 在尾端插入元素
// 返回一个布尔值表明操作是否成功
bool insert(PLIST list, ITEM item){
    assert(list != NULL && item != NULL);
    
    PNODE node = create_node(item, list->item_size);
    
    // 如果分配内存失败，malloc会返回一个NULL指针
    if(!node) return false;
    
    // 如果为空表，初始化表头表尾
    if(is_empty(list)){
        list->head = list->tail = node;
    }else{
        // 将表尾的下一个节点更新为新创建的节点
        list->tail->next = node;
        // 更新表尾为新节点
        list->tail = node;
    }
    
    list->size++;
    
    return true;
}

// 使用指定的函数遍历链表
void traverse_list(PLIST list, TRAVERSE_FUNC func){
    assert(list != NULL);

    // 这里定义了一个临时指针，目的是为了兼容链表删除函数
    PNODE curr = list->head, temp;

    while(curr){
        temp = curr->next;
        func(curr);
        curr = temp;
    }
}

// 反转链表
// 算法还是忘了w
void reverse_list(PLIST list){
    assert(list != NULL);
    
    PNODE curr = list->head,
    next = curr, prev = NULL;
    
    while(next){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    list->tail = list->head;
    list->head = prev;
}

// 使用用户定义的删除链表函数
void destroy_list(PLIST list, DESTROY_FUNC func){
    assert(list != NULL);
    
    traverse_list(list, func);
    
    // 链表还原到初始化状态
    init_list(list, list->item_size);
}

/* 以上是链表函数 */


// 用户自定义的链表遍历函数，这里是解引int类型的数据
void traverse_int_list(PNODE node){
    printf("%d ", *((int *)node->item));
}

// 用户自定义的链表删除函数，这里删除int类型的数据直接free掉即可
void destroy_int_list(PNODE node){
    free(node);
}

// 测试插入整型数据
void test_int_list(){
    LIST list;
    int num = 121;
    
    init_list(&list, sizeof(int));
    
    for(int i=0; i<10; i++)
        insert(&list, &i);

    traverse_list(&list, traverse_int_list);
    putchar('\n');
    reverse_list(&list);
    insert(&list, &num);
    
    traverse_list(&list, traverse_int_list);
    destroy_list(&list, destroy_int_list);
    insert(&list, &num);
    traverse_list(&list, traverse_int_list);
}

typedef struct _STU{
        int age;
        float score;
        // 这里需要手动分配内存，可能会导致内存泄漏
        char *name;
}STU, *PSTU;

void destroy_struct_list(PNODE node){
    PSTU stu = (PSTU)node->item;
    free(stu->name); // 先free掉为name指针分配的内存
    free(stu); // 再free掉自身的内存
}

void traverse_struct_list(PNODE node){
    PSTU stu = (PSTU)node->item;
    printf("Age %d\n", stu->age);
    printf("Score %.2f\n", stu->score);
    printf("Name %s\n", stu->name);
    putchar('\n');
}

// 测试插入结构体类型的数据
void test_struct_list(){
    STU stu;
    LIST list;
    
    init_list(&list, sizeof(STU));
    
    for(int i=0; i<3; i++){
        stu.age = 24;
        stu.score = 114;
        stu.name = (char *)malloc(sizeof(char) * 20);
        strcpy(stu.name, "YJSP");
        
        insert(&list, &stu);
    }
    
    traverse_list(&list, traverse_struct_list);
    destroy_list(&list, destroy_struct_list);
    traverse_list(&list, traverse_struct_list);
}

int main(){
	printf("====== testing int list ======\n");
    test_int_list();
	printf("\n====== testing struct list ======\n");
    test_struct_list();
    printf("\n====== end ======\n");
    
    return 0;
}
