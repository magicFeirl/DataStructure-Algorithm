#include <iostream>

using namespace std;

// 根据二进制的性质加速
/*
	a^x 其中 x 转为二进制，判断 x 的最低位是否为 1，如果为 1 则将答案乘以基数
	基数每次乘以自身
	
	例子：
	10^6
	其中 6 转为二级制: 110
	第一次 0: ret = 1； base = 100
	第二次 1: ret = 1 * base = 100； base = 10000
	第三次 1: ret = 100 * 10000 = 1000000； base = 100000000
	第四次：结束循环
	
	需要注意的是这里 base *= base 的结果是 base 的指数相加，而不是相乘
*/
long long fp(int num, int p){
	int base = num;
	
	long long ret = 1;
	
	while(p){
		if(p & 1){
			ret *= base;
		}
		
		base *= base;
		p >>= 1;
	}
	
	return ret;
}

int main(){
	int n, p;
	
	while(cin >> n >> p){
		cout << fp(n, p) << endl;
	}
	
	return 0;
}
