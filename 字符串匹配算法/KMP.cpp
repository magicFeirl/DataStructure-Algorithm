#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>


void prefix_table(const char pattern[], int prefix[], int n){
    int len = 0; // len ��ʾ �±�Ϊ i ʱ��ǰ�������ǰ��׺Ϊ�೤
    int i = 1; // �ӵڶ�����ĸ��ʼ��ǰ�����ĸ���бȽ�
    prefix[len] = 0; // ��һ����ĸû��ǰ��׺����ǰ׺���е�ֵΪ 0
    
    while(i < n){ // ��ģʽ��û����ʱ
        // ���ģʽ���ĵ� i ����ĸ�͵� len ����ĸ��ͬ�����������Ȼ����� 1
        if(pattern[i] == pattern[len]){ 
            // printf("%d\n", prefix[i]);
            prefix[i++] = ++len;
        }else{
            // ����Ͱѵ�ǰ�����ǰ��׺ָ��ǰ׺��ĵ� len - 1 λ����ǰλ���μ����㣩
            if(len > 0){
                len = prefix[len - 1];
            }else{ // ����û�������ǰ��׺
                prefix[i] = len; // len == 0
                i++; // ��������ַ�
            }
        }
    }
    
    // ��ǰ׺�����������һλ��ͬʱ�����еĵ�һ��Ԫ��ֵ��Ϊ -1
    for(i=n-1; i>0; i--){
        prefix[i] = prefix[i-1];
    }
    
    prefix[0] = -1;
}

int KMP(const char *str, const char *substr, int next[], int n){
    int lenstr = strlen(str);
    int lensubstr = strlen(substr);
    int i = 0, j = 0;
    // �������ĸĽ���
    while(i < lenstr && j < lensubstr){
        if(j == -1 || str[i] == substr[j]){
            i++, j++;
        }else{
            j = next[j]; // ���� next[j] ������ǰ��׺����һ������ʧ��ǰ���Ѿ�ƥ�����
        }
    }
    
    return j == lensubstr ? (i - j) : -1;
}

int BF(const char *str, const char *substr){
    int lenstr = strlen(str);
    int lensubstr = strlen(substr);
    int i = 0, j = 0;
    
    while(i < lenstr && j < lensubstr){
        if(str[i] == substr[j]){
            i++, j++;
        }else{
            i = i - j + 1, j = 0;
        }
    }
    
    return j == lensubstr ? (i - j) : -1;
}

char * gen_str(int len){
    char *str = (char *)malloc(len * sizeof(char) + 1);
    for(int i=0; i<len; i++){
        str[i] = ('a' + rand() % ('z' - 'a'));
    }
    
    str[len] = '\0';
    
    return str;
}

const int N = 1024 * 1024 * 100;
const char *target = "gdjwgyesfobmp";

int main(){
    // const char *str = "1234514";
    // const char *substr = "45";
    
    FILE *file = fopen("data.txt", "r+");

    // fputs(gen_str(N), file);
    // return 0;
    char *genstr = (char *)malloc(sizeof(char) * N + 1);
    fgets(genstr, N, file);
    
    // int n = strlen(genstr);
    int *prefix = (int *)malloc(sizeof(int) * N);
    
    prefix_table(genstr, prefix, N);
    
    int start = time(0);
    printf("start %d\n", start);
    printf("%d\n", KMP(genstr, target, prefix, N)); // 0.05934
    printf("%d\n", BF(genstr, target)); // 0.06173
    
    unsigned int end = time(0);
    printf("end %d\n", end);
    printf("%d\n", end - start);
    
    free(genstr);
    free(prefix);
    
    return 0;
}
