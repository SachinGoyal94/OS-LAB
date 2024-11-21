#include<bits/stdc++.h>
using namespace std;
int k=0;
vector<int>check(3,0);
bool final=1;
void bankersAlgorithm(vector<vector<int>> &all,vector<vector<int>> &need,vector<int> &avl) 
{
    for(int i=0;i<need.size();i++)
    {
        if(!check[i])
        {
            int confirm=1;
            for(int j=0;j<need[0].size();j++)
            {
                if(need[i][j]>avl[j])
                    confirm=0;
            }
            if(confirm )
            {
                for(int j=0;j<need[0].size();j++)
                {
                    avl[j]+=all[i][j];
                    all[i][j]=0;
                    need[i][j]=0;
                    check[i]=1;
                }
            }
        }
    }
    k++;
    if(k!=need.size())
    {
        bankersAlgorithm(all,need,avl);
    }
    
}
int main() 
{
    vector<vector<int>> allocation1 = 
    {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 1, 0, 0}
    };
    vector<vector<int>> max1 = 
    {
        {2, 1, 1, 1},  
        {1, 2, 1, 2},  
        {1, 1, 1, 1}
    }; 
    vector<int> available1 = {1, 1, 2, 1};

    vector<vector<int>>need(max1.size(),vector<int>(max1[0].size()));

    for(int i=0;i<max1.size();i++)
    {
        for(int j=0;j<max1[0].size();j++)
        {
            need[i][j]=max1[i][j]-allocation1[i][j];
        }
    }

    bankersAlgorithm(allocation1,need, available1);

    for(int i=0;i<need.size();i++)
    {
        if(check[i]==0)
            final=0;
    }
    cout<<" result time ";
    cout<<final;
}