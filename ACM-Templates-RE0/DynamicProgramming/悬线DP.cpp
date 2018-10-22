#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000;
int lft[maxn][maxn], up[maxn][maxn], rgt[maxn][maxn];
int Map[maxn][maxn];

int main(){
	int n,m;
	cin>>n>>m;
	for(int y = 0;y < n;y++){
		for(int x = 0;x < m;x++){
			cin>>Map[x][y];
		}
	}
	//预处理右边界
	for(int y = 0;y < n;y++){
		rgt[m-1][y] = 1;
		for(int x = m-1;x >= 0;x--){
			if(Map[x][y] != Map[x+1][y]) rgt[x][y] = rgt[x+1][y] + 1;
			else rgt[x][y] = 1;
		}
	}
	//预处理左边界
	for(int y = 0;y < n;y++){
		lft[0][y] = 1;
		for(int x = 1;x < m;x++){
			if(Map[x][y] != Map[x-1][y]) lft[x][y] = lft[x-1][y] + 1;
			else lft[x][y] = 1;
		}
	}
	//预处理上边界，同时更新左右边界
	for(int x = 0;x < m;x++){
		up[x][0] = 1;
		for(int y = 1;y < n;y++){
			if(Map[x][y] != Map[x][y-1]){
				lft[x][y] = min(lft[x][y],lft[x][y-1]);
				rgt[x][y] = min(rgt[x][y],rgt[x][y-1]);
				up[x][y] = up[x][y-1] + 1;
			} 
			else up[x][y] = 1; 
		}
	}
	//计算答案
	int ans1 = 0,ans2 = 0;
	for(int y = 0;y < n;y++){
		for(int x = 0;x < m;x++){
			int len = lft[x][y];
			int tmp = min(up[x][y],len);
			ans1 = max(ans1,tmp*tmp);
			ans2 = max(ans2,up[x][y]*len);
		}
	}
	cout<<ans1<<endl<<ans2<<endl;
}