#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
    // int t = 这里是检查（对拍）次数;
    // while (--t)
    // {
    //     system("这里写数据生成器名称.exe > 这里写数据生成器名称.txt");
    //     system("这里写程序1名称.exe < 这里写数据生成器名称.txt > 这里写程序1名称.txt");
    //     system("这里写程序2名称.exe < 这里写数据生成器名称.txt > 这里写程序2名称.txt");
    //     if (system("fc 这里写程序2名称.txt 这里写程序1名称.txt"))
    //         break;
    // }
    // if (t == 0)
    //     cout << "no error" << endl;
    // else
    //     cout << "error" << endl;

    while (1)
    {
        system("Input.exe > Input.txt");
        system("Output.exe < Input.txt > Right_Answer.txt");
        system("E1-EX.exe < Input.txt > Answer.txt");
        if (system("fc Answer.txt Right_Answer.txt"))
            break;
    }

    return 0;
}