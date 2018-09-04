/*
只返回结果值，需要区间求最大值线段树 + 离散化
可修改转移方程，实现求最大上升序列和
*/
ll LIS(int* f,int len){
	ll ret = 0;
	//离散化，可以在仅主函数内进行一次 
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//不是严格小于需要修改询问，方程可能需要修改 
		ll tmp = query(1,1,_cnt,1,get_id(f[i])-1) + 1;
		add(1,1,_cnt,get_id(f[i]),tmp);
		ret = max(ret,tmp);
	}
	return ret;
}
/*
在以上的基础上输出方案
由于线段树上的节点是一个pll，需修改线段树保证输出字典序最小方案
输出字典序最小方案，pair里面的second存的是序号取负，这样可以直接对pair取max，若是取min等，需修改
*/
int last[maxn];
vi LIS(int* f,int len){
	ll ret = 0,mark;
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//不是严格小于需要修改询问，方程可能需要修改 
		pll tmp = query(1,1,_cnt,1,get_id(f[i])-1);
		ll val = tmp.fi + 1;
		last[i] = -tmp.se;
		add(1,1,_cnt,get_id(f[i]),mp(val,-i));
		if(val > ret){
			ret = val;
			mark = i;
		}
	}
	stack<int> s;
	while(mark != 0){
		s.push(mark);
		mark = last[mark];
	}
	vi retv;
	while(!s.empty()){
		retv.pb(s.top());
		s.pop();
	}
	return retv;
}
//TODO:以下模板还未测试过 
/*
对数据进行处理之后，选取权值最大字典序最小的x1 < x2，y1 < y2的序列方案输出
若是x1 <= x2，可排序后归约为正常的LIS 
x和y需要是全局变量，大小为len，下标从1开始 
*/
int ord[maxn],last[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
//线段树中的first是val，second是编号取负 
vi LIS(int len){
	//x取值可能是-1时需要修改 
	ll ret = 0,mark,lastx = -1;
	for(int i = 1;i <= len;i++) ord[i] = i;
	sort(ord+1,ord+len+1,cmp);
	discretize(y,len);
	memset(seg,0,sizeof(seg));
	queue<pair<ll,pll> > q;
	for(int i = 1;i <= len;i++){
		if(lastx != x[ord[i]]){
			while(!q.empty()){
				add(1,1,_cnt,q.front().fi,q.front().se);
				q.pop();
			}
			lastx = x[ord[i]];
		}
		pll tmp = query(1,1,_cnt,1,get_id(y[ord[i]])-1);
		ll val = tmp.fi + 1;
		last[i] = -tmp.se;
		q.push(mp(get_id(y[ord[i]]), mp(val,-ord[i])));
		if(val > ret){
			ret = val;
			mark = ord[i];
		}
	}
	stack<int> s;
	while(mark != 0){
		s.push(mark);
		mark = last[mark];
	}
	vi retv;
	while(!s.empty()){
		retv.pb(s.top());
		s.pop();
	}
	return retv;
}
/*
上面那个占空间太大了,太复杂，写一个不输出方案只输出答案的版本 
*/
int ord[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
ll LIS(int len){
	//x取值可能是-1时需要修改 
	ll ret = 0,lastx = -1;
	for(int i = 1;i <= len;i++) ord[i] = i;
	sort(ord+1,ord+len+1,cmp);
	discretize(y,len);
	memset(seg,0,sizeof(seg));
	queue<pll> q;
	for(int i = 1;i <= len;i++){
		if(lastx != x[ord[i]]){
			while(!q.empty()){
				add(1,1,_cnt,q.front().fi,q.front().se);
				q.pop();
			}
			lastx = x[ord[i]];
		}
		ll tmp = query(1,1,_cnt,1,get_id(y[ord[i]])-1) + 1;
		q.push(mp(get_id(y[ord[i]]),tmp));
		ret = max(ret,tmp);
	}
	return ret;
}
