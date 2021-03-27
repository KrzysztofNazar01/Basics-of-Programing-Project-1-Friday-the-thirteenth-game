#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct karta
{
    int wartosc=0;
    char kolor[10] = {0};
};

struct gracz{
    karta hand[100];
    karta deck[100];
};

struct kociol{
    karta pile[100];
};

void ustaw_zielone(karta *player, int b, char (*kolor)[7], int zw);
void ustaw_niezielone(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][7]);
void pukladaj(int zi, int ki, int nzi, int lg, gracz *player , karta *talia);
void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr);
void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr);
void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr);
void wypisz_koncowy(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr);


int main(){ 
    //gracz gracze[7];

  char kolorki[8][7] = {  
    {"green"} ,   /*  row indexed by 0 */
    {"blue"} ,   /* row indexed by 1 */
    {"red"}  , /*  row indexed by 2 */
    {"violet"},
    {"yellow"},
    {"white"},
    {"black"} /*  row indexed by 6 */
};  

    int kolejka=0;
    int liczba_graczy=0;
    int kociolki_ilosc=0;
    int zielone_ilosc=0;
    int zielone_wartosc=0;
    int niezielone_ilosc=0;


//wpisywanie danych do utworzenia gry
    cin >> liczba_graczy;
    cin >> kociolki_ilosc;
    cin >> zielone_ilosc;
    cin >> zielone_wartosc;
    cin >> niezielone_ilosc;

const int wszystkie_karty=(niezielone_ilosc*kociolki_ilosc)+zielone_ilosc; //ilosc kart w calej talii
 
kociol *kociolki = new kociol[kociolki_ilosc+1]; //utworzenie kociolkow, kociolki numerowane od "1"
gracz *gracze = new gracz[liczba_graczy+1];  //utworzenie graczy, gracze numerowani od "1"
karta *talia = new karta[wszystkie_karty]; //utworzenie talii, karty numerowane od "0" do "wszystkie karty-1"
int *niezielone_wartosc = new int[niezielone_ilosc]; //tablica dla niezielonych wartosci

for(int i=0; i<niezielone_ilosc; ++i) //wpisanie niezielonych wartosci
        cin >> niezielone_wartosc[i];


ustaw_zielone(talia, zielone_ilosc, &kolorki[0], zielone_wartosc);

ustaw_niezielone(talia, zielone_ilosc, niezielone_ilosc, kociolki_ilosc, niezielone_wartosc, kolorki);

fopen("program.txt","w");//otworz plik
    FILE *fptr; //wskaznik na plik

    fptr = fopen("program.txt","w"); 
    if(fptr == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

kolejka++; // kolejna runda
    cout << "active player = " << kolejka << endl;
    cout << "players number = " << liczba_graczy << endl;

fprintf(fptr, "active player = %d\n", kolejka); 
fprintf(fptr, "players number = %d\n", liczba_graczy); 
   

pukladaj( zielone_ilosc,  kociolki_ilosc,  niezielone_ilosc,liczba_graczy,gracze, talia );

wypisz_koncowy(liczba_graczy, kociolki_ilosc, gracze, wszystkie_karty, kociolki, &fptr);
 
//usuwanie tablic dynamicznych - unikniecie memory leak
    delete [] talia;
    delete [] niezielone_wartosc;
    delete [] gracze;
    delete [] kociolki;

return 0;

}

void ustaw_zielone(karta *player, int b, char (*kolor)[7], int zw)
{
   for(int i=0; i<b; ++i)
    {
        strcpy(player[i].kolor,(*kolor)); //przypisanie zielonego koloru
        player[i].wartosc= zw; //przypisanie wartosci dla zieloych kart
    }
}

void ustaw_niezielone(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][7])
{
    for(int m=1; m<ki+1; m++)
    {        
        for(int k=zi+(m-1)*nzi; k<zi+(1+m-1)*nzi; k++)
        {         
            strcpy(player[k].kolor,kolorki[m]); //przypisanie niezielonych kolorow
            player[k].wartosc= nzw[(k-zi)-(m-1)*nzi]; //przypisanie niezielonych wartosci
        }    
    }
}

void pukladaj(int zi, int ki, int nzi, int lg, gracz *player , karta *talia)
{
    int nr_karty=0; 
    int numer_gracza=1;
        for(int i=0; i<zi+ki*nzi; i++)
        {   
            player[numer_gracza].hand[nr_karty] = talia[i];
            
            if((i+1) % (lg ) == 0)
            {
                numer_gracza=0;
                nr_karty++;
            }
            
            numer_gracza++;  
        }
}

void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr)
{
    cout << i << "player hand cards: ";
    fprintf(*fptr, "%d %s ",  i, "player hand cards:");

        for(int j=0; j<wszystkie_karty; j++)
        {
            //koniec wypisywania kart dla danego gracza
            if(player[i].hand[j].wartosc==0)
            break;

            //wypisza karty danego gracza
            cout << player[i].hand[j].wartosc << " " << player[i].hand[j].kolor << " ";
            

            fprintf(*fptr," %d ", player[i].hand[j].wartosc);//zapisanie w pliku
            int results = fputs(player[i].hand[j].kolor,*fptr);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
        }
        cout << endl;
        fprintf(*fptr,"\n");
}

void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr)
{
    cout << i << "player deck cards: ";
fprintf(*fptr, "%d %s ",  i, "player deck cards:");
            for(int j=0; j<wszystkie_karty; j++)
            {
                if(player[i].deck[j].wartosc==0)
                break;
                cout << player[i].deck[j].wartosc << " " << player[i].deck[j].kolor << " ";
                fprintf(*fptr," %d ", player[i].deck[j].wartosc);//zapisanie w pliku
            int results = fputs(player[i].deck[j].kolor,*fptr);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
            fprintf(*fptr,"\n");
}

void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr)
{
    cout << i << " pile cards: " << endl;
fprintf(*fptr, "%d %s ",  i, "pile cards:");
        for(int j=0; j<wszystkie_karty; j++)
            {
                if(kociolki[i].pile[j].wartosc==0)
                break;
                cout << kociolki[i].pile[j].wartosc << " " << kociolki[i].pile[j].kolor << " ";
                 fprintf(*fptr," %d ", kociolki[i].pile[j].wartosc);//zapisanie w pliku
            int results = fputs(kociolki[i].pile[j].kolor,*fptr);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
               fprintf(*fptr,"\n");
}

void wypisz_koncowy(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr)
{
     for(int i=1; i<=lg; i++)
    {
        wypisz_hand(gracze, i, wszystkie_karty, fptr);

        wypisz_deck(gracze, i, wszystkie_karty, fptr);
        
        cout << endl;
    }

    for(int i=1; i<=ki; i++)
    {
        wypisz_pile(kociolki, i,wszystkie_karty, fptr);
    }   
}

