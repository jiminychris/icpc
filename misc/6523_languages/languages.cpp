#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>


using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::unordered_map;

int main(int argc, char *argv[])
{
    int numLanguages;
    char c;
    int i, j, k;
    string name;
    string word;
    string line;
    stringstream linestream;
    unordered_map<string, string> languageMap;

    cin >> numLanguages;
    getline(cin, line);

    for (i=0; i<numLanguages; i++)
    {
        getline(cin, line);
        linestream.clear();
        linestream.str(string());
        linestream << line;
        linestream >> name;
        while (linestream >> word)
        {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            languageMap[word] = name;
        }
    }

    getline(cin, line);
    while (getline(cin, line))
    {
        linestream.clear();
        linestream.str(string());
        linestream << line;
        while (1)
        {
            c = linestream.get();
            while (linestream && !(c == '-' || c == '\'' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
                c = linestream.get();
            word = "";
            while (c == '-' || c == '\'' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            {
                word.append(1, c);
                c = linestream.get();
            }
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (languageMap.count(word))
            {
                cout << languageMap[word] << endl;
                break;
            }
        }
    }

    return 0;
}
