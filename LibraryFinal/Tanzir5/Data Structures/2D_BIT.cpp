// 1 based indexing
int mxIdx_x, mxIdx_y, tree[MAX+10][MAX+10]; //An array, suppose arr[MAX][MAX]
void init(int nx, int ny)
{
    mxIdx_x = nx;
    mxIdx_y = ny;
    mem(tree,0);
}
void update(int x , int y , int val) //Updating arr[x][y]
{
    int y1;
    while (x <= mxIdx_x)
    {
        y1 = y;
        while (y1 <= mxIdx_y)
        {
            tree[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}
int query(int x , int y) // Cumulative sum from arr[1][1] to arr[x][y]
{
    int y1, ret = 0;
    while (x)
    {
        y1 = y;
        while (y1)
        {
            ret += tree[x][y1];
            y1 -= (y1 & -y1);
        }
        x -= (x & -x);
    }
    return ret;
}
int query_rectangle(int x1, int y1, int x2, int y2) // sum of the values enclosed by the rectangle x1,y1 and x2,y2 where x1,y1 is the lower corner.
{
    int ret = query(x2,y2);
    ret -= query(x2, y1-1);
    ret -= query(x1-1, y2);
    ret += query(x1-1,y1-1);
    return ret;
}
