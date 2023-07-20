struct SAM
{
    vector<vector<int> >nxt;//转移
    vector<int>len;//长度
    vector<int>link;//后缀链接
    vector<vector<int> >e;//后缀树
    vector<int>sz;//endpos集大小
    int last,cnt;//上一个状态和状态数总数
    void init(int strlen,int chrsize)//字符串大小，字符集大小
    {
        len.clear();link.clear();nxt.clear();sz.clear();e.clear();
        last=cnt=1;//初始状态空集
        len.resize(1+strlen<<1,0);
        link.resize(1+strlen<<1,0);
        nxt.resize(1+strlen<<1,vector<int>(chrsize+1,0));
        sz.resize(1+strlen<<1,0);
    }
    void add(string s)
    {
        for(auto i:s)
            add(i - 'a');
    }
    void add(int c)
    {
        int p=last,cur=++cnt;
        sz[cur]=1;
        len[cur]=len[p]+1;
        //情况1 直接扩展
        while(p&&!nxt[p][c])
        {
            nxt[p][c]=cur;
            p=link[p];
        }
        last=cur;
        if(!p)link[cur]=1;
        else
        {
            int q=nxt[p][c];
            //情况2-A 建立新的后缀链接
            if(len[q]==len[p]+1)link[cur]=q;
            //情况2-B 拆点建立
            else
            {
                int cl=++cnt;
                len[cl]=len[p]+1;
                nxt[cl]=nxt[q],link[cl]=link[q];
                link[cur]=link[q]=cl;
                while(p&&nxt[p][c]==q)
                {
                    nxt[p][c]=cl;
                    p=link[p];
                }
            }
        }
    }
}sam;