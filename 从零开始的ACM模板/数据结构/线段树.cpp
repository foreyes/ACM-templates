//可修改为每个节点为bitset的线段树，修改数据类型 + add函数 + combine函数即可 
const int maxn = 1e5+10;
ll a[maxn],seg[maxn*4]; 
//合并函数，取最大值、求和等等
inline ll combine(ll x,ll y){
	return max(x,y);
	//return min(x,y);
	//return x+y;
}
ll build(int o,int l,int r){
	if(l == r) return seg[o] = a[l];
	int mid = (l + r) / 2;
	build(o*2,l,mid);build(o*2+1,mid+1,r);
	seg[o] = combine(seg[o*2],seg[o*2+1]);
}
ll add(int o,int l,int r,int x,ll v){
	//更新的这一行需要根据需求修改 
	if(l == r) return seg[o] = combine(seg[o],v);
	int mid = (l + r) / 2;
	if(x <= mid) add(o*2,l,mid,x,v);
	else add(o*2+1,mid+1,r,x,v);
	seg[o] = combine(seg[o*2],seg[o*2+1]);
}
ll query(int o,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l >= L && r <= R) return seg[o];
	int mid = (l + r) / 2;
	ll ans = 0;
	if(L <= mid) ans = combine(ans,query(o*2,l,mid,L,R));
	if(R > mid) ans = combine(ans,query(o*2+1,mid+1,r,L,R));
	return ans;
}
//TODO：这一个函数还没有测试过 
ll query(int o,int l,int r,int x){
	if(l == r) return seg[o];
	int mid = (l + r) / 2;
	if(x <= mid) return query(o*2,l,mid,x);
	else return query(o*2+1,mid+1,r,x);
}
