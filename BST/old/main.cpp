#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

// ���
typedef struct _NODE{
	int data;
	
	struct _NODE *parent;
	struct _NODE *left;
	struct _NODE *right;
	
}NODE, *PNODE;

// ��
typedef struct _TREE{
	PNODE root;
	
	int size;
	
}TREE, *PTREE;

bool delete_node(PTREE tree, int data);
PNODE find_min(PNODE node);

// ����Ԫ���ڲ�����
static PNODE create_node(int data, PNODE parent){
	PNODE node = (PNODE)malloc(sizeof(NODE));
	
	assert(node != NULL);
	
	node->data = data;
	node->left = node->right = NULL;
	node->parent = parent;
	
	return node;
}

// ������
void create_tree(PTREE tree, int data){
	tree->root = create_node(data, NULL);
	tree->size = 1;
}

// ����Ԫ��
void insert(PTREE tree, int data){
	assert(tree != NULL);
	
	PNODE curr = tree->root;
	
	while(curr){
		if(data > curr->data){
			if(curr->right == NULL){
				curr->right = create_node(data, curr);
				tree->size++;
			}else{
				curr = curr->right;
			}
		}else if(data < curr->data){
			if(curr->left == NULL){
				curr->left = create_node(data, curr);
				tree->size++;
			}else{
				curr = curr->left;
			}
		}else{
			break;
		}
	}
}

// ǰ�����
void preorder(PNODE root){
	if(root){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// �������
void inorder(PNODE root){
	if(root){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

// ��ȡ����С
int get_size(PTREE tree){
	assert(tree != NULL);
	
	return tree->size;
}

// �������
PNODE find(PTREE tree, int data){
	assert(tree != NULL);
	
	PNODE curr = tree->root;
	
	while(curr){
		if(data > curr->data){
			curr = curr->right;
		}else if(data < curr->data){
			curr = curr->left;
		}else{
			return curr;
		}
	}
	
	return NULL;
}

// ������
void test_tree(){
	TREE tree;
	int nums[] = {3, 7, 2, 4, 6, 8, 9},
	size = sizeof(nums) / sizeof(nums[0]);
	
	create_tree(&tree, 5);

	for(int i=0; i<size; i++){
		insert(&tree, nums[i]);
	}

	preorder(tree.root);
	printf("\n");
	inorder(tree.root);

	delete_node(&tree, 7);
	printf("\n");
	preorder(tree.root);
	printf("\n");
	inorder(tree.root);
	/*
	PNODE node = find(&tree, 1);

	if(node){
		printf("\n%d\n", node->parent->data);
	}*/
	
}


// ɾ���㷨����ûд���� 2020��4��28��16:10:27
// �����¼һ�� BST ɾ��Ԫ�ص���������Ͷ�Ӧ����
/*
	1. Ҷ�ӽ��
		ֱ��ɾ��ͬʱ���¸��ڵ�ָ��
		
	2. ֻ��һ���ӽڵ�Ľ��
		�ѵ�ǰ�ڵ��ֵ����Ϊ�ӽڵ��ֵ��ɾ���ӽڵ㣬���µ�ǰ�ڵ�ָ��
		
	3. �������ڵ�Ľڵ�
	    �ҵ���ǰ�ڵ�����������СԪ��ֵ��������ǰ�ڵ�ֵ����Ϊ�ҵ���ֵ���ݹ�ɾ��
	    
	    �õ��˶���������������
*/
bool delete_node(PTREE tree, int data){
	PNODE node = find(tree, data);
	if(!node){
		return false;
	}else{
		PNODE parent = node->parent;
		if(parent){
			// Ҷ�ӽ��
			if(!node->left && !node->right){
				if(parent->left->data == node->data){
					parent->left = NULL;
				}else{
					parent->right = NULL;
				}
				free(node);
			}else if(node->left && !node->right){
				node->data = node->left->data;
				node->left = NULL;
				free(node->left);
			}else if(!node->left && node->right){
				node->data = node->right->data;
				node->right = NULL;
				free(node->right);
			}else{
				PNODE min = find_min(node->right);
				if(min){
					node->data = min->data;
					
					// free(min);
				}
			}
		}else{
			free(node);
		}
	}
}

PNODE find_min(PNODE node){
	if(!node){
		return NULL;
	}else if(!node->left){
		return node;
	}else{
		find_min(node->left);
	}
}

int main(){
	test_tree();
	
	return 0;
}
