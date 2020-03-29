// ��������ϰ����������д��붼����һ���ļ����ˣ��ú��Ӳ�Ҫѧ��Ŷ�����棩
// ʵ���˲���ͷ�ת�Լ�ɾ�����������
// ɾ���޸Ľڵ�Ȳ����޷Ǿ����ҵ����Ȼ������޸ģ��ڵ����������»��Ƿǳ��򵥵�
// �����ڴ�й©������ûʲô�õĹ��߼�⣬����ɾ�����������ܴ���Bug

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* ������������ */


// Ԫ��
typedef void * ITEM;

// ������
typedef struct _NODE{
    ITEM item;
    struct _NODE *next;
    
}NODE, *PNODE;

// ��������ĺ���
// �ⲿ�����û�����Ԫ�������Լ�����
typedef void (* TRAVERSE_FUNC)(PNODE node);
// ɾ������Զ��庯�������ڲ����ͱ�����㺯����ͬ����������Ͷ�����һ������
typedef TRAVERSE_FUNC DESTROY_FUNC;

// ����
typedef struct _LIST{
    PNODE head;
    PNODE tail;
    
    size_t item_size;
    size_t size;
}LIST, *PLIST;

// ����һ���µ�item������ԭ�ȵ�item��ֵ���ƽ���
// ���������Ƿ��Ͱ棬���Ի��鷳һ��
// static ���η��������ʾ��������ǰ�ļ���������Ҳ�������ΪJava�е�private���η�
static ITEM copy(ITEM item, size_t size){
    ITEM temp = malloc(size);
    
    for(int i=0; i<size; i++){
        // ���ݶ�����λ����Ԫ�أ�����֪��Ԫ�ص�����
        *((char *)temp + i) = *((char *)item + i);
    }
    
    return temp;
}

// �½�һ����㣬�ⲿ�ֲ����ⲿ����������static����
static PNODE create_node(ITEM item, size_t size){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    
    if(!node) return NULL;
    
    node->item = copy(item, size);
    node->next = NULL;
    
    return node;
}

//��ʼ������
void init_list(PLIST list, size_t item_size){
    list->head = list->tail = NULL;
    list->item_size = item_size;
    list->size = 0;
}

// �ж������Ƿ�Ϊ��
bool is_empty(PLIST list){
    return (list == NULL) || (list->size == 0);
}

// ��ȡ������
size_t get_size(PLIST list){
    assert(list != NULL);
    
    return list->size;
}

// ��β�˲���Ԫ��
// ����һ������ֵ���������Ƿ�ɹ�
bool insert(PLIST list, ITEM item){
    assert(list != NULL && item != NULL);
    
    PNODE node = create_node(item, list->item_size);
    
    // ��������ڴ�ʧ�ܣ�malloc�᷵��һ��NULLָ��
    if(!node) return false;
    
    // ���Ϊ�ձ���ʼ����ͷ��β
    if(is_empty(list)){
        list->head = list->tail = node;
    }else{
        // ����β����һ���ڵ����Ϊ�´����Ľڵ�
        list->tail->next = node;
        // ���±�βΪ�½ڵ�
        list->tail = node;
    }
    
    list->size++;
    
    return true;
}

// ʹ��ָ���ĺ�����������
void traverse_list(PLIST list, TRAVERSE_FUNC func){
    assert(list != NULL);

    // ���ﶨ����һ����ʱָ�룬Ŀ����Ϊ�˼�������ɾ������
    PNODE curr = list->head, temp;

    while(curr){
        temp = curr->next;
        func(curr);
        curr = temp;
    }
}

// ��ת����
// �㷨��������w
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

// ʹ���û������ɾ��������
void destroy_list(PLIST list, DESTROY_FUNC func){
    assert(list != NULL);
    
    traverse_list(list, func);
    
    // ����ԭ����ʼ��״̬
    init_list(list, list->item_size);
}

/* ������������ */


// �û��Զ����������������������ǽ���int���͵�����
void traverse_int_list(PNODE node){
    printf("%d ", *((int *)node->item));
}

// �û��Զ��������ɾ������������ɾ��int���͵�����ֱ��free������
void destroy_int_list(PNODE node){
    free(node);
}

// ���Բ�����������
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
        // ������Ҫ�ֶ������ڴ棬���ܻᵼ���ڴ�й©
        char *name;
}STU, *PSTU;

void destroy_struct_list(PNODE node){
    PSTU stu = (PSTU)node->item;
    free(stu->name); // ��free��Ϊnameָ�������ڴ�
    free(stu); // ��free��������ڴ�
}

void traverse_struct_list(PNODE node){
    PSTU stu = (PSTU)node->item;
    printf("Age %d\n", stu->age);
    printf("Score %.2f\n", stu->score);
    printf("Name %s\n", stu->name);
    putchar('\n');
}

// ���Բ���ṹ�����͵�����
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
