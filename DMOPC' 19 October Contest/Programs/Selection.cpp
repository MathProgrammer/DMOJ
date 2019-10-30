#include <iostream>
#include <cstring>

#define LEFT(n) (2*n)
#define RIGHT(n) (2*n + 1)
using namespace std;

const int MAX_N = 5e5 + 5, MAX_VALUE = 25;
int frequency_tree[3*MAX_N][MAX_VALUE + 1], A[MAX_N], no_of_elements, no_of_queries;

int get_sum(int x, int n, int left, int right, int query_left, int query_right)
{
    if(right < left || query_right < left || right < query_left)
        return 0;

    if(query_left <= left && right <= query_right)
    {
        return frequency_tree[n][x];
    }

    int mid = (left + right)/2;
    int left_sum = get_sum(x, LEFT(n), left, mid, query_left, query_right);
    int right_sum = get_sum(x, RIGHT(n), mid + 1, right, query_left, query_right);

    return (left_sum + right_sum);
}

void update(int x, int n, int left, int right, int position, int value)
{
    if(right < position || position < left)
        return;

    if(left == right)
    {
        frequency_tree[n][x] = value;
        return;
    }

    int mid = (left + right)/2;

    update(x, LEFT(n), left, mid, position, value);
    update(x, RIGHT(n), mid + 1, right, position, value);

    frequency_tree[n][x] = frequency_tree[LEFT(n)][x] + frequency_tree[RIGHT(n)][x];
}

void perform_update(int position, int new_value)
{
    int current_value = A[position];

    if(current_value == new_value)
    {
        return;
    }

    update(current_value, 1, 1, no_of_elements, position, 0);

    A[position] = new_value;
    update(new_value, 1, 1, no_of_elements, position, 1);
}

int get_k_best(int left, int right, int k)
{
    for(int i = MAX_VALUE; i >= 0; i--)
    {
        int frequency_i = get_sum(i, 1, 1, no_of_elements, left, right);

        if(frequency_i >= k)
        {
            return i;
        }

        k -= frequency_i;
    }
}

int main()
{
    cin >> no_of_elements >> no_of_queries;

    memset(frequency_tree, 0, sizeof(frequency_tree));

    for(int i = 1; i <= no_of_elements; i++)
    {
        cin >> A[i];

        update(A[i], 1, 1, no_of_elements, i, 1);
    }

    for(int i = 1; i <= no_of_queries; i++)
    {
        const int UPDATE = 1, QUERY = 2;
        int query_type;

        cin >> query_type;

        if(query_type == UPDATE)
        {
            int position, new_value;
            cin >> position >> new_value;

            perform_update(position, new_value);
        }
        else if(query_type == QUERY)
        {
            int left, right, k;
            cin >> left >> right >> k;

            int answer = get_k_best(left, right, k);
            cout << answer << "\n";
        }
    }
    return 0;
}
