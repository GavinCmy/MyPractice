// 一个树 每个节点有三种衣服可以选 每一种价钱不一样 子节点和父节点要的衣服类型不能一样 求最大价钱
/*
sample in
3
2 4 9
1 3 5
1 2 3
0 1
0 2

sample out
14

6
0 1 2
0 1 2
0 1 2
0 1 2
0 1 2
0 1 2
0 1
0 2
1 3
1 4
2 5
*/
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
using namespace std;

int dp[5005][3];
int h[5005][3];
int f[5005];
int n;
int MAX(int a,int b){
    return a>b?a:b;
}

class node{
    public:
        int id;
        vector<int>nex;
}nodes[5005];

int treeDP(int tmp,int j){//编号i为根的子树 选的j号衣服 的开心值的最大值
    if(nodes[tmp].nex.size()==0){//如果是叶结点 直接返回
        // cout<<"leaf "<<tmp<<" "<<j<<"  "<<dp[tmp][j]<<endl;
        return dp[tmp][j];
    }
    // cout<<"In subTree "<<tmp<<" "<<j<<endl;
    for(int i=0;i<nodes[tmp].nex.size();i++){//加上每个叶结点的最大值
        dp[tmp][j]=dp[tmp][j]+(MAX(treeDP(nodes[tmp].nex[i],(j+1)%3),treeDP(nodes[tmp].nex[i],(j+2)%3)));// j+1 j+2 是为了确保选的衣服和j不一样
    }
    // cout<<"dp "<<tmp<<' '<<j<<"  = "<<dp[tmp][j]<<endl<<endl;
    return dp[tmp][j];
}

int getf(int x){//找到根节点用的
    if(f[x]==x)return x;
    else{
        return f[x]=getf(f[x]);
    }
}
void ini(){//初始化dp为输入的快乐值
    for(int i=0;i<n;i++){
        dp[i][0]=h[i][0];
        dp[i][1]=h[i][1];
        dp[i][2]=h[i][2];
    }
}
int main(){
    
    int root;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>h[i][0]>>h[i][1]>>h[i][2];
    }

    for(int i=0;i<n-1;i++){
        int father,son;
        cin>>father>>son;
        nodes[father].nex.push_back(son);//构造树
        f[son]=father;
        if(i==n-2){
            root = getf(father);
        }
    }
    // cout<<"root "<<root<<endl;
    int ans = 0;
    ini();
    ans = MAX(ans,treeDP(root,0));
    ini();
    ans = MAX(ans,treeDP(root,1));
    ini();
    ans = MAX(ans,treeDP(root,2));
    cout<<ans<<endl;
    system("pause");
    return 0;
}