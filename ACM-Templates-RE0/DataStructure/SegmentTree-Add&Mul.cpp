/* TEST CODE
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5+10;
int n,m,MOD;
ll seg[maxn*4],addl[maxn*4],mull[maxn*4],a[maxn];

ll build(int o,int l,int r);
ll addLazy(int o,int l,int r,ll k);
ll mulLazy(int o,int l,int r,ll k);
ll push_down(int o,int l,int r);
ll add(int o,int l,int r,int L,int R,ll k);
ll mul(int o,int l,int r,int L,int R,ll k);
ll query(int o,int l,int r,int L,int R);

int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>MOD;
	for(int i = 1;i <= n;i++) cin>>a[i];
	build(1,1,n);
	for(int i = 1;i <= m;i++){
		ll op,x,y,k;
		cin>>op>>x>>y;
		if(op == 1){
			cin>>k;
			mul(1,1,n,x,y,k);
		} else if(op == 2){
			cin>>k;
			add(1,1,n,x,y,k);
		} else{
			cout<<query(1,1,n,x,y)<<endl;
		}
	}
}
*/
//seg addl mull a MOD
ll build(int o,int l,int r){
	mull[o] = 1;addl[o] = 0;//init
	if(l == r) return seg[o] = a[l] % MOD;
	int mid = (l + r) >> 1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
}
ll addLazy(int o,int l,int r,ll k){
	addl[o] = (addl[o] + k) % MOD;
	return seg[o] = (seg[o] + (r-l+1) * k) % MOD;
}
ll mulLazy(int o,int l,int r,ll k){
	mull[o] = (mull[o] * k) % MOD;
	addl[o] = (addl[o] * k) % MOD;
	return seg[o] = (seg[o] * k) % MOD;
}
ll push_down(int o,int l,int r){
	int mid = (l + r) >> 1;
	if(mull[o] != 1){
		mulLazy(o<<1,l,mid,mull[o]);
		mulLazy(o<<1|1,mid+1,r,mull[o]);
	}
	if(addl[o] != 0){
		addLazy(o<<1,l,mid,addl[o]);
		addLazy(o<<1|1,mid+1,r,addl[o]);
	}
	addl[o] = 0;mull[o] = 1;
	return 0;
}
ll add(int o,int l,int r,int L,int R,ll k){
	if(l >= L && r <= R) return addLazy(o,l,r,k);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) add(o<<1,l,mid,L,R,k);
	if(R > mid) add(o<<1|1,mid+1,r,L,R,k);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
}
ll mul(int o,int l,int r,int L,int R,ll k){
	if(l >= L && r <= R) return mulLazy(o,l,r,k);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) mul(o<<1,l,mid,L,R,k);
	if(R > mid) mul(o<<1|1,mid+1,r,L,R,k);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
}
ll query(int o,int l,int r,int L,int R){
	if(l >= L && r <= R) return seg[o];
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	ll ans = 0;
	if(L <= mid) ans = (ans + query(o<<1,l,mid,L,R)) % MOD;
	if(R > mid) ans = (ans + query(o<<1|1,mid+1,r,L,R)) % MOD;
	return ans;
}
