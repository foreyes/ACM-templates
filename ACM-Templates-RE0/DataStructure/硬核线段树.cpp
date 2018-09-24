#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
const int MOD = 1e9+7;
typedef long long ll;
ll seg[maxn*4],mull[maxn*4],addl[maxn*4],mulsig[maxn*4],sigma[maxn*4],adds[maxn*4];

ll addLazy(int o,int l,int r,ll k){
	addl[o] = (addl[o] + k) % MOD;
	return seg[o] = (seg[o] + k * (r - l + 1)) % MOD;
}
ll mulLazy(int o,int l,int r,ll k){
	mull[o] = (mull[o] * k) % MOD;
	addl[o] = (addl[o] * k) % MOD;
	adds[o] = (adds[o] * k) % MOD;
	return seg[o] = (seg[o] * k) % MOD;
}
ll mulLazySig(int o,int l,int r,ll k){
	mulsig[o] = (mulsig[o] * k) % MOD;
	return sigma[o] = (sigma[o] * k) % MOD;
}
addLazySig(int o,int l,int r,ll k){
	adds[o] = (adds[o] + mulsig[o] * k) % MOD;
	return seg[o] = (seg[o] + sigma[o] * k) % MOD;
}
ll push_down(int o,int l,int r){
	int mid = (l + r) >> 1;
	if(mull[o] != 1){
		mulLazy(o<<1,l,mid,mull[o]);
		mulLazy(o<<1|1,mid+1,r,mull[o]);
	}
	if(adds[o] != 0){
		addLazySig(o<<1,l,mid,adds[o]);
		addLazySig(o<<1|1,mid+1,r,adds[o]);
	}
	if(mulsig[o] != 1){
		mulLazySig(o<<1,l,mid,mulsig[o]);
		mulLazySig(o<<1|1,mid+1,r,mulsig[o]);
	}
	if(addl[o] != 0){
		addLazy(o<<1,l,mid,addl[o]);
		addLazy(o<<1|1,mid+1,r,addl[o]);
	}
	addl[o] = adds[o] = 0;mull[o] = mulsig[o] = 1;
	return 0;
}
ll build(int o,int l,int r){
	mull[o] = mulsig[o] = 1;
	addl[o] = adds[o] = 0;
	if(l == r){
		seg[o] = 0;
		sigma[o] = 10;
		return 0;
	}
	int mid = (l + r) >> 1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
	sigma[o] = (sigma[o<<1] + sigma[o<<1|1]) % MOD;
}
ll add(int o,int l,int r,int L,int R,ll d){
	if(l >= L && r <= R) return addLazy(o,l,r,d);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) add(o<<1,l,mid,L,R,d);
	if(R > mid) add(o<<1|1,mid+1,r,L,R,d);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
	sigma[o] = (sigma[o<<1] + sigma[o<<1|1]) % MOD;
}
ll mul(int o,int l,int r,int L,int R,ll d){
	if(l >= L && r <= R) return mulLazy(o,l,r,d);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) mul(o<<1,l,mid,L,R,d);
	if(R > mid) mul(o<<1|1,mid+1,r,L,R,d);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
	sigma[o] = (sigma[o<<1] + sigma[o<<1|1]) % MOD;
}
ll mulSig(int o,int l,int r,int L,int R,ll d){
	if(l >= L && r <= R) return mulLazySig(o,l,r,d);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) mulSig(o<<1,l,mid,L,R,d);
	if(R > mid) mulSig(o<<1|1,mid+1,r,L,R,d);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
	sigma[o] = (sigma[o<<1] + sigma[o<<1|1]) % MOD;
}
ll addBySig(int o,int l,int r,int L,int R,ll d){
	if(l >= L && r <= R) return addLazySig(o,l,r,d);
	push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) addBySig(o<<1,l,mid,L,R,d);
	if(R > mid) addBySig(o<<1|1,mid+1,r,L,R,d);
	seg[o] = (seg[o<<1] + seg[o<<1|1]) % MOD;
	sigma[o] = (sigma[o<<1] + sigma[o<<1|1]) % MOD;
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

int main(){
	int T,n,m;
	cin>>T;
	for(int cas = 1;cas <= T;cas++){
		cin>>n>>m;
		build(1,1,n);
		cout<<"Case "<<cas<<": "<<endl;
		for(int i = 1;i <= m;i++){
			int x,y,d;string op;
			cin>>op>>x>>y;
			if(op[0] == 'w'){
				cin>>d;
				mul(1,1,n,x,y,10);
				add(1,1,n,x,y,d);
				addBySig(1,1,n,x,y,d);
				mulSig(1,1,n,x,y,100);
			} else{
				cout<<query(1,1,n,x,y)<<endl;
			}
		}
	}
}
