/*
ֻ���ؽ��ֵ����Ҫ���������ֵ�߶��� + ��ɢ��
���޸�ת�Ʒ��̣�ʵ��������������к�
*/
ll LIS(int* f,int len){
	ll ret = 0;
	//��ɢ���������ڽ��������ڽ���һ�� 
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//�����ϸ�С����Ҫ�޸�ѯ�ʣ����̿�����Ҫ�޸� 
		ll tmp = query(1,1,_cnt,1,get_id(f[i])-1) + 1;
		add(1,1,_cnt,get_id(f[i]),tmp);
		ret = max(ret,tmp);
	}
	return ret;
}
/*
�����ϵĻ������������
�����߶����ϵĽڵ���һ��pll�����޸��߶�����֤����ֵ�����С����
����ֵ�����С������pair�����second��������ȡ������������ֱ�Ӷ�pairȡmax������ȡmin�ȣ����޸�
*/
int last[maxn];
vi LIS(int* f,int len){
	ll ret = 0,mark;
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//�����ϸ�С����Ҫ�޸�ѯ�ʣ����̿�����Ҫ�޸� 
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
//TODO:����ģ�廹δ���Թ� 
/*
�����ݽ��д���֮��ѡȡȨֵ����ֵ�����С��x1 < x2��y1 < y2�����з������
����x1 <= x2����������ԼΪ������LIS 
x��y��Ҫ��ȫ�ֱ�������СΪlen���±��1��ʼ 
*/
int ord[maxn],last[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
//�߶����е�first��val��second�Ǳ��ȡ�� 
vi LIS(int len){
	//xȡֵ������-1ʱ��Ҫ�޸� 
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
�����Ǹ�ռ�ռ�̫����,̫���ӣ�дһ�����������ֻ����𰸵İ汾 
*/
int ord[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
ll LIS(int len){
	//xȡֵ������-1ʱ��Ҫ�޸� 
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
