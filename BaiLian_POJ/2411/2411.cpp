//Mondriaan's Dream
#include <algorithm>
#include <cstring>
#include <iostream>
#define AND &&
#define OR ||
#define NOT !
//规范, 所有位运算状态变量统一加上前缀 bit_
using namespace std;

int height, width;
long long F[1005][2050];//这个范围是必须的
//F[i][bit_j] 表示填充第 i 列, 第 i-1 列对它的影响是 bit_j 的时候的方法数。i <= width , 0 <= bit_j < 2^height

void Construct(int i, int j, int bit_state, int bit_next) //DFS
//第 i 列, 枚举到了第 j 行(0 -> height - 1), 当前状态是 bit_state, 对下一列的影响是 bit_next
{
    if (j == height) //对行枚举结束
    {
        F[i + 1][bit_next] += F[i][bit_state];
        return;
    }
    if (((1 << j) & bit_state) > 0)               //如果 bit_state 的第 j+1 位是 1, 即这个位置已经被上一列所占用
        Construct(i, j + 1, bit_state, bit_next); //直接跳过

    if (((1 << j) & bit_state) == 0)                         //如果 bit_state 的第 j+1 位是 0, 即这个位置是空的
        Construct(i, j + 1, bit_state, bit_next | (1 << j)); //尝试放一个 1*2 的, 不应改变 state 因为这个分量形容影响

    if ((j + 1 < height) AND(((1 << j) & bit_state) == 0) AND(((1 << (j + 1)) & bit_state) == 0)) //如果这个位置以及下一个位置都是空的
        Construct(i, j + 2, bit_state, bit_next);                                                 //尝试放一个2*1的
    return;
}

int main()
{
    while (cin >> height >> width)
    {
        memset(F, 0, sizeof(F));
        if ((height == 0) AND(width == 0))
            break;
        F[0][0] = 1;
        for (int i = 0; i < width; i++)
        {
            for (int bit_state = 0; bit_state < (1 << height); bit_state++)
                if (F[i][bit_state])
                {
                    Construct(i, 0, bit_state, 0);
                }
        }
        cout << F[width][0] << endl;
    }
}
