#include <stdio.h>
#include <string.h>


// ��ӡ�ַ����еĵ��ʣ���򵥵�˫ָ��ģ��
int main(){
	char str[1000];
	
	gets(str);
	
	int len = strlen(str);
	
	// ��O(N^2)�Ż�ΪO(N)
	for(int i=0; i<len; i++){
		int j = i;
		
		// ģ�����
		while(j < len && str[j] != ' ') j++;
		
		// ������Ŀд��Ӧ���߼�
		for(int k=i; k<j; k++){
			printf("%c", str[k]);
		}
		
		while(j < len && str[j] == ' ') j++;
		
		printf("\n");
		
		i = j-1;
	}
	
	return 0;
}
