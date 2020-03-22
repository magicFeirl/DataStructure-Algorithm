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

// �߾��ӷ�
string add(string a, string b){
	// ��һ�����ַ���ǰ�˲�0���볤��
	int len = fill_zero(a, b) - 1, ok = 0;
	int temp, n;
	
	string result = "";
	
	for(int i=len; i>=0; i--){
		// ��������תΪint
		temp = a[i] + b[i] - 2 * '0' + ok;
		// ��ȡ����ĸ�λ
		n = temp % 10;
		// ��ȡʮλ ����ÿλ���Ϊ9+9���Խ�����ֻ��Ϊ2λ��
		ok = temp / 10; // ��λ��־
		
		result = char(n + '0') + result;
	}
	
	if(ok) result = char(ok + '0') + result;
	
	return result;
}

// �߾�����
string sub(string a, string b){
	
	string prefix = ""; // ����ǰ��
	
	// ���a<b����������ȷ����������в����±����
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
