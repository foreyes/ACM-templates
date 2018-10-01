/*
Andrew�㷨����ˮƽ����͹��
����������p����ĸ���n����������Ϊ1��ʾ�����ñ�ŵĵ㣻����͹����ĸ�����͹���ĵ����ch������
ֱ���ϵĵ�ҲҪ��Ļ���������<=�ĳ�< 
����Ҫ���ʱ����ʹ����̬����
warning���±��0��ʼ
warning: ����������ֱ���ϵĶ���㣬ͬʱ���Ի����˻�����εĻ������������һ���汾 
*/
int convexHull(Point* p,bool* check,int n,Point* ch,polygon& poly){
	sort(p,p+n);
	int m = 0;
	for(int i = 0;i < n;i++){
		if(check[p[i].id]) continue; 
		while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i >= 0;i--){
		if(check[p[i].id]) continue;
		while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(m > 1) m--;
	poly.clear();
	for(int i = 0;i < m;i++) poly.push_back(ch[i]);
	return m;
}
/*
�汾2�����ڴ������������
�����������Ҫ����ֱ���ϵĵ㣬ͬʱ���ܻ����˻���ֱ�ߵĶ���� 
*/ 
int convexHull(Point* p,bool* check,int n,Point* ch,polygon& poly){
	sort(p,p+n);
	int m = 0,st = n;
	bool vis[n] = {0};
	for(int i = 0;i < n;i++){
		if(check[p[i].id]) continue;
		st = min(st,i); 
		while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) vis[ch[--m].id] = false;
		vis[p[i].id] = true;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i >= 0;i--){
		if(check[p[i].id]) continue;
		if(i != st && vis[p[i].id]) continue;
		while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(m > 1) m--;
	poly.clear();
	for(int i = 0;i < m;i++) poly.push_back(ch[i]);
	return m;
}
