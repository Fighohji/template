// class Point
// {
// 	public:
// 	db x,y;

// 	Point(db x=0,db y=0):x(x),y(y) {}
// 	Point operator + (Point p){return Point(x+p.x,y+p.y); }
// 	Point operator - (Point p){return Point(x-p.x,y-p.y); }
// 	Point operator * (db a){return Point(a*x,a*y); }
// 	Point operator / (db a){return Point(x/a,y/a); }
	
// 	bool operator<(const Point &p)const{ return !equals(x,p.x) ? x<p.x : y<p.y; }
// 	bool operator==(const Point &p)const{ return fabs(x-p.x)<eps&&fabs(y-p.y)<eps; }
// };
// class Circle
// {
// 	public:
// 	Point c;db r;
// 	Circle(Point c=Point(),db r=0.0):c(c),r(r){};
// };
// struct Segment
// {
// 	Point p1,p2;
// };
// struct Triangle
// {
// 	Point aa,bb,cc;
// 	Segment a,b,c;
// 	db alen,blen,clen;
// 	db A,B,C;
// };
// typedef Segment Line;
// typedef Point Vector;
// typedef vector<Point> Polygon;

// il db norm(Point c) {return c.x*c.x+c.y*c.y;}
// il db abs(Point c) {return sqrt(norm(c));}
// il db abs(Segment a)
// {
// 	Point k=a.p1-a.p2;
// 	return abs(k);
// }
// il db arg(Vector p) {return atan2(p.y,p.x); }//与x轴夹角
// il Vector polar (db a,db r){return Point(cos(r)*a,sin(r)*a); }//求向量（与x轴夹角为a，长度为r的向量）
// il db dot(Vector a,Vector b){ return a.x*b.x+a.y*b.y; }//内积
// il db cross(Vector a, Vector b){ return a.x*b.y-a.y*b.x; }//外积
// il bool isOrthogonal(Vector a,Vector b){return equals(dot(a,b),0.0);}
// il bool isOrthogonal(Point a1,Point a2,Point b1,Point b2){return isOrthogonal(a1-a2,b1-b2);}
// il bool isOrthogonal(Segment s1,Segment s2){return equals(dot(s1.p1-s1.p2,s2.p1-s2.p2),0.0);}
// il bool isParallel(Vector a,Vector b){return equals(cross(a,b),0.0);}
// il bool isParallel(Point a1,Point a2,Point b1,Point b2){return isParallel(a1-a2,b1-b2);}
// il bool isParallel(Segment s1,Segment s2){return equals(cross(s1.p1-s1.p2,s2.p1-s2.p2),0.0);}
// il Vector getUnitVector(Vector p){return p/abs(p); }
// il int dcmp(db x)
// {
// 	if(equals(x,0.0))return 0;
// 	if(x<0)return -1;
// 	else return 1;
// }
// il int ccw(Point p0,Point p1,Point p2)
// {
// 	Vector a=p1-p0,b=p2-p0;
// 	if(cross(a,b)>eps)return CCW;
// 	if(cross(a,b)<-eps)return CW;
// 	if(dot(a,b)<-eps)return BACK;
// 	if(norm(a)<norm(b))return FRONT;
// 	return ON;
// }
// il Point project(Segment s,Point p)
// {
// 	Vector base=s.p2-s.p1;
// 	db r=dot(p-s.p1,base)/norm(base);
// 	return s.p1+base*r;
// }//投影终点所在坐标
// il db projectlength(Segment s,Point p)
// {
// 	Vector base=s.p2-s.p1;
// 	db r=dot(p-s.p1,base)/abs(base);
// 	return r;
// }//投影长度
// il Point reflect(Segment s,Point p){return p+(project(s,p)-p)*2.0;}//对称点坐标
// il db getDistance(Point a,Point b){return abs(a-b);}
// il db getDistanceLP(Line l,Point p){return fabs(cross(l.p2-l.p1,p-l.p1)/abs(l.p2-l.p1));}
// il db getDistanceSP(Segment s,Point p)
// {
// 	if(dot(s.p2-s.p1,p-s.p1)<0.0)return abs(p-s.p1);
// 	if(dot(s.p1-s.p2,p-s.p2)<0.0)return abs(p-s.p2);
// 	return getDistanceLP(s,p);
// }
// il bool intersect(Point p1,Point p2,Point p3,Point p4)
// {
// 	return (ccw(p1,p2,p3)*ccw(p1,p2,p4)<=0&&
// 			ccw(p3,p4,p1)*ccw(p3,p4,p2)<=0);
// }//不规范相交
// il bool intersect(Segment s1,Segment s2){return (intersect(s1.p1,s1.p2,s2.p1,s2.p2));}
// il db getDistanceSS(Segment s1,Segment s2)
// {
// 	if(intersect(s1,s2))return 0.0;
// 	return min(min(getDistanceSP(s1,s2.p1),getDistanceSP(s1,s2.p2)),
// 			   min(getDistanceSP(s2,s1.p1),getDistanceSP(s2,s1.p2)));
// }
// il Point getCrossPoint(Segment s1,Segment s2)
// {
// 	Vector base=s2.p2-s2.p1;
// 	db d1=fabs(cross(base,s1.p1-s2.p1));
// 	db d2=fabs(cross(base,s1.p2-s2.p1));
// 	db t=d1/(d1+d2);
// 	return s1.p1+(s1.p2-s1.p1)*t;
// }
// il Point getCrossPoint(Point p1,Point p2,Point p3,Point p4)
// {
// 	Segment s1,s2;s1.p1=p1,s1.p2=p2;s2.p1=p3,s2.p2=p4;
// 	return getCrossPoint(s1,s2);
// }
// il Point getCrossPointLL(Line l1,Line l2)
// {
// 	if(intersect(l1,l2))return getCrossPoint(l1,l2);
// 	db x,y;db a1=cross(l1.p2-l1.p1,l2.p1-l1.p1),a2=cross(l1.p2-l1.p1,l2.p2-l1.p1);
// 	x=(a2*l2.p1.x-a1*l2.p2.x)*1.0/(a2-a1);
// 	y=(a2*l2.p1.y-a1*l2.p2.y)*1.0/(a2-a1);
//     return Point(x,y);
// }
// il pair<Point,Point> getCrossPoints(Circle c,Line l)
// {
// 	Vector pr=project(l,c.c);
// 	Vector e=(l.p2-l.p1)/abs(l.p2-l.p1);
// 	db base=sqrt(c.r*c.r-norm(pr-c.c));
// 	return mkp(pr+e*base,pr-e*base);
// }
// il pair<Point,Point>getCrossPoints(Circle c1,Circle c2)
// {
//     db d=abs(c1.c-c2.c);
//     db a=acos((c1.r*c1.r+d*d-c2.r*c2.r)/((db)2*c1.r*d));//余弦定理求角度
//     db t=arg(c2.c-c1.c);
//     return mkp(c1.c+polar(c1.r,t-a),c1.c+polar(c1.r,t+a));
// }
// il Triangle getTriangle(Point a,Point b,Point c)
// {
// 	Triangle k;
// 	k.aa=a,k.bb=b,k.cc=c;
// 	k.a.p1=b;k.a.p2=c;
// 	k.b.p1=a;k.b.p2=c;
// 	k.c.p1=a;k.c.p2=b;
// 	k.alen=abs(a),k.blen=abs(b),k.clen=abs(c);
// 	k.A=acos((k.blen*k.blen+k.clen*k.clen-k.alen*k.alen)/2.0/k.blen/k.clen);
// 	k.B=acos((k.alen*k.alen+k.clen*k.clen-k.blen*k.blen)/2.0/k.alen/k.clen);
// 	k.C=acos((k.blen*k.blen+k.alen*k.alen-k.clen*k.clen)/2.0/k.blen/k.alen);
// 	return k;
// }

// // 判断点是否在多边形内部
// il int contains(Polygon g,Point p)
// {
// 	int n=g.size();
// 	bool x=0;
// 	for(int i=0;i<n;++i)
// 	{
// 		Point a=g[i]-p,b=g[(i+1)%n]-p;
// 		if(abs(cross(a,b))<eps&&dot(a,b)<eps)return 1;
// 		if(a.y>b.y)swap(a,b);
// 		if(a.y<eps&&eps<b.y&&cross(a,b)>eps)x=!x;
// 	}
// 	return x ? 2:0;
// }

// Polygon andrew(Polygon s)//安德鲁算法构建凸包
// {
// 	int n=s.size();
// 	Polygon l,u;//上、下凸包
// 	if(n<3)return s;
// 	sort(s.begin(),s.end());
// 	u.push_back(s[0]);u.push_back(s[1]);
// 	l.push_back(s[n-1]);l.push_back(s[n-2]);
// 	for(int i=2;i<n;++i)
// 	{
// 		for(int j=u.size();j>=2&&(ccw(u[j-2],u[j-1],s[i])!=CW);--j)
// 			u.pop_back();
// 		u.push_back(s[i]);
// 	}
// 	for(int i=n-3;i>=0;--i)
// 	{
// 		for(int j=l.size();j>=2&&ccw(l[j-2],l[j-1],s[i])!=CW;--j)
// 			l.pop_back();
// 		l.push_back(s[i]);
// 	}
// 	reverse(l.begin(),l.end());
// 	for(int i=u.size()-2;i>=1;--i)l.push_back(u[i]);
// 	return l;
// }




// 动态凸包
// Point basic;set<Point>s;
// bool operator<(Point a,Point b)
// {
// 	a=a-basic;b=b-basic;
// 	db ang1=atan2(a.y,a.x),ang2=atan2(b.y,b.x);
// 	db len1=norm(a),len2=norm(b);
// 	if(equals(ang1,ang2))return len1<len2;
// 	else return ang1<ang2;
// }
// set<Point>::iterator Pre(set<Point>::iterator it)
// {
// 	if(it==s.begin())it=s.end();
// 	return --it;
// }
// set<Point>::iterator Nxt(set<Point>::iterator it)
// {
// 	++it;
// 	if(it==s.end())it=s.begin();
// 	return it;
// }
// bool qry(Point p)
// {
// 	set<Point>::iterator it=s.lower_bound(p);
// 	if(it==s.end())it=s.begin();
// 	Point k=*it;
// 	return (cross((p-*(Pre(it))),k-*(Pre(it))))<eps;
// }
// void ins(Point p)
// {
// 	if(qry(p))return ;
// 	s.insert(p);
// 	set<Point>::iterator it=Nxt(s.find(p));
// 	Point k=*it;
// 	while(s.size()>3&&(cross(p-*(Nxt(it)),k-*(Nxt(it))))<eps)
// 	{
// 		s.erase(it);
// 		it=Nxt(s.find(p));
// 		k=*it;
// 	}
// 	it=Pre(s.find(p));
// 	k=*it;
// 	while(s.size()>3&&(cross(p-k,k-*(Pre(it))))>-eps)
// 	{
// 		s.erase(it);
// 		it=Pre(s.find(p));
// 		k=*it;
// 	}
// }