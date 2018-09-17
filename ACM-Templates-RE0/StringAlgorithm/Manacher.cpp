#include <bits/stdc++.h>
using namespace std; 

const int maxn = 2e7+10;

//重要性质：一个字符串最多只有n个本质不同的回文子串
int p[maxn*2];
int manacher(string s_source){
	//预处理左加#右加$，##a#b#c#$
	string s = "##";
	for(int i = 0;i < s_source.size();i++){
		s += s_source[i];
		s += '#';
	}
	s += '$'; 
    int max_len = -1,mx = 0,id;
    for(int i = 1;i < s.size() - 1;i++){
        p[i] = i < mx ? min(p[2 * id - i], mx - i) : 1;
        while(s[i - p[i]] == s[i + p[i]]) p[i]++;//在这一行修改可统计所有的回文子串
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
