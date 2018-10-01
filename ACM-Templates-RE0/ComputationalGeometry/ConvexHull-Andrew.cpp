/*
Andrew算法基于水平序求凸包
输入点的数组p，点的个数n，布尔数组为1表示跳过该编号的点；返回凸包点的个数，凸包的点存在ch数组里
直线上的点也要算的话，把两个<=改成< 
精度要求高时建议使用三态函数
warning：下标从0开始
warning: 如果允许计算直线上的多个点，同时可以会是退化多边形的话，用下面的另一个版本 
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
版本2，用于处理特殊情况。
特殊情况：需要计算直线上的点，同时可能会有退化成直线的多边形 
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
