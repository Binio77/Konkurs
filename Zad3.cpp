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

int rzad(int n, vector<vector<char>>& vec,  int numer_wyrazu, string x, int sumka_X, anagram *wsk)                          //szuka anagramów w wyrazach
{
    int licznik = 0;
    bool znaleziono = false;
    for(int i = 0; i < n - (x.size()-1); i++)
    {
        string wyraz;
        int sumka_W = 0;
        for(int j = 0; j < x.size(); j++)
        {
            sumka_W += vec[numer_wyrazu][i+j];
            wyraz += vec[numer_wyrazu][i+j];
        }

        if(sumka_X == sumka_W)
        {
            sort(x.begin(), x.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == x)
            {
                cout << i << ' ';
                znaleziono = true;
                wsk->Y.push_back(numer_wyrazu);
                wsk->X.push_back(i);
            }
            else
            {
                licznik++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return licznik;
}

int kolumna(int m, vector<vector<char>>& vec,  int numer_kolumny, string x, int sumka_X, anagram*wsk)
{
    bool znaleziono = false;
    string wyraz;
    int licznik = 0;
    for(int i = 0; i < m - (x.size()-1); i++)
    {
        string wyraz;
        int sumka_W = 0;
        for(int j = 0; j < x.size(); j++)
        {
            sumka_W += vec[i+j][numer_kolumny];
            wyraz += vec[i+j][numer_kolumny];
        }

        if(sumka_X == sumka_W)
        {
            sort(x.begin(), x.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == x)
            {
                cout << i << ' ';
                znaleziono = true;
                wsk->X.push_back(numer_kolumny);
                wsk->Y.push_back(i);
            }
            else
            {
                licznik++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return licznik;
}
int przekatnaLP(int m, int n, vector<vector<char>>& vec, string x, int sumka_X)
{
    int licznik = 0;
    bool znaleziono = false;
    for(int i = 0; i < m - (x.size()-1); i++)
    {
        string wyraz;
        int sumka_W = 0;
        for(int j = 0; j < x.size(); j++)
        {
            sumka_W += vec[i+j][i+j];
            wyraz += vec[i+j][i+j];
        }
        if(sumka_X == sumka_W)
        {
            sort(x.begin(), x.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == x)
            {
                cout << i << ' ';
                znaleziono = true;
            }
            else
            {
                licznik++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return licznik;
}
int przekatnaPL(int m, int n, vector<vector<char>>& vec, string x, int sumka_X)
{
    int licznik = 0;
    bool znaleziono = false;
    for(int i = 0; i < m - (x.size()-1); i++)
    {
        string wyraz;
        int sumka_W = 0;
        for(int j = 0; j < x.size(); j++)
        {
            sumka_W += vec[i+j][n-j-1-i];
            wyraz += vec[i+j][n-j-1-i];
        }
        if(sumka_X == sumka_W)
        {
            sort(x.begin(), x.end());
            sort(wyraz.begin(), wyraz.end());
            if(wyraz == x)
            {
                cout << i << ' ';
                znaleziono = true;
            }
            else
            {
                licznik++;
            }

        }
    }
    if(znaleziono == false)
        cout << "-1";

    cout << endl;
    return licznik;
}


int main()
{
    ifstream wej("tekst.txt");
    int m, n;
    string x;
    int bledy = 0;                               
                                                //slowo wzorcowe      
                                                //m to liczba tekstow
                                                //n liczba znaków
    wej >> m >> n >> x;

    vector<vector<char>>vec;
    anagram poziome;
    anagram*wsk1 = &poziome;
    anagram pionowe;
    anagram*wsk2 = &pionowe;
    int sumka_X = 0;
    for(int i = 0; i < m; i++)
    {
        string wyraz;
        wej >> wyraz;
        vector<char>v;
        for(int j = 0; j < n; j++)
        {
            v.push_back(wyraz[j]);
        }
        vec.push_back(v);
    }
    for(int i = 0; i < m ;i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << vec[i][j]<<' ';
        }
        cout << endl;
    }
    for(int i = x.size()-1; i >= 0; i--)
    {
        sumka_X += (int)x[i];
    }

    for(int i = 0; i < m; i++)
        bledy += rzad(n, vec, i, x, sumka_X, wsk1);
    
    cout << endl<<endl;

    for(int i = 0; i < n; i++)
        bledy += kolumna(m, vec, i, x, sumka_X, wsk2);
       
    
    cout << endl<<endl;
    
    if(m == n)
    {
        bledy += przekatnaLP(m, n, vec, x, sumka_X);
        cout << endl<<endl;
        bledy += przekatnaPL(m, n, vec, x, sumka_X);
        cout << endl<<endl;
    }
    //cout << bledy;
    if(x.size() % 2 != 0)
    {
        int licznik_T = 0;
        for(int i = 0; i < poziome.X.size(); i++)
        {
            for(int j = 0; j < pionowe.X.size(); j++)
            {
                if(poziome.X[i] + x.size()/2 == pionowe.X[j] && poziome.Y[i]-1 == pionowe.Y[j])
                    licznik_T++;
            }
        }
        cout << licznik_T;
    }
    getchar();
    getchar();
    return 0;
}