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
	
	// 如果为空串表示结果为0
	if(result.length() == 0){
		return "0";
	}
	
	return prefix + result;
}

// 要用到大数加
string mul(string a, string b){
	string result = "0";
	int i, j;
	int lena = a.length() - 1, lenb = b.length() - 1;
	
	for(i=lena; i>=0; i--){
		if(a[i] != '0'){
			int ok = 0, temp, n;
			string temp_str = "";
			// 末尾补零
			for(j=0; j<lena-i; j++)
				temp_str += "0";
				
			for(j=lenb; j>=0; j--){
				temp = (b[j] - '0') * (a[i] - '0') + ok;
				n = temp % 10;
				ok = temp / 10;
				temp_str = char(n+'0') + temp_str;
			}
			
			if(ok) temp_str = char(ok+'0') + temp_str;
			result = add(result, temp_str);
		}
	}
	
	return result;
}

int main(){
	string a, b;
	
	while(cin >> a >> b){
		cout << a << "+" << b << " = " << add(a, b) << endl;
		cout << a << "-" << b << " = " << sub(a, b) << endl;
		cout << a << "*" << b << " = " << mul(a, b) << endl << endl;
	}
	
	return 0;
}
