#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

class notacja_wykladnicza
{
    public:
        double mantysa;
        int wykladnik = 0;           //moze dziala nie wiadomo
    
    
    string str_notacja()
    {
        string _mantysa = to_string(mantysa);
        string _wykladnik = " *10(" + to_string(wykladnik) + ")";
        _mantysa.erase ( _mantysa.find_last_not_of('0') + 1, string::npos );
        if(_mantysa[_mantysa.size()-1] == '.')
            _mantysa.erase(_mantysa.size()-1);
        if(mantysa < 0)
            return '(' + _mantysa + ')' + _wykladnik;
        else
            return _mantysa + _wykladnik;
    }
    void normalizacja(string wczytana_liczba)
    {
        wykladnik = 0;
        double normalizowana_Liczba = stod(wczytana_liczba);
        while(abs(normalizowana_Liczba) >= 10)
        {
            normalizowana_Liczba /= 10;
            wykladnik++;
        }
        while(abs(normalizowana_Liczba) < 1)
        {
            normalizowana_Liczba *= 10;
            wykladnik--;
        }
        mantysa = normalizowana_Liczba;
    }
    void debug_wyswietl()
    {
        cout << mantysa << ' ' << wykladnik << ' ' << str_notacja() << endl;
    }     
    double nieznormalizowana()
    {
        if(wykladnik > 0)
            return mantysa * (10 * abs(wykladnik));
        else if(wykladnik < 0)
             return mantysa / (10 * abs(wykladnik));
        else return mantysa;
    }  
};
int szukaj_symbolu(vector<char> symbole_Matematyczne, vector<char> kolejnosc_Dzialan)
{
    int wynik = 0;
    for(int i = 0; i < kolejnosc_Dzialan.size(); i++)
    {
        for(int j = 0; j < symbole_Matematyczne.size(); j++)
        {
            if(kolejnosc_Dzialan[i] == symbole_Matematyczne[j])
            {
                return j;
            }
        }
    }
}

string dzialanie_Wynik(char numer_dzialania, vector<char> symbole_Matematyczne, notacja_wykladnicza liczba1, notacja_wykladnicza liczba2)
{
    string wynik;
    if(symbole_Matematyczne[numer_dzialania] == '+')
        return to_string(liczba1.nieznormalizowana() + liczba2.nieznormalizowana());
    else if(symbole_Matematyczne[numer_dzialania] == '-')
        return to_string(liczba1.nieznormalizowana() - liczba2.nieznormalizowana());
    else if(symbole_Matematyczne[numer_dzialania] == '*')
        return to_string(liczba1.nieznormalizowana() * liczba2.nieznormalizowana());
    else
        return to_string(liczba1.nieznormalizowana() / liczba2.nieznormalizowana());
}

int main()
{
    ifstream wej("normalizacja.txt");
    int ilosc_Liczb;
    wej >> ilosc_Liczb;
    vector<notacja_wykladnicza> Liczby(ilosc_Liczb);
    vector<char> symbole_Matemayczne(ilosc_Liczb-1);
    vector<char> kolejnosc_Dzialan;
    int ilosc_Dzialan = symbole_Matemayczne.size();

    for(int i = 0; i < Liczby.size(); i++)
    {
        string liczba;
        wej >> liczba;
        Liczby[i].normalizacja(liczba);
    }
    for(int i = 0; i < symbole_Matemayczne.size(); i++)
        wej >> symbole_Matemayczne[i];

    //for(int i = 0; i < Liczby.size(); i++)
        //Liczby[i].debug_wyswietl();

    for(int i = 0; i < symbole_Matemayczne.size(); i++)
    {
        if(symbole_Matemayczne[i] == '*' || symbole_Matemayczne[i] == '/')
            kolejnosc_Dzialan.push_back(symbole_Matemayczne[i]);
    }
    for(int i = 0; i < symbole_Matemayczne.size(); i++)
    {
        if(symbole_Matemayczne[i] == '+' || symbole_Matemayczne[i] == '-')
            kolejnosc_Dzialan.push_back(symbole_Matemayczne[i]);
    }

    for(int i = 0; i < Liczby.size(); i++)
    {
        if(i < Liczby.size() - 1)
            cout << Liczby[i].str_notacja() << ' ' << symbole_Matemayczne[i] << ' ';
        else 
            cout << Liczby[i].str_notacja() << ' ';
    }
    for(int i = 0; i < ilosc_Dzialan; i++)
    {
        cout << endl;
        int numer_dzialania = szukaj_symbolu(symbole_Matemayczne, kolejnosc_Dzialan);
        string wynik = dzialanie_Wynik(numer_dzialania, symbole_Matemayczne, Liczby[numer_dzialania], Liczby[numer_dzialania + 1]);
        Liczby[numer_dzialania].normalizacja(wynik);
        symbole_Matemayczne.erase(symbole_Matemayczne.begin() + numer_dzialania);
        kolejnosc_Dzialan.erase(kolejnosc_Dzialan.begin());
        Liczby.erase(Liczby.begin() + numer_dzialania + 1);
        for(int i = 0; i < Liczby.size(); i++)
        {
            if(i < Liczby.size() - 1)
                cout << Liczby[i].str_notacja() << ' ' << symbole_Matemayczne[i] << ' ';
            else 
                cout << Liczby[i].str_notacja() << ' ';
        }

    }
    getchar();
    getchar();
    return 0;
}