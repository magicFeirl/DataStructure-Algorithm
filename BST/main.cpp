// û�㶮���������д����򵥵� BST
// 2020��6��26��14:15:27

// ��������ǰ�ο����˲��͵Ĵ��룬�����Լ�д���ˡ�����
// 2020��6��26��15:43:36 ���������Ѿ��Ĺ����ˡ�
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int TREE_DATA;

typedef struct _NODE{
    TREE_DATA val;
    struct _NODE *left;
    struct _NODE *right;
    struct _NODE *parent;
}NODE, *PNODE;

typedef void (*TVE_FUNC)(PNODE);

typedef struct _TREE{
    int size;
    
    PNODE root;
}TREE, *PTREE;

void init_tree(PTREE tree){
    tree->size = 0;
    tree->root = NULL;
}

static PNODE create_node(TREE_DATA val){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    
    if(!node){
        return NULL;
    }
    
    node->val = val;
    node->right = node->left = node->parent = NULL;
    
    return node;
}
// ��
int insert(PTREE tree, TREE_DATA val){
    PNODE node = create_node(val);
    
    if(!node){
        return 0;
    }
    
    if(!tree->root){
        tree->root = node;
    }else{
        PNODE curr_node = tree->root;
        while(curr_node){
            TREE_DATA curr_val = curr_node->val;
            
            if(curr_val > val){
                if(!curr_node->left){
                    curr_node->left = node;
                    curr_node->left->parent = curr_node;
                }else{
                    curr_node = curr_node->left;
                }
            }else if(curr_val < val){
                if(!curr_node->right){
                    curr_node->right = node;
                    curr_node->right->parent = curr_node;
                }else{
                    curr_node = curr_node->right;
                }
            }else{
                return 0;
            }
        }
    }
    
    tree->size++;
    
    return 1;
}

// ��
PNODE find_node(PNODE node, TREE_DATA val){
    while(node){
        TREE_DATA curr_val = node->val;

        if(curr_val > val){
            node = node->left;
        }else if(curr_val < val){
            node = node->right;
        }else{
            return node;
        }
    }
    
    return NULL;
}

// �ҵ���С���
PNODE find_min(PNODE node){
    // ��ǰ����д���� node���������������ǰ�ڵ�ֻ��һ���ҽڵ��û���ӽڵ�Ļ��ᵼ�·��ص���ڵ�Ϊ NULL
    // ��ʵ����������������µĽ��Ӧ��������
    while(node->left){ 
        node = node->left;
    }
    
    return node;
}

// ɾ
// �ο���https://blog.csdn.net/isea533/article/details/80345507
void delete_node(PTREE tree, TREE_DATA val){
    // ���ҵ�Ҫɾ���Ľ��
    PNODE node = find_node(tree->root, val); 
    
    if(!node){
        return ;
    }
    
    // ���Ҫɾ���Ľ���������ӽڵ�
    // �����������������Ҫת����ֻ��һ���ӽڵ�����������̽ڵ����ֻ������һ���ڵ㣬���Կ��Կ�����
    // ��̽ڵ��ֵ���浱ǰ�ڵ��ֵͬʱ����ǰ�ڵ�ָ���̽ڵ�
    if(node->right && node->left){
        // ��Ҫɾ���Ľڵ���ҽڵ㿪ʼ����С��㣬ֻ���������ӽڵ�ʱ�Ż��õ�
        // ��ǰ����д�� node �ˣ����������д�Ļ����صĽ����ܻ������ҪС����ڵ����Ǳȸ��ڵ�С��
        // �������ǵ��������ҵ�Ҫɾ���Ľڵ�ĺ�̣��ȸýڵ�����С��㣩���������д�� node �Ļ����Ǵ��
        // 0 1 2 3 => 0 �ĺ�̾��� 1
        PNODE min_node = find_min(node->right);
        node->val = min_node->val; // �ѽ��ֵ�滻Ϊ��̵�ֵ��ɾ���˵�ǰ�Ľ��ֵ��
        node = min_node; // �ѵ�ǰ�ڵ�ָ���̣���һ�����������ӽڵ������º���Ҫ
    }
    
    // ���ܺ�̽ڵ���û���ӽڵ㣬����
    PNODE child_node = node->left;
    
    if(node->right){
        child_node = node->right;
    }
    
    // ���������ӽڵ㣬��ô�Ѻ�̵��ӽڵ�ĸ��ڵ��Ϊ��̽ڵ�ĸ��ڵ㣬��Ϊ�Ժ����Ǿͻ�ɾ����̽ڵ�
    if(child_node){
        child_node->parent = node->parent;
    }

    // �����̽ڵ�û�и��ڵ㣬Ҳ���Ǹ��ڵ���������ô�����ĸ��ڵ����Ϊ�ӽڵ㣨������û�У�
    if(!node->parent){
        tree->root = child_node;
    // �����жϺ�������ӻ����Һ��ӣ������ڵ���ӽڵ������Ӧ��ϵ����
    }else if(node->parent->left == node){ 
        node->parent->left = child_node;
    }else{
        node->parent->right = child_node;
    }
    
    free(node); // ɾ����ǰ�ڵ㣬�����ڴ�й©
    tree->size--; // ���Ĵ�С��һ
}

void preorder(PNODE node, TVE_FUNC func){
    if(node){
        func(node);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

void inorder(PNODE node, TVE_FUNC func){
    if(node){
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
    }
}

void prt_node_val(PNODE node){
    printf("%d ", node->val);
}

int main(){
    TREE tree;
    TREE_DATA data[] = {1, 0, 3, 5, 6, 10, 9, 8, 7, 13},
     size = sizeof(data) / sizeof(data[0]);
    
    init_tree(&tree);
    
    for(int i=0; i<size; i++){
        insert(&tree, data[i]);
    }
    
    //delete_node(&tree, 10);
    //delete_node(&tree, 11);
    delete_node(&tree, 3);
    //delete_node(&tree, 1);
    preorder(tree.root, prt_node_val);
    printf("\n");
    inorder(tree.root, prt_node_val);
    printf("\n");
    printf("find value 6: %p", find_node(tree.root, 6));
    printf("\n");
    
    return 0;
}
