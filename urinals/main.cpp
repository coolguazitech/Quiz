/*
    This is a problem I came up with on a whim, when I was in a toilet, it put
    me in mind all of a sudden. I saw that each man wouldn't be willing to use
    the urinal right next to another occupied, what I want to know is, if the-
    re are n urinals arranged in a sequence, under my assumption, how many si-
    tuations will happen at a time? Let's restate the problem: If we have a 1D
    array of size n with its elements equal to either 0 or 1, and at least on-
    e 0 between two 1s, then how many ways can fill this array? Let the answe-
    r be f(n). I would adopt dynamic programming to solve this problem.
*/

#include <iostream>
#include <algorithm>

using namespace std;

/*
    solve by DP, linear time and linear space complexities
*/
unsigned long long f(int n)
{
    if(n == 1){return 2;}
    if(n == 2){return 3;}
    unsigned long long table[n];
    fill(table, table + n, 0);
    table[0] = 2;
    table[1] = 3;
    int count = 1;

    while(++count < n)
    {
        table[count] = table[count - 1] + table[count - 2];
    }

    return table[n - 1];
}

int main()
{
    int n;

    cout << "Please input a positive integer n: ";
    cin >> n;
    
    cout << "f(" << n << ") = " << f(n) << endl;

    system("pause");
}