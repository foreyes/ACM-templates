typedef long long ll;
const int maxn = 1e6+10;
ll seg[maxn*4],lazy[maxn*4],a[maxn];

inline ll merge(ll a,ll b){
	return a + b;
	//return max(a,b);
	//return min(a,b);
}
inline ll addLazy(int o,int l,int r,ll x){
	seg[o] += x * (r-l+1);
	//seg[o] += x;
	lazy[o] += x;
}
inline void push_down(int o,int l,int r){
	int mid = (l + r) >> 1;
	addLazy(o<<1,l,mid,lazy[o]);
	addLazy(o<<1|1,mid+1,r,lazy[o]);
	lazy[o] = 0;
}
ll build(int o,int l,int r){
	if(l == r) return seg[o] = a[l];
	int mid = (l + r) >> 1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	seg[o] = merge(seg[o<<1],seg[o<<1|1]); 
}
ll add(int o,int l,int r,int L,int R,ll v){
	if(l >= L && r <= R) return addLazy(o,l,r,v);
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) add(o<<1,l,mid,L,R,v);
	if(R > mid) add(o<<1|1,mid+1,r,L,R,v);
	seg[o] = merge(seg[o<<1],seg[o<<1|1]);
}
ll query(int o,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l >= L && r <= R) return seg[o];
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	ll ans = 0;//or inf
	if(L <= mid) ans = merge(ans,query(o<<1,l,mid,L,R));
	if(R > mid) ans = merge(ans,query(o<<1|1,mid+1,r,L,R));
	return ans;
}
