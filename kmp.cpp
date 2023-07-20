// int i,j=0;
// 	nxt[1]=0;int l1=strlen(s1+1),l2=strlen(s2+1);
// 	for(i=2;i<=l2;++i)
// 	{
// 		while(j>0&&s2[j+1]!=s2[i])j=nxt[j];
// 		if(s2[j+1]==s2[i])j++;
// 		nxt[i]=j;
// 	}
// 	i=1,j=0;
// 	while(i<=l1)
// 	{
// 		while(j>0&&s1[i]!=s2[j+1])j=nxt[j];
// 		if(s1[i]==s2[j+1])j++;
// 		if(j==l2)cout<<i-j+1<<'\n',j=nxt[j];i++;
// 	}
// 	for(int i=1;i<=l2;++i)cout<<nxt[i]<<' ';
int nxt[maxn];
void get_nxt(string s)
{
	int cur = 0;
    nxt[0] = 0;
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == s[cur]) {
            nxt[i] = ++cur;
        } else if (cur != 0) {
            cur = nxt[cur - 1];
            i--;
        } else {
            nxt[i] = 0;
        }
    }
}