#include <cstdio>
#include <vector>

using namespace std;


vector<int> res;
long long count;

// ��ʼλ�� ����λ�� �������� ��ǰ������ʵ������ res.size() �����
void dfs(int begin, int end, int limit, int step){
	if(step == limit){
		for(int i=0; i<res.size(); i++){
			printf("%d ", res[i]);
		}
		
		printf("\n");
		
		count++;
		return ;
	}
	
	for(int i=begin; i<end; i++){
		res.push_back(i);
		dfs(begin, end, limit, step + 1);
		res.pop_back();
	}
}

int main(){
	// ���� 0-9 ����Ϊ 2 ���ظ�����
	dfs(0, 9, 2, 0);
	
	printf("count: %lld\n", count); // 81
	
	return 0;
}
