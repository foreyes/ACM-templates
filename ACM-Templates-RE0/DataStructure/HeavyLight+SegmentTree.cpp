#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5+10;
ll seg[maxn*4],lazy[maxn*4],dfn[maxn],size[maxn],son[maxn],fa[maxn],deep[maxn],top[maxn];
ll a[maxn],b[maxn];
ll dfs_clock = 0,n,m,MOD;
vector<int> G[maxn];

ll build(int o,int l,int r){
	lazy[o] = 0;
	if(l == r) return seg[o] = b[l] % MOD;
	int mid = (l + r) >> 1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
}
ll addLazy(int o,int l,int r,ll k){
	lazy[o] = (lazy[o] + k) % MOD;
	seg[o] =  (seg[o] + k * (r - l + 1)) % MOD;
	return 0;
}
void push_down(int o,int l,int r){
	int mid = (l + r) >> 1;
	addLazy(o<<1,l,mid,lazy[o]);
	addLazy(o<<1|1,mid+1,r,lazy[o]);
	lazy[o] = 0;
}
ll add(int o,int l,int r,int L,int R,ll k){
	if(l >= L && r <= R) return addLazy(o,l,r,k);
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) add(o<<1,l,mid,L,R,k);
	if(R > mid) add(o<<1|1,mid+1,r,L,R,k);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
}
ll query(int o,int l,int r,int L,int R){
	if(l >= L && r <= R) return seg[o];
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	ll ans = 0;
	if(L <= mid) ans = (ans + query(o<<1,l,mid,L,R)) % MOD;
	if(R > mid) ans = (ans + query(o<<1|1,mid+1,r,L,R)) % MOD;
	return ans;
}
void dfs1(int cur,int pre,int depth){
	size[cur] = 1,fa[cur] = pre,son[cur] = 0,deep[cur] = depth;
	for(auto nx : G[cur]){
		if(nx == pre) continue;
		dfs1(nx,cur,depth + 1);
		size[cur] += size[nx];
		if(size[nx] > size[son[cur]]) son[cur] = nx;
	}
}
void dfs2(int cur,int tp){
	dfn[cur] = ++dfs_clock;top[cur] = tp;
	if(son[cur]) dfs2(son[cur],tp);
	for(auto nx : G[cur]){
		if(nx == fa[cur] || nx == son[cur]) continue;
		dfs2(nx,nx);
	}
}
void modify(int x,int y,ll k){
	int t1 = top[x], t2 = top[y];
	while(t1 != t2){
		if(deep[t1] < deep[t2]){
			swap(x,y);swap(t1,t2);
		}
		add(1,1,n,dfn[t1],dfn[x],k);
		x = fa[t1];t1 = top[x];
	}
	if(deep[x] > deep[y]) swap(x,y);
	add(1,1,n,dfn[x],dfn[y],k);
}
ll queryTree(int x,int y){
	ll ans = 0;
	int t1 = top[x], t2 = top[y];
	while(t1 != t2){
		if(deep[t1] < deep[t2]){
			swap(x,y);swap(t1,t2);
		}
		ans = (ans + query(1,1,n,dfn[t1],dfn[x])) % MOD;
		x = fa[t1];t1 = top[x];
	}
	if(deep[x] > deep[y]) swap(x,y);
	ans = (ans + query(1,1,n,dfn[x],dfn[y])) % MOD;
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	int root;
	cin>>n>>m>>root>>MOD;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 1;i <= n-1;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);G[v].push_back(u);
	}
	dfs1(root,0,0);dfs2(root,root);
	for(int i = 1;i <= n;i++) b[dfn[i]] = a[i];
	build(1,1,n); 
	for(int i = 1;i <= m;i++){
		ll op,x,y,k;
		cin>>op;
		if(op == 1){
			cin>>x>>y>>k;
			modify(x,y,k);
		} else if(op == 2){
			cin>>x>>y;
			cout<<queryTree(x,y)<<endl;
		} else if(op == 3){
			cin>>x>>k;
			add(1,1,n,dfn[x],dfn[x] + size[x] - 1,k);
		} else{
			cin>>x;
			cout<<query(1,1,n,dfn[x],dfn[x] + size[x] - 1)<<endl;
		}
	}
}
