#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
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