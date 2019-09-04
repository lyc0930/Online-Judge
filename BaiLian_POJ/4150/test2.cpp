
/* version 2:

    对于每一个不是最左和最右的位置，都有四个状态：

        0. 左右没人
        1. 左有人右没人
        2. 左没人右有人
        3. 左右有人

    于是可以考虑将每一个点分为四个状态DP。

        f[i][0] : 坐第 i 个机器时左右无人，于是左下后考虑前面 i-1 个机器，只需考察 f[i-1][2] 和 f[i-1][3]

        f[i][1] : 坐第 i 个机器时左有人右没人，于是先坐完前 i-1 个机器，只考察 f[i-1][0] 和 f[i-1][1]

        同理对 f[i][2] 和 f[i][3]

    最后只需输出 max( f[n][0] , f[n][1] ) 即可

*/

#include<iostream>

using namespace std;

int f[10001][4],a[10001],b[10001],c[10001],n;

int main()

{

	cin>>n;

	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++) cin>>b[i];

	for(int i=1;i<=n;i++) cin>>c[i];

	f[1][0]=a[1],f[1][2]=b[1];

	for(int i=2;i<=n;i++){

		f[i][0]=max(f[i-1][2],f[i-1][3])+a[i];

		f[i][1]=max(f[i-1][0],f[i-1][1])+b[i];

		f[i][2]=max(f[i-1][2],f[i-1][3])+b[i];

		f[i][3]=max(f[i-1][0],f[i-1][1])+c[i];

	}

	cout<<max(f[n][0],f[n][1]);

}
