#include <iostream>

using namespace std;

int fill_zero(string& a, string &b){
	int lena, lenb;
	int max_len = max(lena=a.length(), lenb=b.length());
	
	for(int i=lena; i<max_len; i++){
		a = "0" + a;
	}
	
	for(int i=lenb; i<max_len; i++){
		b = "0" + b;
	}
	
	return max_len;
}

// 高精加法
string add(string a, string b){
	// 第一步：字符串前端补0对齐长度
	int len = fill_zero(a, b) - 1, ok = 0;
	int temp, n;
	
	string result = "";
	
	for(int i=len; i>=0; i--){
		// 将运算数转为int
		temp = a[i] + b[i] - 2 * '0' + ok;
		// 获取结果的个位
		n = temp % 10;
		// 获取十位 由于每位最大为9+9所以结果最多只会为2位数
		ok = temp / 10; // 进位标志
		
		result = char(n + '0') + result;
	}
	
	if(ok) result = char(ok + '0') + result;
	
	return result;
}

// 高精减法
string sub(string a, string b){
	
	string prefix = ""; // 符号前导
	
	// 如果a<b交换两个串确保计算过程中不会下标溢出
	if(a < b){
		swap(a, b);
		prefix = "-";
	}
	
	int len = fill_zero(a, b) - 1, temp, n;
	string result = "";
	
	for(int i=len; i>=0; i--){
		if(a[i] < b[i]){
			a[i] += 10;
			a[i-1] -= 1;
		}
		
		result = char(a[i] - b[i] + '0') + result;
	}
	
	result.erase(0, result.find_first_not_of('0'));
	
	return prefix + result;
}

int main(){
	string a, b;
	
	while(true){
		cin >> a >> b;
		cout << a << "+" << b << " = " << add(a, b) << endl;
		cout << a << "-" << b << " = " << sub(a, b) << endl;
	}
	
	return 0;
}
