#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<vector>
#include<climits>

using namespace std;

class zwierzatko
{
    public:
        int czas_startu, liczba_Postoi, czas_drogi, ominieta_ilosc_przeszkod = 0, miejsce_Postoju = 1;
        vector<int>moment_Postoju;

        void czekanie()
        {
            this->czas_drogi++;
        }

};

int main()
{
    ifstream wej("czasy.txt");
    int poziom_Skomplikowania, liczba_Zwierzatek, czas = 1;
    wej >> poziom_Skomplikowania >> liczba_Zwierzatek;
    vector<zwierzatko>Zwierzatka(liczba_Zwierzatek);
    int rozmiar_Toru = 4 + 4 * poziom_Skomplikowania;
    bool czekanie_Wyjscia[2] = {false, false};
    bool pola_Puste[rozmiar_Toru];
    bool potrzeba_Resetu[2] = {false, false};
    int licznik_resetu_Konca[2] = {0,0};
    for(int i = 0; i < rozmiar_Toru; i++)
        pola_Puste[i] = true;

    for(int i = 0; i < liczba_Zwierzatek; i++)
    {
        wej >> Zwierzatka[i].czas_startu >> Zwierzatka[i].liczba_Postoi;
        Zwierzatka[i].czas_drogi = Zwierzatka[i].czas_startu;
    }
    for(int i = 0; i < liczba_Zwierzatek; i++)
    {
        int postoj;
        wej >> postoj;
        if(postoj != -1)
        {
            for(int j = 0; j < Zwierzatka[i].liczba_Postoi; j++)
            {
                if(j != 0)
                    wej >> postoj;
                
                Zwierzatka[i].moment_Postoju.push_back(postoj);
            }
        }
        else
        {
            Zwierzatka[i].moment_Postoju.push_back(postoj);
        }
    }
    vector<int> punkty_wyboru_sciezek;
    for(int i = 0; i <= poziom_Skomplikowania; i++)
    {
        punkty_wyboru_sciezek.push_back(2 + 4 * i);
    }
    vector<int> wystartowaly;
    while(Zwierzatka[Zwierzatka.size()-1].miejsce_Postoju != rozmiar_Toru - 1 || Zwierzatka[Zwierzatka.size()-1].miejsce_Postoju != rozmiar_Toru)
    {
        for(int i = 0 + wystartowaly.size(); i < liczba_Zwierzatek; i++)
        {
            if(czas == Zwierzatka[i].czas_startu)
            {
                Zwierzatka[i].czas_drogi++;      
                wystartowaly.push_back(i);
            }
        }
        for(int i = 0; i < wystartowaly.size(); i++)
        {
            if(czas >= Zwierzatka[wystartowaly.size()-1].czas_startu)
            {
                if(Zwierzatka[i].moment_Postoju[0] == czas)
                {
                    Zwierzatka[i].czekanie();
                    Zwierzatka[i].moment_Postoju.erase(Zwierzatka[i].moment_Postoju.begin());
                }
                else if(Zwierzatka[i].miejsce_Postoju == punkty_wyboru_sciezek[Zwierzatka[i].ominieta_ilosc_przeszkod] && Zwierzatka[i].miejsce_Postoju != punkty_wyboru_sciezek[punkty_wyboru_sciezek.size()-1])
                {
                    if(pola_Puste[Zwierzatka[i].miejsce_Postoju] == true)
                    {
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                        Zwierzatka[i].miejsce_Postoju++;
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                    }
                    else if(pola_Puste[Zwierzatka[i].miejsce_Postoju + 1] == true)
                    {
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                        Zwierzatka[i].miejsce_Postoju += 2;
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                        Zwierzatka[i].ominieta_ilosc_przeszkod++;
                    }
                    else
                    {
                        Zwierzatka[i].czekanie();
                    }
                }
                else if(Zwierzatka[i].miejsce_Postoju < punkty_wyboru_sciezek[punkty_wyboru_sciezek.size()-1] )
                {
                    if(punkty_wyboru_sciezek[Zwierzatka[i].ominieta_ilosc_przeszkod] + 1 == Zwierzatka[i].miejsce_Postoju)
                    {
                        if(pola_Puste[Zwierzatka[i].miejsce_Postoju + 1] == true)
                        {
                            pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                            Zwierzatka[i].miejsce_Postoju += 2;
                            pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                            Zwierzatka[i].ominieta_ilosc_przeszkod++;
                        }
                        else
                        {
                            Zwierzatka[i].czekanie();
                        }
                    }
                    else
                    {
                        if(pola_Puste[Zwierzatka[i].miejsce_Postoju] == true)
                        {
                            pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                            Zwierzatka[i].miejsce_Postoju++;
                            pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                        }
                        else
                        {
                            Zwierzatka[i].czekanie();
                        }
                    }
                        
                }
                else if(Zwierzatka[i].miejsce_Postoju < rozmiar_Toru - 1)
                {
                    if(pola_Puste[Zwierzatka[i].miejsce_Postoju] == true)
                    {
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                        Zwierzatka[i].miejsce_Postoju++;
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                        potrzeba_Resetu[0] = true;
                        cout << czas +1 << ' ' << Zwierzatka[i].miejsce_Postoju <<endl;
                    }
                    else if(pola_Puste[Zwierzatka[i].miejsce_Postoju + 1] == true)
                    {
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = true;
                        Zwierzatka[i].miejsce_Postoju += 2;
                        pola_Puste[Zwierzatka[i].miejsce_Postoju-1] = false;
                        potrzeba_Resetu[1] = true;
                        cout << czas + 1 << ' ' << Zwierzatka[i].miejsce_Postoju << endl;
                    }
                    else
                    {
                        Zwierzatka[i].czekanie();
                    }
                }
            }
        }
        czas++;
        if(potrzeba_Resetu[0] == true)
            licznik_resetu_Konca[0]++;
        
        if(potrzeba_Resetu[1] == true)
            licznik_resetu_Konca[1]++;

        if(licznik_resetu_Konca[0] == 2)
        {
            licznik_resetu_Konca[0] = 0;
            pola_Puste[rozmiar_Toru-2] = true;
            potrzeba_Resetu[0] = false;
        }
        if(licznik_resetu_Konca[1] == 2)
        {
            licznik_resetu_Konca[1] = 0;
            pola_Puste[rozmiar_Toru-1] = true;
            potrzeba_Resetu[1] = false;
        }
    }

    getchar();
    getchar();
    return 0;
}