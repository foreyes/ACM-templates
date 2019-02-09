#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
vector<tuple<int,int,int> > edges;
int fa[maxn];

void init(){
	for(int i = 0;i < maxn;i++) fa[i] = i;
}
int getFather(int x){
	return fa[x] == x? x: fa[x] = getFather(fa[x]);
}
bool merge(int a,int b){
	int x = getFather(a), y = getFather(b);
	if(x == y) return false;
	fa[y] = x;
	return true;
}
typedef long long ll;

ll kruskal(int n, int m){
	sort(edges.begin(), edges.end());
	int rem = n-1, i = 0;
	ll ans = 0;
	while(rem && i != m){
		int u, v, len;
		tie(len, u, v) = edges[i++];
		if(merge(u, v)){
			ans += len;
			rem--;
		}
	}
	return i != m? ans: -1;
}

int main(){
	ios::sync_with_stdio(false);
	init();
	int n, m;
	cin>>n>>m;
	for(int i = 0;i < m;i++){
		int u,v,len;
		cin>>u>>v>>len;
		edges.push_back(make_tuple(len,u,v));
	}
	ll ans = kruskal(n, m);
	if(ans == -1) cout<<"orz"<<endl;
	else cout<<ans<<endl;	
	return 0;
}