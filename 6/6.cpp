#include <fstream>
#include <string>




std::string decrypt(std::string &s)
{
    std::string result;

    for (auto i = 0ul; i < s.size(); ++i) {

    }
}


int main()
{
    std::ifstream fin("Input6.txt");
    std::ofstream fout("Output6.txt");

    std::string s;
    std::getline(fin, s);

    fout << decrypt(s);

    return 0;
}
