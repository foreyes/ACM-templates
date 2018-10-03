const int maxn = 5e5+10;
vector<int> G[maxn];//˫��� 
//������С���ض��ӣ���ȣ�����
int size[maxn],son[maxn],deep[maxn],fa[maxn];
int dfn[maxn],top[maxn];//DFS�����������Ķ��� 
int dfs_clock;//�ǵó�ʼ����dfn������Ҫ 

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
	if(son[cur]) dfs2(son[cur],tp);//���ȱ����ض��� 
	for(auto nx: G[cur]) {
		if(nx != fa[cur] && nx != son[cur]) {
			dfs2(nx, nx);
		}
	}
}
int lca(int x, int y) {
	int t1 = top[x], t2 = top[y];
	while(t1 != t2) {
		//����һ�������ϣ�����ȴ�������� 
		if(deep[t1] < deep[t2]) {
			swap(x, y); swap(t1, t2);
		}
		x = fa[t1], t1 = top[x];
	}
	return deep[x] < deep[y] ? x : y;
}
//�޸ģ���u-v������ִ�к���f����ѯҲ���� 
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
