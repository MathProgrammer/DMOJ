#include <iostream>
#include <vector>

using namespace std;

const int MAX_VALUE = 2e5 + 5;
vector <int> suffix_sum(MAX_VALUE, 0);

int read_person(int length, int base)
{
    int effective_no = 0;
    vector <int> D(length + 1);
    for(int i = 1; i <= length; i++)
    {
        cin >> D[i];
    }

    for(int i = 1; i <= length; i++)
    {
        effective_no = (effective_no*base) + D[i];
    }

    return effective_no;
}

void print(int n)
{
    vector <int> D;
    while(n > 0)
    {
        D.push_back(n%11);
        n /= 11;
    }

    for(int i = D.size() - 1; i >= 0; i--)
    {
        int d = D[i];
        cout << d << " ";
    }
    cout << "\n";
}

int main()
{
    int no_of_people, no_of_problems, maximum_score;
    cin >> no_of_problems >> maximum_score >> no_of_people;

    for(int i = 1; i <= no_of_people; i++)
    {
        int effective_no = read_person(no_of_problems, maximum_score); //cout << "Number = " << effective_no << "\n"; print(effective_no);

        suffix_sum[effective_no]++;
    }

    int max_score = 0;
    for(int base = 1, d = no_of_problems; d >= 1; d--, base *= maximum_score)
    {
        for(int score = MAX_VALUE - 1; score >= 0; score--)
        {
            int digit_d = (score/base)%maximum_score;

            if(digit_d == maximum_score - 1 || score + base > MAX_VALUE)
            {
                continue;
            }

            suffix_sum[score] += suffix_sum[score + base];

            if(suffix_sum[score] > max_score)
            {
                max_score = suffix_sum[score];
              //cout << "D = " << digit_d << " Base = " << base << " Adding " << base << " to "; print(score); cout << " to get "; print(score + base); cout << "\n";
            }
        }
    }

    int no_of_queries;
    cin >> no_of_queries;

    for(int i = 1; i <= no_of_queries; i++)
    {
        int effective_no = read_person(no_of_problems, maximum_score);

        cout << suffix_sum[effective_no] << "\n";
    }

    return 0;
}
