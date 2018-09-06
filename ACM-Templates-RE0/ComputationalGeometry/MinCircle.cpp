//二维最小圆覆盖，增量法 
Circle minCircle(Point *p, int n){
	random_shuffle(p,p+n);
	Circle cur = Circle(p[0],0);
	for(int i = 1;i < n;i++){
		if(pointInCircle(p[i],cur)) continue;
		cur = Circle(p[i],0);
		for(int j = 0;j < i;j++){
			if(pointInCircle(p[j],cur)) continue;
			cur = getCircle(p[i],p[j]);
			for(int k = 0;k < j;k++){
				if(pointInCircle(p[k],cur)) continue;
				cur = getCircle(p[i],p[j],p[k]);
			}
			
		}
	}
	return cur;
}
