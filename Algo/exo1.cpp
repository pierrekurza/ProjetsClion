#include <iostream>
#include <string>
#define NB_VOYELLES 12
using namespace std;


 void nbVoyellesConsonnes(string s, char tabVoy[NB_VOYELLES])
{
    int voyelle = 0;

    for(int i = 0; i < s.size(); i++)
    {
        for (int j = 0 ; j < NB_VOYELLES; j++)
        {
            if(s[i] == tabVoy[j])
                voyelle++;
        }

    }
    int consonnes = s.size() - voyelle;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == ' ')
            consonnes -= 1;
    }
    cout << "il y a " << voyelle << " Voyelles" << endl;
    cout << "il y a " << consonnes << " Consonnes" << endl;
}

int main()
{
    string saisie;
    char tabVOyelles[NB_VOYELLES] = {'a','e','i','o','u','y','A','E','I','O','U','Y'};
    cout << "Saisissez une phrase : ";
    getline(cin,saisie);
    nbVoyellesConsonnes(saisie, tabVOyelles);
    return 0;
}
