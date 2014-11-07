#include <fstream>
#include <string>



int main()
{
    std::ifstream fin("Input6.txt");
    std::ofstream fout("Output6.txt");

    std::string s;
    std::getline(fin, s);


    return 0;
}
