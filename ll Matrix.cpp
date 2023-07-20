struct Matrix
{
	int siz;
	ll mat[101][101];
	void init()
	{
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				mat[i][j]=0;
	}
	Matrix operator+(const Matrix &t)
	{
		Matrix ans;ans.siz=siz;
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				ans.mat[i][j]=mat[i][j]+t.mat[i][j];
		return ans;
	}
	Matrix operator-(const Matrix &t)
	{
		Matrix ans;ans.siz=siz;
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				ans.mat[i][j]=mat[i][j]-t.mat[i][j];
		return ans;
	}
	Matrix operator*(const Matrix &t)
	{
		Matrix ans={0};ans.siz=siz;
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				for(int k=1;k<=siz;++k)
					ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*t.mat[k][j])%mod;
		return ans;
	}
	Matrix operator*(const ll &t)
	{
		Matrix ans;ans.siz=siz;
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				ans.mat[i][j]=mat[i][j]*t;
		return ans;
	}
	Matrix operator/(const ll &t)
	{
		Matrix ans;ans.siz=siz;
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				ans.mat[i][j]=mat[i][j]/t;
		return ans;
	}
	Matrix operator +=(const Matrix &t) {return (*this)=(*this)+t;}
	Matrix operator -=(const Matrix &t) {return (*this)=(*this)-t;}
	Matrix operator *=(const Matrix &t) {return (*this)=(*this)*t;}
	Matrix operator *=(const ll &t) {return (*this)=(*this)*t;}
	Matrix operator /=(const ll &t) {return (*this)=(*this)/t;}
	Matrix UnitMatrix()
	{
		Matrix ans;
		ans.siz=siz;
		for(int i=1;i<=ans.siz;++i)ans.mat[i][i]=1;
		return ans;
	}
	Matrix qpow(ll power)
	{
		Matrix tmp=(*this);
		(*this)=UnitMatrix();
		while(power)
		{
			if(power&1)(*this)=(*this)*tmp;
			tmp=tmp*tmp;
			power>>=1;
		}
		return (*this);
	}
	void print()
	{
		for(int i=1;i<=siz;++i)
			for(int j=1;j<=siz;++j)
				cout<<mat[i][j]<<(j==siz ? '\n':' ');
	}
};