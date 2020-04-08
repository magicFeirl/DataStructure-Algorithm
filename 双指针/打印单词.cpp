#include <stdio.h>
#include <string.h>


// 打印字符串中的单词，最简单的双指针模板
int main(){
	char str[1000];
	
	gets(str);
	
	int len = strlen(str);
	
	// 将O(N^2)优化为O(N)
	for(int i=0; i<len; i++){
		int j = i;
		
		// 模板核心
		while(j < len && str[j] != ' ') j++;
		
		// 根据题目写相应的逻辑
		for(int k=i; k<j; k++){
			printf("%c", str[k]);
		}
		
		while(j < len && str[j] == ' ') j++;
		
		printf("\n");
		
		i = j-1;
	}
	
	return 0;
}
