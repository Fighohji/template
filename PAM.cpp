struct PAM { //在PAM上走能走出所有回文子串
    int sz; // 状态数
    int tot; //字符串长度
    int last; //上一个状态
    int len[maxn]; //对应状态的回文串的长度
    int link[maxn]; //对应的最长回文后缀状态
    int nxt[maxn][26]; //转移边
    char s[maxn]; //字符串
    int newNode(int l) { // 建立一个新节点，长度为 l
        ++sz;
        len[sz] = l;
        /*     清空 不是多组样例注释掉      */
        link[sz] = 0;
        memset(nxt[sz], 0, sizeof(nxt[sz]));
        return sz;
    }
    void init() { //初始化
        sz = -1;
        last = 0;
        s[tot = 0] = '$';
        newNode(0); //偶根
        newNode(-1); //奇根
        link[0] = 1;
    }
    int getPrev(int x) { // 找后缀回文
        while (s[tot - len[x] - 1] != s[tot]) x = link[x];
        return x;
    }
    void insert(char c) {
        s[++tot] = c;
        int now = getPrev(last);
        if (!nxt[now][c - 'a']) {
            int x = newNode(len[now] + 2);
            link[x] = nxt[getPrev(link[now])][c - 'a'];
            nxt[now][c - 'a'] = x;
        }
        last = nxt[now][c - 'a'];
    }
} pam;
