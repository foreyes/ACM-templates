/*
//��p��ֱ��L�����(����������) �޸� >= 
bool onLeft(Point p,Line L){
	return Cross(L.p2, p-L.p1) > 0;
}
//��ƽ�潻�����ܼ����˻��Ķ���Ρ����ǿ��Խ�ÿ����ƽ����΢������ý�Ϊ��������ߵ����
//���ذ�ƽ�潻��Ķ���εĶ�����������δ���poly�� 
int halfplaneIntersection(Line* L,int n,Polygon& poly){
	sort(L,L+n);				//���������� 
	int first,last;				//˫�˶���ָ�� 
	Point *p = new Point[n];	//p[i]Ϊq[i]��q[i+1]�Ľ���
	Line *q = new Line[n];		//˫�˶���
	q[first=last=0] = L[0];		//˫�˶��г�ʼ��
	for(int i = 1;i < n;i++){
		while(first < last && !onLeft(p[last-1], L[i])) last--;
		while(first < last && !onLeft(p[first], L[i])) first++;
		q[++last] = L[i];
		if(fabs(Cross(q[last].v, q[last-1].v)) < eps){
			//������ƽ����ͬ��ȡ�ڲ��һ��
			last--;
			if(onLeft(L[i].P, q[last])) q[last] = L[i]; 
		}
		if(first < last) p[last-1] = getLineIntersection(q[last-1],q[last]);
	} 
	while(first < last && !onLeft(p[last-1], q[first])) last--;
	//�˴�Ҫע�⣬�����ܻ�����޽�����Ӧ������ǰ�ֶ������ĸ������ƽ�潫��������� 
	//ɾ������ƽ��(*)
	if(last - first <= 1) return 0;	//�ռ�
	p[last] = getLineIntersection(q[last],q[first]);	//������β������ƽ��Ľ���
	//��˫�˶��аѴ𰸸��Ƶ�poly�� 
	poly.size = last - first + 1;
	poly.ps.clear(); 
	for(int i = first;i <= last;i++) poly.ps.pb(p[i]);
	return poly.size;
}
*/ 
