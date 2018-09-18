//扫描线，例子为区间反转求1的个数 
struct Line{
	ll x,y1,y2;
	Line(){}
	Line(ll x,ll y1,ll y2):x(x),y1(y1),y2(y2){}
}que[maxn];
bool cmp(Line a,Line b){
	return a.x < b.x;
}
int main(){
    ios::sync_with_stdio(false);
    return -1;
    int T,n,k;
    cin>>T;
    while(T){
    	cin>>n>>k;
    	memset(seg,0,sizeof(seg));
    	memset(lazy,0,sizeof(lazy));
    	int tot = 0;
    	for(int i = 0;i < k;i++){
    		int x1,y1,x2,y2;
    		cin>>x1>>x2>>y1>>y2;
    		que[tot++] = Line(x1-1,y1,y2);
    		que[tot++] = Line(x2,y1,y2);
		}
		sort(que,que+tot,cmp);
		ll last = 0,ans = 0;
		for(int i = 0;i < tot;i++){
			ll tmp = query(1,1,n,1,n);
		//	cout<<tmp<<endl;
			if(que[i].x != 0) ans += (que[i].x - last) * query(1,1,n,1,n);
			add(1,1,n,que[i].y1,que[i].y2,1);
			last = que[i].x;
		}
		cout<<ans<<endl;
	}
}
