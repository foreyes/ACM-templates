#include <bits/stdc++.h>
using namespace std; 

const int maxn = 2e7+10;

//��Ҫ���ʣ�һ���ַ������ֻ��n�����ʲ�ͬ�Ļ����Ӵ�
int p[maxn*2];
int manacher(string s_source){
	//Ԥ�������#�Ҽ�$��##a#b#c#$
	string s = "##";
	for(int i = 0;i < s_source.size();i++){
		s += s_source[i];
		s += '#';
	}
	s += '$'; 
    int max_len = -1,mx = 0,id;
    for(int i = 1;i < s.size() - 1;i++){
        p[i] = i < mx ? min(p[2 * id - i], mx - i) : 1;
        while(s[i - p[i]] == s[i + p[i]]) p[i]++;//����һ���޸Ŀ�ͳ�����еĻ����Ӵ�
        if (mx < i + p[i]) mx = i + p[i],id = i;
        max_len = max(max_len, p[i] - 1);
    }
    return max_len;
}

int main(){
	string s;
	cin>>s;
	cout<<manacher(s);
	return 0;
}
