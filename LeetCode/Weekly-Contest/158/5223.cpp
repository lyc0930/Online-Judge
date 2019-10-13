#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king)
    {
        vector<vector<int>> Threatening_Queens;
        vector<int> temp;
        bool Board[8][8] = {0};
        for (int i = 0; i < queens.size(); i++)
            Board[queens[i][0]][queens[i][1]] = true;
        // WN
        for (int i = king[0], j = king[1]; i >= 0 && j >= 0; i--, j--)
        {
            if (Board[i][j])
            {
                temp.push_back(i);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // N
        for (int j = king[1]; j >= 0; j--)
        {
            if (Board[king[0]][j])
            {
                temp.push_back(king[0]);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // EN
        for (int i = king[0], j = king[1]; i < 8 && j >= 0; i++, j--)
        {
            if (Board[i][j])
            {
                temp.push_back(i);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // W
        for (int i = king[0]; i >= 0; i--)
        {
            if (Board[i][king[1]])
            {
                temp.push_back(i);
                temp.push_back(king[1]);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // E
        for (int i = king[0]; i < 8; i++)
        {
            if (Board[i][king[1]])
            {
                temp.push_back(i);
                temp.push_back(king[1]);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // WS
        for (int i = king[0], j = king[1]; i >= 0 && j < 8; i--, j++)
        {
            if (Board[i][j])
            {
                temp.push_back(i);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // S
        for (int j = king[1]; j < 8; j++)
        {
            if (Board[king[0]][j])
            {
                temp.push_back(king[0]);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        // ES
        for (int i = king[0], j = king[1]; i < 8 && j < 8; i++, j++)
        {
            if (Board[i][j])
            {
                temp.push_back(i);
                temp.push_back(j);
                Threatening_Queens.push_back(temp);
                temp.clear();
                break;
            }
        }
        return Threatening_Queens;
    }
};