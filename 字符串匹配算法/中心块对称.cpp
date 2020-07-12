#include <stdio.h>
#include <string.h>

// 判断一个串是否为中心块对称
int judge(const char *str){
    int len = strlen(str);
    int mid = len & 1 ? (len / 2 + 1) : len / 2;
    int i = 0;
    
    while(i < mid && mid < len){
        if(str[i] != str[mid]){
            return 0;
        }
        
        i++, mid++;
    }
    
    return 1;
}

// 打印串前缀
void prt_prefix(const char *str, int len){
    if(len-1 == 0){
        return ;
    }
    
    printf("Prefix of str[%d] (%c): ", len-1, str[len-1]);
    
    for(int i=0; i<len-1; i++){
        printf("%c", str[i]);
    }
    printf("\n");
    
    prt_prefix(str, len-1);
}

void prt_suffix(const char *str, int begin, int len){
    if(begin+1 == len){
        return ;
    }
    
    printf("Suffix of str[%d] (%c): ", begin, str[begin]);
    
    for(int i=begin+1; i<len; i++){
        printf("%c", str[i]);
    }
    printf("\n");
    
    prt_suffix(str, begin+1, len);
}

int main(){
    const char * str = "ABCBAC";
    int len = strlen(str);
    
    prt_prefix(str, len);
    printf("\n");
    prt_suffix(str, 0, len);
    // printf("%d %d\n", judge(str), judge("12312"));
    
    return 0;
}
