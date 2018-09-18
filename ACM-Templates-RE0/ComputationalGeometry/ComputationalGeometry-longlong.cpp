struct Point{
	ll x,y,id;
	Point(ll _x = 0,ll _y = 0):x(_x),y(_y){}
};
bool operator<(const Point& a,const Point& b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
Point operator-(Point a,Point b){
	return Point(a.x-b.x, a.y-b.y);
}
Point operator+(Point a,Point b){
	return Point(a.x+b.x, a.y+b.y);
}
ll operator*(Point a,Point b){
	return a.x*b.x + a.y*b.y;
}
Point operator*(Point a,ll b){
	return Point(a.x*b, a.y*b);
}
inline ll Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
inline double Length(Point a){
	return sqrt((double)(a*a));
}
inline double Angle(Point a,Point b){
	return acos((double)(a * b) / Length(a) / Length(b));
}
//����ʧ�����ж��߶ι淶�ཻ(�����˵�)
/��Ҫ�ж��߶��Ƿ��е��ڶ�����ڲ������������Σ�����һ�����㣬
//���߰��߶ζ˵�������һ�£�ͬʱȡ�е㣬checkһ�����������ǲ����ڶ�����ڲ� 
bool isSegmentsIntersection(Point A,Point B,Point C,Point D){
	//�������� 
	if(Cross(C-A,D-A) * Cross(C-B,D-B) >= 0) return false;
	if(Cross(A-C,B-C) * Cross(A-D,B-D) >= 0) return false;
	//�����ų����� 
	if(min(max(A.x,B.x),max(C.x,D.x)) < max(min(A.x,B.x),min(C.x,D.x))) return false;
	if(min(max(A.y,B.y),max(C.y,D.y)) < max(min(A.y,B.y),min(C.y,D.y))) return false;
	return true;
}
//�����߶���(//�����˵�)
bool isPointOnSegment(Point P,Point a,Point b){
	if(P == a || P == b) return true;
	//if(p == a || p == b) return false;
	return Cross(a-P,b-P) == 0 && (a-P)*(b-P) < 0;
} 
//�ж������߶��Ƿ��й����� 
bool isSegmengtsCrash(Point A,Point B,Point C,Point D){
	if( isPointOnSegment(A,C,D) || isPointOnSegment(B,C,D) ||
		isPointOnSegment(C,A,B) || isPointOnSegment(D,A,B)) return true;
	if(Cross(B-A,D-C) == 0) return false;//���� 
	return isSegmentsIntersection(A,B,C,D);//�ж��߶ι淶�ཻ 
}
