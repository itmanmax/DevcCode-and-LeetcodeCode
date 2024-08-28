#include <iostream>
#include <string>
using namespace std;
int main() {
	string s = "22111103163";
	int n = s.length();
	int num = 0;
	for(int i = 0; i < n; i++) {
		num = num*10 + int(s[i] - '0');
	}
	cout<<"字符串22111303163转化为整型数字为"<<num<<endl;
}

