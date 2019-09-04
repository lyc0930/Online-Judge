#include <iostream>
#include <cstring>
using namespace std;
void mult(char a[],char b[],char s[])//高精乘
{
    int i, j, k = 0, alen, blen, sum = 0, res[200][200] = {{0}};
    char result[200];
    alen=strlen(a);blen=strlen(b);
    for (i=0;i<alen;i++)
    for (j=0;j<blen;j++) res[i][j]=(a[i]-'0')*(b[j]-'0');
    for (i=alen-1;i>=0;i--)
    {
    for (j=blen-1;j>=0;j--) sum=sum+res[i+blen-j-1][j];
    result[k]=sum%10;
    k=k+1;
    sum=sum/10;
    }
    for (i=blen-2;i>=0;i--)
    {
    for (j=0;j<=i;j++) sum=sum+res[i-j][j];
    result[k]=sum%10;
    k=k+1;
    sum=sum/10;
    }
    if (sum!=0) {result[k]=sum;k=k+1;}
    for (i=0;i<k;i++) result[i]+='0';
    for (i=k-1;i>=0;i--) s[i]=result[k-1-i];
    s[k]='\0';
    while(1)
    {
    if (strlen(s)!=strlen(a)&&s[0]=='0')
    strcpy(s,s+1);
    else
    break;
    }
}//mult
int main()
{
    int i,pl,k,n,t,z,c,j;char r[6],rr[200],b[200],all[9];int re[200];
    while(scanf("%s%d",all,&n)!=EOF)
    {
        k=0;
        memset(r,0,sizeof(r));
        memset(rr,0,sizeof(rr));
        memset(b,0,sizeof(b));
        memset(re,0,sizeof(re));
        for(i=0;i<=5;++i)
        {
            if ((all[i])=='.') pl=i;
            else r[k++]=all[i];
        }//把底数去掉小数点，放入r中
        pl=strlen(r)-pl;//计算小数位数
        strcpy(rr,r);
        for (i=2;i<=n;++i) mult(r,rr,rr);//计算结果
        i=strlen(rr)-1;z=0;
        while ((rr[i]=='0')&&(i>strlen(rr)-pl*n)) {z++;--i;}
        if (i==strlen(rr)-pl*n) z++;//计算后置0数z
        c=0;
        while(rr[c]=='0')c++;//计算前置0数c
        t=strlen(rr)-pl*n-c;//计算小数点位置t
        if (t<0) //t小于0时在小数点后补0，并输出
            {
                printf(".");
                for(j=1;j<=-t;++j) printf("0");
            }
        for (i=c;i<=strlen(rr)-1-z;++i) //输出计算结果
        {
            if (i==t) printf(".");
            printf("%c",rr[i]);
        }
        printf("\n");
    }
    return 0;
}