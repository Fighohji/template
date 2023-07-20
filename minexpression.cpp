// il int minexpression(int len,string s)
// {
// 	int minid=0;
// 	for(int i=1,k;i<len;)
// 	{
// 		for(k=1;k<=len;++k)if(s[(i+k-1)%len]!=s[(minid+k-1)%len])break;
// 		if(k>len)break;
// 		if(s[(i+k-1)%len]<s[(minid+k-1)%len])
// 		{
// 			int tmp=i;
// 			i=max(minid+k,tmp+1);
// 			minid=tmp;
// 		}
// 		else i+=k;
// 	}
// 	return minid;
// }