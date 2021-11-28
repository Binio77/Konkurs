#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;


class anagram
{
    public:
        vector<int> X;
        vector<int> Y;

};


int rzad(int n, vector<vector<char>>& tablica_znakow,  int numer_wyrazu, string wzor, int suma_znakow_Wzoru, anagram *wsk_poziome)                          //szuka anagramów w wyrazach
{
    int bledy_alg_Andrzeja = 0;
    bool znaleziono = false;
    for(int i = 0; i < n - (wzor.size()-1); i++)
    {
        string wyraz;
        int suma_znakow_Wyrazu = 0;
        for(int j = 0; j < wzor.size(); j++)
        {
            suma_znakow_Wyrazu += tablica_znakow[numer_wyrazu][i+j];
            wyraz += tablica_znakow[numer_wyrazu][i+j];
        }

        if(suma_znakow_Wzoru == suma_znakow_Wyrazu)
        {
            sort(wzor.begin(), wzor.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == wzor)
            {
                cout << i << ' ';
                znaleziono = true;
                wsk_poziome->Y.push_back(numer_wyrazu);
                wsk_poziome->X.push_back(i);
            }
            else
            {
                bledy_alg_Andrzeja++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return bledy_alg_Andrzeja;
}

int kolumna(int m, vector<vector<char>>& tablica_znakow,  int numer_kolumny, string wzor, int suma_znakow_Wzoru, anagram*wsk_pionowe)
{
    bool znaleziono = false;
    string wyraz;
    int bledy_alg_Andrzeja = 0;
    for(int i = 0; i < m - (wzor.size()-1); i++)
    {
        string wyraz;
        int suma_znakow_Wyrazu = 0;
        for(int j = 0; j < wzor.size(); j++)
        {
            suma_znakow_Wyrazu += tablica_znakow[i+j][numer_kolumny];
            wyraz += tablica_znakow[i+j][numer_kolumny];
        }

        if(suma_znakow_Wzoru == suma_znakow_Wyrazu)
        {
            sort(wzor.begin(), wzor.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == wzor)
            {
                cout << i << ' ';
                znaleziono = true;
                wsk_pionowe->X.push_back(numer_kolumny);
                wsk_pionowe->Y.push_back(i);
            }
            else
            {
                bledy_alg_Andrzeja++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return bledy_alg_Andrzeja;
}
int przekatnaLP(int m, int n, vector<vector<char>>& tablica_znakow, string wzor, int suma_znakow_Wzoru)
{
    int bledy_alg_Andrzeja = 0;
    bool znaleziono = false;
    for(int i = 0; i < m - (wzor.size()-1); i++)
    {
        string wyraz;
        int suma_znakow_Wyrazu = 0;
        for(int j = 0; j < wzor.size(); j++)
        {
            suma_znakow_Wyrazu += tablica_znakow[i+j][i+j];
            wyraz += tablica_znakow[i+j][i+j];
        }
        if(suma_znakow_Wzoru == suma_znakow_Wyrazu)
        {
            sort(wzor.begin(), wzor.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == wzor)
            {
                cout << i << ' ';
                znaleziono = true;
            }
            else
            {
                bledy_alg_Andrzeja++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return bledy_alg_Andrzeja;
}
int przekatnaPL(int m, int n, vector<vector<char>>& tablica_znakow, string wzor, int suma_znakow_Wzoru)
{
    int bledy_alg_Andrzeja = 0;
    bool znaleziono = false;
    for(int i = 0; i < m - (wzor.size()-1); i++)
    {
        string wyraz;
        int suma_znakow_Wyrazu = 0;
        for(int j = 0; j < wzor.size(); j++)
        {
            suma_znakow_Wyrazu += tablica_znakow[i+j][n-j-1-i];
            wyraz += tablica_znakow[i+j][n-j-1-i];
        }
        if(suma_znakow_Wzoru == suma_znakow_Wyrazu)
        {
            sort(wzor.begin(), wzor.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == wzor)
            {
                cout << i << ' ';
                znaleziono = true;
            }
            else
            {
                bledy_alg_Andrzeja++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return bledy_alg_Andrzeja;
}

int srodek_anagramu_poziomego(int poczatek_anagramu, int dlugosc_wzoru)
{
    return poczatek_anagramu + dlugosc_wzoru/2;
}

int main()
{
    ifstream wej("tekst.txt");
    int m, n;
    string wzor;
    int suma_bledy_alg_Andrzeja = 0;                               
                                                //slowo wzorcowe      
                                                //m to liczba tekstow
                                                //n liczba znaków
    wej >> m >> n >> wzor;

    vector<vector<char>>tablica_znakow;
    anagram anagramy_poziome;
    anagram*wsk_poziome = &anagramy_poziome;
    anagram anagramy_pionowe;
    anagram*wsk_pionowe = &anagramy_pionowe;
    int suma_znakow_Wzoru = 0;
    for(int i = 0; i < m; i++)
    {
        string wyraz;
        wej >> wyraz;
        vector<char>v;
        for(int j = 0; j < n; j++)
        {
            v.push_back(wyraz[j]);
        }
        tablica_znakow.push_back(v);
    }
    for(int i = 0; i < m ;i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << tablica_znakow[i][j]<<' ';
        }
        cout << endl;
    }
    for(int i = wzor.size()-1; i >= 0; i--)
    {
        suma_znakow_Wzoru += (int)wzor[i];
    }

    for(int i = 0; i < m; i++)
        suma_bledy_alg_Andrzeja += rzad(n, tablica_znakow, i, wzor, suma_znakow_Wzoru, wsk_poziome);
    
    cout << endl<<endl;

    for(int i = 0; i < n; i++)
        suma_bledy_alg_Andrzeja += kolumna(m, tablica_znakow, i, wzor, suma_znakow_Wzoru, wsk_pionowe);
       
    
    cout << endl<<endl;
    
    if(m == n)
    {
        suma_bledy_alg_Andrzeja += przekatnaLP(m, n, tablica_znakow, wzor, suma_znakow_Wzoru);
        cout << endl<<endl;
        suma_bledy_alg_Andrzeja += przekatnaPL(m, n, tablica_znakow, wzor, suma_znakow_Wzoru);
        cout << endl<<endl;
    }

    if(wzor.size() % 2 != 0)
    {
        int licznik_liter_T = 0;
        for(int iteracja_pozioma = 0; iteracja_pozioma < anagramy_poziome.X.size(); iteracja_pozioma++)
        {
            for(int interacja_pionowa = 0; interacja_pionowa < anagramy_pionowe.X.size(); interacja_pionowa++)
            {
                if(srodek_anagramu_poziomego(anagramy_poziome.X[iteracja_pozioma], wzor.size()) == anagramy_pionowe.X[interacja_pionowa] && 
                    anagramy_poziome.Y[iteracja_pozioma]-1 == anagramy_pionowe.Y[interacja_pionowa])
                    licznik_liter_T++;
            }
        }
        cout << licznik_liter_T << endl;
    }
    cout << suma_bledy_alg_Andrzeja;
    getchar();
    getchar();
    return 0;
}