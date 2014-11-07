#include <iostream>
#include <vector>
#include <algorithm>


enum Operations {
    SUM,
    DIFF,
    MULT
};



int main()
{
    int N;
    std::cin >> N;

    std::vector<int> v(N);
    for (int i = 0; i < N; ++i)
        std::cin >> v[i];


    return 0;
}
