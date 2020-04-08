#include <iostream>

using namespace std;

/*
    ˫ָ�������Ŀһ�㶼������д��һ�����ص��㷨
    �ٸ���ʵ����������Ż�
    
    ģ��:
    
    for(int i=0; i<size; i++){
		int j = i;
		// check Ϊ�������ֵ�Ƿ����Ҫ��ĺ���
		while(j < i && check(i, j)) j++;
		
		// ������Ŀ�ľ����߼�
		// ...
	}
*/

int main(){
	int arr[] = {1, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 1};
	int size = sizeof(arr) / sizeof(arr[0]);
	int i, j, res = 0;

	// �����㷨O(N^2)
	
	// ˫ָ�루�����Ż���ÿ�ν�i����Ϊj�������ظ�
	// ����˵���ǵ������е�������Ҳ��Ȼ�ǵ������У���ô����ֱ���������ε�����β���м���
	
	// ��֪���Բ���ORZ
	for(i=0; i<size; i++){
		j = i;
		
		while(j + 1 < size && arr[j] <= arr[j+1]) j++;
		
		res = max(res, j - i + 1);
		
		i = j;
	}
	
	printf("%d", res);
	
	return 0;
}
