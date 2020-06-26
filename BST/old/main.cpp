#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

// 结点
typedef struct _NODE{
	int data;
	
	struct _NODE *parent;
	struct _NODE *left;
	struct _NODE *right;
	
}NODE, *PNODE;

// 树
typedef struct _TREE{
	PNODE root;
	
	int size;
	
}TREE, *PTREE;

bool delete_node(PTREE tree, int data);
PNODE find_min(PNODE node);

// 创建元素内部函数
static PNODE create_node(int data, PNODE parent){
	PNODE node = (PNODE)malloc(sizeof(NODE));
	
	assert(node != NULL);
	
	node->data = data;
	node->left = node->right = NULL;
	node->parent = parent;
	
	return node;
}

// 创建树
void create_tree(PTREE tree, int data){
	tree->root = create_node(data, NULL);
	tree->size = 1;
}

// 插入元素
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

// 前序遍历
void preorder(PNODE root){
	if(root){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// 中序遍历
void inorder(PNODE root){
	if(root){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

// 获取树大小
int get_size(PTREE tree){
	assert(tree != NULL);
	
	return tree->size;
}

// 搜索结点
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

// 测试树
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


// 删除算法还是没写出来 2020年4月28日16:10:27
// 这里记录一下 BST 删除元素的三种情况和对应方法
/*
	1. 叶子结点
		直接删，同时更新父节点指针
		
	2. 只有一个子节点的结点
		把当前节点的值更新为子节点的值，删除子节点，更新当前节点指针
		
	3. 有两个节点的节点
	    找到当前节点右子树的最小元素值，并将当前节点值更新为找到的值，递归删除
	    
	    用到了二叉搜索树的性质
*/
bool delete_node(PTREE tree, int data){
	PNODE node = find(tree, data);
	if(!node){
		return false;
	}else{
		PNODE parent = node->parent;
		if(parent){
			// 叶子结点
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
