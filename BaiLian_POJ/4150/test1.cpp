
/* version 1:

	记：

		f[i].before 为前 i 个机器在第 i 台机器先于第 i+1 台机器坐人的情况下能力值和的最大值

		f[i].after 为前 i 个机器在第 i 台机器后于第 i+1 台机器坐人的情况下能力值和的最大值

	显然我们有

		f[1].before=a[1] , f[1].after=b[1]

	假若我们已经知道了 f[i-1].before 和 f[i-1].after ，即在第 i 个位置没人和有人的情况下前 i-1 个机器能力值的最大

	对于 f[i].before 而言， 即第 i+1 个机器上还没坐人时，那么考虑第 i 个机器和第 i-1 个机器有人的时间顺序

		如果第 i 个机器坐人后于第 i-1 个机器坐人，那么必然坐第 i 个机器的能力值为 b[i] ，因为它左边有人右边没人

		对前 i-1 个机器，由于第 i 个机器后于第 i-1 个机器坐人，这时 f[i].before = f[i-1].before+b[i]

		如果第 i 个机器坐人先于第 i-1 个机器坐人，那么 f[i].before = f[i-1].after+a[i]

  	同理对于 f[i].after ， f[i].after = max( f[i-1].before+c[i] , f[i-1].after+b[i] )，还是第 i 台和第 i-1 台机器坐人的顺序问题

	即：对于 i>=2 ，我们有

		f[i].before = max( f[i-1].before+b[i] , f[i-1].after+a[i] )---(1)

		f[i].after = max( f[i-1].before+c[i] , f[i-1].after+b[i] )---(2)

	这样下去，由于第 n 台机器右边始终为空，不会坐人，故所求即为 f[n].before

*/

#include <iostream>
#define MAX 10000
using namespace std;

struct Condition
{
	int before, after;
};


int main()

{

	int n;
	int a[MAX + 1], //左右都无人 both
		b[MAX + 1], //左或右有人 either
		c[MAX + 1]; //左右都有人 neither
	struct Condition F[MAX + 1];
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= n; i++)
		cin >> b[i];

	for (int i = 1; i <= n; i++)
		cin >> c[i];

	F[1].before = a[1];
	F[1].after = b[1];

	for (int i = 2; i <= n; i++)
	{

		F[i].before = max(F[i - 1].before + b[i], F[i - 1].after + a[i]);

		F[i].after = max(F[i - 1].before + c[i], F[i - 1].after + b[i]);
	}

	cout << F[n].before;
}
