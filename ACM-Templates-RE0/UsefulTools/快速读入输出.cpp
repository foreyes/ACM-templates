#include <cstdio>
#include <iostream>
using namespace std;

inline void read(int& x){
	char ch = getchar();
	int flag = 1;
	while(ch < '0' || ch > '9'){
		if(ch == '-') flag = -1;
		ch = getchar();
	}
	x = 0;
	for(;ch >= '0' && ch <= '9';ch = getchar()) x=x*10+ch-'0';
	x *= flag;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x *= -1;
	}
	char ch = x%10+'0';
	if(x > 10) write(x/10);
	putchar(ch);
}


int main(){
	int x,y;
	read(x);read(y);
	cout<<x<<" "<<y<<endl;
	write(x+y);puts("");
	write(x*y);puts("");
}
