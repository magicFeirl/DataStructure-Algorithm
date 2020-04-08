#include <iostream>

using namespace std;


// 非常简单的双指针问题
int main(){
	
	int array[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
	int size = sizeof(array) / sizeof(array[0]);
	int res = 0;
	
	for(int i=0; i<size; i++){
		int j = i;
		
		while(j < size - 1 && array[j] == array[j+1]) j++;
		
		res = max(res, j - i + 1);
		i = j;
	}
	
	printf("%d", res);
	
	return 0;
}
