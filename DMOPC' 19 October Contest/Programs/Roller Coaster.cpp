#include <iostream>

using namespace std;

int main()
{
    int no_of_elements, min_height, max_height;
    cin >> no_of_elements >> min_height >> max_height;

    int no_of_good_elements = 0;
    for(int i = 1; i <= no_of_elements; i++)
    {
        int height;
        cin >> height;

        no_of_good_elements += (min_height <= height && height <= max_height);
    }

    cout << no_of_good_elements;
    return 0;
}
