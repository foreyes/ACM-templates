const int maxn = 5e5+10;
vector<int> G[maxn];//双向边 
//子树大小，重儿子，深度，父亲
int size[maxn],son[maxn],deep[maxn],fa[maxn];
int dfn[maxn],top[maxn];//DFS序，所在重链的顶端 
int dfs_clock;//记得初始化，dfn计算需要 

void dfs1(int cur, int father, int depth) {
	size[cur] = 1,son[cur] = 0,deep[cur] = depth,fa[cur] = father;
	for(auto nx: G[cur]) {
		if(nx != father) {
			dfs1(nx, cur, depth + 1);
			size[cur] += size[nx];
			if(size[nx] > size[son[cur]]) {
				son[cur] = nx;
			}
		}
	}
}
void dfs2(int cur, int tp){
	top[cur] = tp,dfn[cur] = ++dfs_clock;
	if(son[cur]) dfs2(son[cur],tp);//优先遍历重儿子 
	for(auto nx: G[cur]) {
		if(nx != fa[cur] && nx != son[cur]) {
			dfs2(nx, nx);
		}
	}
}
int lca(int x, int y) {
	int t1 = top[x], t2 = top[y];
	while(t1 != t2) {
		//不在一个重链上，将深度大的往上跳 
		if(deep[t1] < deep[t2]) {
			swap(x, y); swap(t1, t2);
		}
		x = fa[t1], t1 = top[x];
	}
	return deep[x] < deep[y] ? x : y;
}
//修改，对u-v这条链执行函数f。查询也类似 
void modify(int x, int y,void f(int,int)) {
	int t1 = top[x], t2 = top[y];
	while(t1 != t2) {
		if(deep[t1] < deep[t2]) {
			swap(x, y); swap(t1, t2);
		}
		f(dfn[t1], dfn[x]);
		x = fa[t1], t1 = top[x];
	}
	if(deep[x] > deep[y]) swap(x, y);
	f(dfn[x], dfn[y]);
}
