
//2D Segment Tree

const int inf = 1000000000;
struct segTree{
    int arr[MAX<<2];

    segTree(){
        for(int i = 0; i < (MAX << 2); i++) arr[i] = inf;
    }

    void update(int idx, int st, int ed, int pos, int val, vector<int> &nodeList){
        nodeList.push_back(idx);

        if(st == ed){
            arr[idx] = val;
            return;
        }

        int mid = (st+ed)/2, l = idx << 1, r = l | 1;
        if(pos <= mid) update(l, st, mid, pos, val, nodeList);
        else update(r, mid+1, ed, pos, val, nodeList);

        arr[idx] = min(arr[l], arr[r]);
    }

    int query(int idx, int st, int ed, int i, int j)
    {
        if(st == i && ed == j) return arr[idx];

        int mid = (st+ed)/2, l = idx << 1, r = l | 1;
        if(j <= mid) return query(l, st, mid, i, j);
        if(i > mid) return query(r, mid+1, ed, i, j);
        else return min(query(l, st, mid, i, mid), query(r, mid+1, ed, mid+1, j));
    }
};

struct _2DsegTree{
    segTree segArr[MAX<<2];
    vector<int> affected_nodes;

    void update(int idx, int st, int ed, int i, int j, int val){
        if(st == ed){
            affected_nodes.clear();
            segArr[idx].update(1, 1, MAX, j, val, affected_nodes);
            return;
        }

        int mid = (st+ed)/2, l = idx << 1, r = l|1;
        if(i <= mid) update(l, st, mid, i, j, val);
        else update(r, mid+1, ed, i, j, val);

        for(int p = 0; p < affected_nodes.size(); p++)
        {
            int q = affected_nodes[p];
            segArr[idx].arr[q] = min(segArr[l].arr[q], segArr[r].arr[q]);
        }
    }

    int query(int idx, int st, int ed, int st_r, int ed_r, int st_c, int ed_c){
        assert(st_r <= ed_r && st_c <= ed_c);

        if(st == st_r && ed == ed_r) return segArr[idx].query(1, 1, MAX, st_c, ed_c);

        int mid = (st+ed)/2, l = idx << 1, r = l | 1;
        if(ed_r <= mid) return query(l, st, mid, st_r, ed_r, st_c, ed_c);
        else if(st_r > mid) return query(r, mid+1, ed, st_r, ed_r, st_c, ed_c);
        return min(query(l, st, mid, st_r, mid, st_c, ed_c), query(r, mid+1, ed, mid+1, ed_r, st_c, ed_c));
    }
};
