
struct hashMap{
    int t, n;
    int id[MAX], value[MAX];
    char name[MAX][11];

    hashMap(){
        t = 1;
        n = 9999991;
    }

    void clear(){
        t++;
    }

    int getHash(char *str){
        LL ret = 0;
        int i;

        for(i = 0; str[i] ; i++){
            ret = (ret * hp) % n;
            ret = ret + (str[i]);
        }

        return ret;
    }

    void add(char *str, int marks){
        int x = getHash(str);

        while(id[x] == t){
            if(strcmp(name[x], str) == 0){
                value[x] += marks;
                return;
            }
            x = (x + 1) % n;
        }

        id[x] = t;
        strcpy(name[x], str);
        value[x] = marks;

        return;
    }

    int query_index(char *str){
        int x = getHash(str);

        while(id[x] == t){
            if(strcmp(name[x], str) == 0)
                return x;
            x = (x + 1) % n;
        }
        return -1;
    }

    int query(char *str){
        int p = query_index(str);
        if(p == -1) return 0;
        return value[p];
    }

    void erase(char *str){
        int p = query_index(str);
        if(p == -1) return;
        return (void) (value[p] = 0);
    }
} HM;
