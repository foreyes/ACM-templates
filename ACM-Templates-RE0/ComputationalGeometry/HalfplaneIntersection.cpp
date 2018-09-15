/*
//点p在直线L的左边(不包括线上) 修改 >= 
bool onLeft(Point p,Line L){
	return Cross(L.p2, p-L.p1) > 0;
}
//半平面交，不能计算退化的多边形。但是可以将每个半平面略微扩大求得交为单点或者线的情况
//返回半平面交后的多边形的顶点数，多边形存在poly种 
int halfplaneIntersection(Line* L,int n,Polygon& poly){
	sort(L,L+n);				//按极角排序 
	int first,last;				//双端队列指针 
	Point *p = new Point[n];	//p[i]为q[i]和q[i+1]的交点
	Line *q = new Line[n];		//双端队列
	q[first=last=0] = L[0];		//双端队列初始化
	for(int i = 1;i < n;i++){
		while(first < last && !onLeft(p[last-1], L[i])) last--;
		while(first < last && !onLeft(p[first], L[i])) first++;
		q[++last] = L[i];
		if(fabs(Cross(q[last].v, q[last-1].v)) < eps){
			//两向量平行且同向，取内侧的一个
			last--;
			if(onLeft(L[i].P, q[last])) q[last] = L[i]; 
		}
		if(first < last) p[last-1] = getLineIntersection(q[last-1],q[last]);
	} 
	while(first < last && !onLeft(p[last-1], q[first])) last--;
	//此处要注意，若可能会出现无界区域，应在运行前手动加入四个特殊半平面将区域框起来 
	//删除无用平面(*)
	if(last - first <= 1) return 0;	//空集
	p[last] = getLineIntersection(q[last],q[first]);	//计算首尾两个半平面的交点
	//从双端队列把答案复制到poly中 
	poly.size = last - first + 1;
	poly.ps.clear(); 
	for(int i = first;i <= last;i++) poly.ps.pb(p[i]);
	return poly.size;
}
*/ 
