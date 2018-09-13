struct Point{
	ll x,y,id;
	Point(ll _x = 0,ll _y = 0):x(_x),y(_y){}
};
typedef Point Vector;
bool operator<(const Point& a,const Point& b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
Vector operator-(Point a,Point b){
	return Point(a.x-b.x, a.y-b.y);
}
Vector operator+(Point a,Point b){
	return Point(a.x+b.x, a.y+b.y);
}
ll operator*(Vector a,Vector b){
	return a.x*b.x + a.y*b.y;
}
Vector operator*(Vector a,ll b){
	return Vector(a.x*b, a.y*b);
}
inline ll Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
inline double Length(Vector a){
	return sqrt((double)(a*a));
}
inline double Angle(Vector a,Vector b){
	return acos((double)(a * b) / Length(a) / Length(b));
}
/*
//�����߶���(�����˵�)
bool pointOnSegment(Point P,Point a,Point b){
	return Cross(a-P,b-P) == 0 && (a-P)*(b-P) < 0;
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
//�ж������߶��Ƿ��г��˶˵���Ĺ����� 
bool segmentsCrashCheck(Point A,Point B,Point C,Point D){
	//���� 
	if(Cross(B-A,D-C) == 0){
		if(pointOnSegment(A,C,D) || pointOnSegment(B,C,D) ||
		   pointOnSegment(C,A,B) || pointOnSegment(D,A,B)) return true;
		return false; 
	}
	return isSegmentsIntersection(A,B,C,D);
}
*/
