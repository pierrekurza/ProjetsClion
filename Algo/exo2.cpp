#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void anagramme(string chaine1, string chaine2)
{
    if(chaine1.size() == chaine2.size())
    {
        sort(chaine1.begin(), chaine1.end());
        sort(chaine2.begin(), chaine2.end());
        if(chaine1 == chaine2)
            cout << "Ce sont des anagrammes !" << endl;
        else
        {
            cout << "Ce ne sont pas des ananas" << endl;
            cout << "Mais se sont des fraises" << endl;
        }
    }
    else
        cout << "Ce ne sont pas des anagrammes " << endl;
}

int main()
{
    string un;
    string deux;
    cout << "Entrez 2 mots en MAJUSCULES :" << endl;
    cout << "-> ";
    cin >> un >> deux;
    anagramme(un,deux);
    return 0;
}

