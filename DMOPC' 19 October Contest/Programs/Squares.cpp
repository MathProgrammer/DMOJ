#include <iostream>

using namespace std;

const int MAX_N = 555;
long long minimum_till[MAX_N][MAX_N], grid[MAX_N][MAX_N];

int main()
{
    int rows, columns;
    cin >> rows >> columns;

    for(int i = 1; i <= rows; i++)
    {
        for(int j = 1; j <= columns; j++)
        {
            cin >> grid[i][j];
        }
    }

    for(int i = 1; i <= rows; i++)
    {
        for(int j = 1; j <= columns; j++)
        {
            if(i == 1 && j == 1)
            {
                minimum_till[i][j] = grid[i][j];
            }
            else if(i == 1)
            {
                minimum_till[i][j] = grid[i][j] + minimum_till[i][j - 1];
            }
            else if(j == 1)
            {
                minimum_till[i][j] = grid[i][j] + minimum_till[i - 1][j];
            }
            else
            {
                minimum_till[i][j] = grid[i][j] + min(minimum_till[i - 1][j], minimum_till[i][j - 1]);
            }
        }
    }

    cout << minimum_till[rows][columns] << "\n";
    return 0;
}
