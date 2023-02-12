
// 2D BIT
int max_x, max_y, tree[MAX+10][MAX+10]; //An array, suppose arr[MAX][MAX]
// 1 based indexing

void update(int x , int y , int val) //Updating arr[x][y]
{
    int y1;
    while (x <= max_x)
    {
        y1 = y;
        while (y1 <= max_y)
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
