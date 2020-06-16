// DFS
// ������û��˼������������
// ��һ������ A���� A ��Ԫ�صĺ������ target ��������A��ÿ��Ԫ�ؿ����ظ�ʹ��
// ���� A=[1, 2, 3] target = 7
// ��� 44
// �ǳ��򵥵�һ���⣬ˮ�ˣ�������
#include <cstdio>
#include <vector>

using namespace std;

long long count;

const int N = 1e3;
int res[N], idx = 0;

// A���� ���鳤�� Ŀ��ֵ ��ǰ�ܺ�
void dfs(int *A, int length, int target, int sum){
	if(sum > target){
		return ;
	}else if(sum == target){
		count++;
		
		for(int i=0; i<idx; i++){
			printf("%d ", res[i]);
		}

		printf("\n");
	}else{
		// ö�ٿ���
		for(int i=0; i<length; i++){
			// ����һ�����ܽ�
			res[idx++] = A[i];
			// ���Կ�������ֻ��sum��ֵ�ڱ�
			dfs(A, length, target, sum + A[i]);
			// �������Ժ�ɾ�����һ����
			idx--;
		}
	}
}

int main(){
	int A[] = {1, 2, 3},
	length = sizeof(A) / sizeof(A[0]), target = 7;
	
	printf("%d\n", length);
	dfs(A, length, target, 0);
	
	printf("count: %lld\n", count);
	
	return 0;
}
