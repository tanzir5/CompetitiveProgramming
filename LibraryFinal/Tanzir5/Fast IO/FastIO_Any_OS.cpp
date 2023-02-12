//   ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
/// never use c style printf scanf with the above

/// works for negative numbers
/// fastRead_string was never tested by me.
/// Remember to fix data type

inline void Read(int &a)
{
    int cc = getc(stdin);
    for (; (cc < '0' || cc > '9') && (cc!='-');)  cc = getc(stdin);
    bool neg = false;
    if(cc == '-')
    {
        neg = true;
        cc = getc(stdin);
    }
    int ret = 0;
    for (; cc >= '0' && cc <= '9';)
    {
        ret = ret * 10 + cc - '0';
        cc = getc(stdin);
    }
    if(neg)
        ret = -ret;
    a = ret;
}

inline void Read_string(char *str)
{

    register char c = 0;
    register int i = 0;

    while (c < 33)
        c = getc(stdin);

    while (c != '\n' && c != ' ')
    {
        str[i] = c;
        c = getc(stdin);
        i = i + 1;
    }
    str[i] = '\0';
}

inline void print(int a)
{

    if(a < 0)
    {
        putc('-',stdout);
        a = -a;
    }
    char s[11];
    int t = -1;
    do
    {
        s[++t] = a % 10 + '0';
        a /= 10;
    }
    while(a > 0);
    while(t >= 0)putc(s[t--],stdout);
}
