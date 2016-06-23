#include <iostream>
#include <cmath>
using namespace std;
/*
Il faut compiler ce programme avec C++ 11
Auteur : Pierre KURZAWSKI
OS : Arch Linux x64
G++ : 5.2.0
*/

int menuChoix() //Demande quelle transformation l'user va choisir, elle retourne un entier
{
    int choixTransformation;
    cout << "Utilitaire de conversion IEEE 754" << endl;
    cout << endl;
    cout << "Choisissez votre transformation : " << endl;
    cout << "[1] - Décimal -> Simple Précision (32 Bits)" << endl;
    cout << "[2] - Décimal -> Double Précision (64 Bits)" << endl;
    cout << "[3] - Simple Précision (32 Bits) -> Décimal" << endl;
    cout << "[4] - Double Précision (64 Bits) -> Décimal" << endl;
    cout << "> ";
    cin >> choixTransformation;
    return choixTransformation;
}
/*
 * Décimal vers simple && double précision
 */
string saisieString() //L'user saisie un string
{
    string saisie;
    cout << "Veuillez saisir une valeur : ";
    cin >> saisie;
    return saisie;
}

string signe(string chaine)
{
    string res = "";
    if(chaine[0] == '-')
        res = "1";
    else
        res = "0";
    return res;
}

int recupPartieEntiere(string chaine) //Retourne la partie entiere du float et le converti en int
{
    string partieEntiere;
    int positionDuPoint = chaine.find(".");
    partieEntiere = chaine.substr(0, positionDuPoint);
    return stoi(partieEntiere);
}

float recupPartieDecimale(string chaine) //Retourne la partie decimale d'un float
{
    string partieDecimale;
    int positionDuPoint = chaine.find(".");
    partieDecimale = "0." + chaine.substr(positionDuPoint +1, chaine.size());
    return stof(partieDecimale);
}

string toBin(int partEnt) //Converti un nbre bin
{
    string binRes;
    while(partEnt != 0)
    {
        if(partEnt % 2 == 0)
            binRes = "0" + binRes;
        else
            binRes = "1" + binRes;
        partEnt /= 2;
    }
    if(binRes == "")
        binRes = "0";
    return binRes;
}

string decimalToBin(float partDec)
{
    string res = "";
    while(partDec != 0.0)
    {
        partDec *= 2;

        if(partDec >= 1)
        {
            res += "1";
            partDec -= 1;
        }
        else
            res += "0";
    }
    return res;
}

string expToBin(int partEnt, int tailleMax) //Converti un nbre bin
{
    string binRes;
    while(partEnt != 0)
    {
        if(partEnt % 2 == 0)
            binRes = "0" + binRes;
        else
            binRes = "1" + binRes;
        partEnt /= 2;
    }
    if(binRes == "")
        binRes = "0";
    if (binRes.length() != 8)
    {
        while(binRes.length() != tailleMax)
            binRes.insert(0,1,'0');
    }
    else
        return binRes;
}

string exposantSP(string partEnt, string partDec)
{
    int exp = 23;
    if(partEnt != "0")
        exp += partEnt.size() - 1;
    else if (partDec != "")
    {
        int i = 0;
        while(partDec[i] != '1')
            i++;
        exp -= i +1;
    }
    string res = expToBin(exp,8);
    return res;
}

string exposantDP(string partEnt, string partDec)
{
    int exp = 52;
    if(partEnt != "0")
        exp += partEnt.size() - 1;
    else if (partDec != "")
    {
        int i = 0;
        while(partDec[i] != '1')
            i++;
        exp -= i +1;
    }
    string res = expToBin(exp,11);
    return res;
}

/*
 * IEEE 754 (32 && 64 Bits)  vers Décimal
 */

string saisieIEEE_32bits_String()
{
    string saisie;
    cout << "Veuillez saisir un mot binaire de 32 Bits (Simple Précision) : ";
    cout << endl;
    cout << "-> ";
    cin >> saisie;

    if(saisie.length() != 32)
    {
        cout << "Ceci n'est pas un mot binaire sur 32 Bits !" << endl;
        cout << "Veuillez recommencer !" << endl;
        cout << '\n';
        saisieIEEE_32bits_String();
    }
    else
        return saisie;
}

string saisieIEEE_64bits_String() //Idem mais pour une longueur de 64
{
    string saisie;
    cout << "Veuillez saisir un mot binaire de 64 Bits (Double Précision) : ";
    cout << endl;
    cout << "-> ";
    cin >> saisie;
    if(saisie.length() != 64)
    {
        cout << "Ceci n'est pas un mot binaire sur 64 Bits !" << endl;
        cout << "Veuillez recommencer !" << endl;
        cout << '\n';
        saisieIEEE_64bits_String();
    }
    else
        return saisie;
}

int recupSigne(string s)
{
    if (s[0] == '0')
        return 1;
    return -1;
}

string recupExposantIEEE_SP(string motBin)
{
    string res = motBin.substr(1, 8);
    return res;
}

string recupExposantIEEE_DP(string motBin)
{
    string res = motBin.substr(1, 12);
    return res;
}

string recupMantisse_SP(string motBin)
{
    string res ="";
    for(int i = 9; i < motBin.size(); i++)
        res += motBin[i];
    return res;
}

string recupMantisse_DP(string motBin)
{
    string res ="";
    for(int i = 12; i < motBin.size(); i++)
        res += motBin[i];
    return res;
}

int binToInt(string motBin)
{
    int res = 0;
    int currentPow = 1;
    for(int i = motBin.length() -1 ; i >= 0; i--)
    {
        if (motBin[i] == '1')
            res += currentPow;
        currentPow *= 2;
    }
    return res;
}

string removeZero(string partDec) //on retire les zéros superflus de la partie décimale
{
    string tmp = "", s = "";
    for(int i = 0 ; i < partDec.length(); i++)
    {
        tmp +=  partDec[i];
        if(partDec[i] == '1')
        {
            s += tmp;
            tmp = "";
        }
    }
    return s;
}

double binToFloat_SP(string motBin)
{
    string partEnt = "", partDec = "";
    for(int i = 0; i < 23+1; i++)
        if (i < 23)
            partEnt += motBin[i];
        else
            partDec += motBin[i];
    removeZero(partDec);
    int entier = 0;
    double decimal =0;
    entier = binToInt(partEnt);

    double pow = 0.5;
    for(int i = 0; i < partDec.length(); i++)
    {
        if (partDec[i] == '1')
            decimal += pow;
        pow /= 2;
    }
    return entier + decimal;
}

double binToFloat_DP(string motBin)
{
    motBin = "1"+motBin;
    string partEnt = "", partDec = "";
    string s = "", tmp = "";
    for(int i = 0; i < 52+1; i++)
        if (i < 52)
            partEnt += motBin[i];
        else
            partDec += motBin[i];
    removeZero(partDec);
    int entier = 0;
    double decimal =0;

    entier = binToInt(partEnt);

    double pow = 0.5;
    for(int i = 0; i < partDec.length(); i++)
    {
        if (partDec[i] == '1')
            decimal += pow;
        pow /= 2;
    }
    return entier + decimal;
}

void floatToSimpleIEEE()
{
    string chaine = saisieString();
    string dec = decimalToBin(recupPartieDecimale(chaine));
    string ent = toBin(recupPartieEntiere(chaine));
    string exp = exposantSP( toBin(recupPartieEntiere(chaine)), decimalToBin(recupPartieDecimale(chaine)) );
    while(ent.size() + dec.size() != 23)
    {
        dec += "0";
        if(dec.size() > 23) {
            string tmp = "";
            for (int i = 0; i < 23; i++) {
                tmp[i] += dec[i];
            }
            dec = tmp;
        }
    }
    string final = signe(chaine) + " " + exp + " " + ent+dec;
    cout << "Après conversion : " << final << endl;
    cout << "                   " << "S   E                  M" << endl;
}

void floatToDoubleIEEE()
{
    string chaine = saisieString();
    string dec = decimalToBin(recupPartieDecimale(chaine));
    string ent = toBin(recupPartieEntiere(chaine));
    string exp = exposantDP(toBin(recupPartieEntiere(chaine)), decimalToBin(recupPartieDecimale(chaine)));
    while(ent.size() + dec.size() != 52)
    {
        dec += "0";
    }
    if(dec.size() > 52) {
        string tmp = "";
        for (int i = 0; i < 52; i++) {
            tmp[i] += dec[i];
        }
        dec = tmp;
    }
    string final = signe(chaine) + " " + exp + " " + ent + dec;
    cout << "Après conversion : " << final << endl;
    cout << "                   " << "S      E                           M" << endl;
}

void simpleIEEEtoFloat()
{
    string chaine = saisieIEEE_32bits_String();
    string chaine1 =  recupMantisse_SP(chaine);
    int expo = binToInt(recupExposantIEEE_SP(chaine));
    double nb = binToFloat_SP(chaine1);
    cout << nb << endl;

}

void doubleIEEEtoFloat()
{
    string chaine = saisieIEEE_64bits_String();
    string chaine1 = recupMantisse_DP(chaine);
    int expo = binToInt(recupExposantIEEE_DP(chaine));
    double nb = binToFloat_DP(chaine1);
    cout << nb << endl;
}

void switchConversion(int c) //Fonction qui suit le choix de l'user par rapport au menu
{
    switch(c)
    {
        case 1:
            floatToSimpleIEEE();
            break;

        case 2:
            floatToDoubleIEEE();
            break;

        case 3:
            simpleIEEEtoFloat();
            break;

        case 4:
            doubleIEEEtoFloat();
            break;

        default:
        {
            cerr << "Erreur ! Faites un choix valide compris entre 1 et 4 ! " << endl;
            exit(1);
            break;
        }
    }
}

int main()
{
    switchConversion(menuChoix());
    return 0;
}
