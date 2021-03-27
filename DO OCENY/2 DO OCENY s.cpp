#include <iostream>
#include <string.h>
#include <stdio.h>              
using namespace std;

#define MAX_INPUT_LENGTH 1000
#define CARDS 500
#define COLORS 8
#define COLORS_LENGTH 10
#define MAX_NUMBER_OF_PILES 7

struct karta
{
    int wartosc=0;
    char kolor[COLORS_LENGTH]="0";
};


struct gracz{

    int ilosc_kart_na_rece=0;
    karta *hand;

    int ilosc_kart_z_eksplozji_kociolka=0;
    karta *deck;
    
    int ilosc_kart_kolorow[COLORS]={0};
    int indeksy_kolorow_na_ktore_odporny_jest_gracz[7]={8};
};


struct kociol{
    
    karta *pile;
    int ilosc_kart_w_kociolku=0;
    int kolor_kart[COLORS][100]= {0};
    int suma_wartosci_kart=0;
    int indeksy_kolorow_w_kotle[3]={10};
};

void ustaw_zielone(karta *player, int b, char (*kolor)[COLORS_LENGTH], int zw);
void ustaw_niezielone(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][COLORS_LENGTH]);
void pukladaj(int zi, int ki, int nzi, int lg, gracz *player , karta *talia);
void wypisz_hand2(gracz *player, int i, const int wszystkie_karty , FILE **fptr2);
void wypisz_deck2(gracz *player, int i, const int wszystkie_karty, FILE **fptr2);
void wypisz_pile2(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr2);
void wypisz_koncowy2(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr2);


int main(){ 
    //gracz gracze[7];

    char kolorki[COLORS][COLORS_LENGTH] = 
    {  
            {"green"} ,  /* 0 */
            {"blue"} ,   /* 1 */
            {"red"}  ,   /* 2 */
            {"violet"},  /* 3 */
            {"yellow"},  /* 4 */
            {"white"},   /* 5 */
            {"black"},   /* 6 */
            {" "}        /* 7 */
    };

    int kolejka2=0;
    int liczba_graczy2=0;
    int kociolki_ilosc2=0;
    int zielone_ilosc2=0;
    int zielone_wartosc2=0;
    int niezielone_ilosc2=0;


//wpisywanie danych do utworzenia gry
    cin >> liczba_graczy2;
    cin >> kociolki_ilosc2;
    cin >> zielone_ilosc2;
    cin >> zielone_wartosc2;
    cin >> niezielone_ilosc2;

const int wszystkie_karty=(niezielone_ilosc2*kociolki_ilosc2)+zielone_ilosc2; //ilosc kart w calej talii
 
kociol *kociolki = new kociol[kociolki_ilosc2+1]; //utworzenie kociolkow, kociolki numerowane od "1"
for(int i=1; i<= kociolki_ilosc2; i++)
kociolki[i].pile = new karta[CARDS];  //utworz karty dla kociolka 

gracz *gracze = new gracz[liczba_graczy2+1];  //utworzenie graczy, gracze numerowani od "1"
for(int i=1; i<= liczba_graczy2; i++)
{
    gracze[i].hand = new karta[CARDS];
    gracze[i].deck = new karta[CARDS];
}
karta *talia = new karta[wszystkie_karty]; //utworzenie talii, karty numerowane od "0" do "wszystkie karty-1"
int *niezielone_wartosc2 = new int[niezielone_ilosc2]; //tablica dla niezielonych wartosci

for(int i=0; i<niezielone_ilosc2; ++i) //wpisanie niezielonych wartosci
        cin >> niezielone_wartosc2[i];


ustaw_zielone(talia, zielone_ilosc2, &kolorki[0], zielone_wartosc2);

ustaw_niezielone(talia, zielone_ilosc2, niezielone_ilosc2, kociolki_ilosc2, niezielone_wartosc2, kolorki);

fopen("PO_ROZDANIU.txt","w");//otworz plik
    FILE *fptr2; //wskaznik na plik

    fptr2 = fopen("PO_ROZDANIU.txt","w"); 
    if(fptr2 == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

kolejka2++; // kolejna runda

fprintf(fptr2, "active player = %d\n", kolejka2); 
fprintf(fptr2, "players number = %d\n", liczba_graczy2); 
  

pukladaj( zielone_ilosc2,  kociolki_ilosc2,  niezielone_ilosc2,liczba_graczy2,gracze, talia );

wypisz_koncowy2(liczba_graczy2, kociolki_ilosc2, gracze, wszystkie_karty, kociolki, &fptr2);
 
//usuwanie tablic dynamicznych - unikniecie memory leak
    delete [] talia;
    delete [] niezielone_wartosc2;
    delete [] gracze;
    delete [] kociolki;

return 0;

}

void ustaw_zielone(karta *player, int b, char (*kolor)[COLORS_LENGTH], int zw)
{
   for(int i=0; i<b; ++i)
    {
        strcpy(player[i].kolor,(*kolor)); //przypisanie zielonego koloru
        player[i].wartosc= zw; //przypisanie wartosci dla zieloych kart
    }
}

void ustaw_niezielone(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][COLORS_LENGTH])
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

void wypisz_hand2(gracz *player, int i, const int wszystkie_karty , FILE **fptr2)
{
    
    fprintf(*fptr2, "%d %s ",  i, "player hand cards:");

        for(int j=0; j<wszystkie_karty; j++)
        {
            //koniec wypisywania kart dla danego gracza
            if(player[i].hand[j].wartosc==0)
            break;

            //wypisz karty danego gracza
            fprintf(*fptr2," %d ", player[i].hand[j].wartosc);//zapisanie w pliku
            int results = fputs(player[i].hand[j].kolor,*fptr2);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
        }
        
        fprintf(*fptr2,"\n");
}

void wypisz_deck2(gracz *player, int i, const int wszystkie_karty, FILE **fptr2)
{

fprintf(*fptr2, "%d %s ",  i, "player deck cards:");
            for(int j=0; j<wszystkie_karty; j++)
            {
                if(player[i].deck[j].wartosc==0)
                break;
    
                fprintf(*fptr2," %d ", player[i].deck[j].wartosc);//zapisanie w pliku
            int results = fputs(player[i].deck[j].kolor,*fptr2);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
            fprintf(*fptr2,"\n");
}

void wypisz_pile2(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr2)
{
    
fprintf(*fptr2, "%d %s ",  i, "pile cards:");
        for(int j=0; j<wszystkie_karty; j++)
            {
                if(kociolki[i].pile[j].wartosc==0)
                break;
                
                 fprintf(*fptr2," %d ", kociolki[i].pile[j].wartosc);//zapisanie w pliku
            int results = fputs(kociolki[i].pile[j].kolor,*fptr2);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
               fprintf(*fptr2,"\n");
}

void wypisz_koncowy2(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr2)
{
     for(int i=1; i<=lg; i++)
    {
        wypisz_hand2(gracze, i, wszystkie_karty, fptr2);

        wypisz_deck2(gracze, i, wszystkie_karty, fptr2);
        
        
    }

    for(int i=1; i<=ki; i++)
    {
        wypisz_pile2(kociolki, i,wszystkie_karty, fptr2);
    }   
}

