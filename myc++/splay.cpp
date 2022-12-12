#include <bits/stdc++.h>
using namespace std;
struct node{
    int num,cnt,size;
    node *son[2],*fa;
    node(){
        this->son[0] = this->son[1] = NULL;
        num = cnt = size = 0;
    }
    void update(){
        this->size = this->cnt;
        if(son[0] != NULL) this->size += son[0]->size;
        if(son[1] != NULL) this->size += son[1]->size;
    }
    int get(){
        if(this->fa == NULL) return -1;
        return (this->fa->son[1] == this);
    }
    void clear(){
        this->size = this->cnt = this->num = 0;
        this->fa = this->son[0] = this->son[1] = NULL;
    }
    void rotate(){
        int op = this->get();
        if(op == -1) return;
        int opt = this->fa->get();
        node *tmp = this->son[!op],*emp = this->fa->fa;
        this->son[!op] = this->fa;this->son[!op]->fa = this;
        this->son[!op]->son[op] = tmp;
        if(tmp != NULL) this->son[!op]->son[op]->fa = this->son[!op];
        this->fa = emp;
        if(opt != -1) emp->son[opt] = this;
        this->son[!op]->update();this->update();
    }
    void splay(node *f){
        while(this->fa != f){
            if(this->fa->get() == -1) this->rotate();
            else if(this->get() == this->fa->get()) {this->fa->rotate();this->rotate();}
            else {this->rotate();this->rotate();}
        }
    }
    node *mge(node *tmp){
        node *p = this;
        while(p->son[1] != NULL) p = p->son[1];
        p->splay(this->fa);
        p->son[1] = tmp;
        if(tmp != NULL) tmp->fa = p;
        p->update();
        return p;
    }
    void print(){
        if(this->son[0] != NULL) this->son[0]->print();
        printf("%d ",this->num);
        if(this->son[1] != NULL) this->son[1]->print();
    }
};
struct Tree{
    node *root;
    Tree() {this->root = NULL;}
    void insert(int x){
        if(this->root == NULL){
            node *p = new node;
            this->root = p;
            p->cnt = 1;p->num = x;p->size = 1;
            p->fa = p->son[0] = p->son[1] = NULL;
            return;
        }
        int type = -1;
        node *f = NULL;
        node *p = this->root;
        while(true){
            if(p == NULL){
                node *q = new node;
                q->cnt = 1;q->num = x;q ->size = 1;
                q->fa = f; f->son[type] = q;
                q->son[0] = q->son[1] = NULL;
                q->splay(NULL);
                this->root = q;
                return;
            }
            if(p->num == x){
                p->cnt += 1;
                p->update();
                p->splay(NULL);
                this->root = p;
                return;
            }
            p->size += 1;
            f = p;
            type = (p->num<x);
            p = p->son[type];
        }
    }
    void erase(int x){
        if(this->root == NULL) return;
        int type = -1;
        node *f = NULL;
        node *p = this->root;
        while(true){
            if(p == NULL) return;
            if(p->num == x){
                p->splay(NULL);
                this->root = p;
                p->cnt -= 1;
                p->update();
                if(p->fa != NULL)p->fa->update();
                if(p->cnt == 0){
                    if(p->son[0] != NULL)this->root = p->son[0]->mge(p->son[1]);
                    else this->root = p->son[1];
                    if(this->root != NULL)this->root->fa = NULL;
                    p->clear();
                    delete p;
                }
                return;
            }
            f = p;
            type = (p->num>x);
            p = p->son[type];
        }
    }
    int rk(int x){
        this->insert(x);
        int ans = this->root->son[0]->size+1;
        this->erase(x);
        return ans;
    }
    int kth(int x){
        if(this->root == NULL) return -1;
        int nums = x-1;
        node *p = this->root;
        while(true){
            if(p == NULL) return -1;
            if((p->son[0] == NULL ? 0 : p->son[0]->size) > nums) p = p->son[0];
            else if((p->son[0] == NULL ? 0 : p->son[0]->size) + p->cnt > nums){
                p->splay(NULL);
                this->root = p;
                return p->num;
            }
            else{
                nums -= p->son[0] == NULL ? 0 : p->son[0]->size + p->cnt;
                p = p->son[1];
            }
        }
    }
    int low(int x){
        this->insert(x);
        node *p = this->root->son[0];
        while(p->son[1] != NULL) p = p->son[1];
        int ans = p->num;
        this->erase(x);
        return ans;
    }
    int upp(int x){
        this->insert(x);
        node *p = this->root->son[1];
        while(p->son[0] != NULL) p = p->son[0];
        int ans = p->num;
        this->erase(x);
        return ans;
    }
    void check(){
        this->root->print();
        putchar('\n');
    }
}tree;

int main(){
    tree.insert(2147483647);
    tree.insert(-2147483647);
    int n,opt,x;
    cin >> n;
    while(n--){
        cin >> opt >> x;
        switch (opt)
        {
        case 1:
            tree.insert(x);
            break;
        case 2:
            tree.erase(x);
            break;
        case 3:
            cout << tree.rk(x) - 1 << endl;
            break;
        case 4:
            cout << tree.kth(x+1) << endl;
            break;
        case 5:
            cout << tree.low(x) << endl;
            break;
        case 6:
            cout << tree.upp(x) << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}