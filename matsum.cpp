#include <iostream>
#include<string.h>
using namespace std;
int t[1050][1050];
int v[1050][1050];
      void update(int x , int y , int val, int n){
                x = x + 1;
                y = y + 1;
                while (x <= n){
                        int y1 = y;
                        while (y1 <= n){
                                t[x][y1] += val;
                                y1 += (y1 & -y1);
                        }
                        x += (x & -x);
                }
        }

        int sum(int xx , int yy){
                int x = xx + 1;
                int y = yy + 1;
                int sum = 0;
                while (x > 0){
                        int y1 = y;
                        while (y1 > 0){
                                sum += t[x][y1];
                                y1 -= (y1 & -y1);
                        }
                        x -= (x & -x);
                }

                return sum;
        }

int main() {
	
	int T,x1,y1,x2,y2, n;
    int ans,val;
    char ch[5];
    scanf("%d",&T);
    while(T--)
    {
         scanf("%d",&n);
         memset(t,0,sizeof(t));
         memset(v,0,sizeof(v));
         while(scanf("%s",ch))
         {
             if(ch[0]=='E')break;
             if(ch[1]=='E')
             {
                scanf("%d%d%d",&x1,&y1,&val);
				
                update(x1,y1,val-v[x1][y1], n);
                v[x1][y1] = val;
             }
             else
             {
                 scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                 ans=sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1);
				 printf("%d\n",ans);                 
             }
         }
         printf("\n");
    }

	return 0;
}
