#include <iostream>
using namespace std;

string reverseString(string s)
{
    string tmp ="";
    for (int i = s.size() - 1 ; i >= 0; i--)
    {
        tmp += s[i];
    }
    return tmp;
}

int main()
{
    string chaine;
    cout << "Entrez une phrase : " ;
    getline(cin,chaine);
    string mdr = reverseString(chaine);
    if(chaine == mdr)
        cout << "C'est un palindrome GG" << endl;
    else
        cout << "Ceci n'est pas un palindrome" << endl;
}
