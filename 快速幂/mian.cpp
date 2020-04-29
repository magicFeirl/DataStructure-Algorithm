#include <iostream>

using namespace std;

// ���ݶ����Ƶ����ʼ���
/*
	a^x ���� x תΪ�����ƣ��ж� x �����λ�Ƿ�Ϊ 1�����Ϊ 1 �򽫴𰸳��Ի���
	����ÿ�γ�������
	
	���ӣ�
	10^6
	���� 6 תΪ������: 110
	��һ�� 0: ret = 1�� base = 100
	�ڶ��� 1: ret = 1 * base = 100�� base = 10000
	������ 1: ret = 100 * 10000 = 1000000�� base = 100000000
	���ĴΣ�����ѭ��
	
	��Ҫע��������� base *= base �Ľ���� base ��ָ����ӣ����������
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
