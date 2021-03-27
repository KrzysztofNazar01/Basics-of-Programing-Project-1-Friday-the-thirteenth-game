#include <iostream>
#include <string.h>
#include <stdio.h>              
using namespace std;

#define MAX_INPUT_LENGTH 1000
#define CARDS 500
#define COLORS 8
#define COLORS_LENGTH 10
#define MAX_NUMBER_OF_PILES 7
#define MAX_NUMBER_OF_PLAYERS 8


struct karta
{
    int wartosc=0;
    char kolor[COLORS_LENGTH]="0";
};

struct gracz
{    
    karta *hand;
    karta *deck;

    int ilosc_kart_na_rece=0;
    int ilosc_kart_kolorow[COLORS]={0};
    int indeksy_kolorow_na_ktore_odporny_jest_gracz[COLORS]={COLORS};
};

struct kociol
{
    karta *pile;
    int ilosc_kart_w_kociolku=0;
    int kolor_kart[COLORS][CARDS]= {0};
    int suma_wartosci_kart=0;
    int indeks_koloru_w_kotle=COLORS;
    char kolor[COLORS_LENGTH]="0";
};

void utworz_zielone_karty(karta *player, int b, char (*kolor)[COLORS_LENGTH], int zw);
void utworz_niezielone_karty(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][COLORS_LENGTH]);
void rozdaj_karty(int wszystkie_karty, int lg, gracz *player , karta *talia);
void wypisz_hand2(gracz *player, int i, const int wszystkie_karty , FILE **fptr2);
void wypisz_deck2(gracz *player, int i, const int wszystkie_karty, FILE **fptr2);
void wypisz_pile2(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr2);
void wypisz_stan_gry2(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr2);
int ustaw_wartosc(char znak1, char znak2);
int get_value(char znak[MAX_INPUT_LENGTH], int poczatek);
void zsumuj_karty_z_kociolkow(int *wszystkie, int nowe_karty);
void zsumuj_karty_graczy(int *wszystkie, int hand, int deck);
void wyzeruj(char (*input)[MAX_INPUT_LENGTH]);
void hand_input3( int i, int j, int *reka, gracz *player,char  kolor[][COLORS_LENGTH], char znak[CARDS],int (*spr)[COLORS], int *number_of_cards);
void deck_input3( int i, int j, int *deck, gracz *player,char  kolor[][COLORS_LENGTH], char znak[MAX_INPUT_LENGTH],int (*spr)[COLORS]);
void pile_input3( int i, int j, int *pile, kociol *kociolki,char  kolor[][COLORS_LENGTH], char znak[CARDS],int (*spr)[COLORS], int (*kolorkart1)[COLORS][CARDS], int *kolejna );
void wypisz_koniec3(int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS],int ilosc_kociolkow, kociol kociolki[MAX_NUMBER_OF_PILES] );
void policz_zielone_karty(int ilosc_graczy, int ilosc_kociolkow, int *zielona_karta_info_1, int *zielona_karta_info_2, int *pz, gracz player[MAX_NUMBER_OF_PLAYERS], kociol pot[MAX_NUMBER_OF_PILES], int (*gc)[MAX_NUMBER_OF_PLAYERS][CARDS] );
void wypisz_stan_gry4(int x, int y, int pz, int gc[][CARDS], int ilosc_graczy);
int wypisz_rowne4(int spr[COLORS]);
int wypisz_nierowne4(int spr[COLORS], char kolor[][COLORS_LENGTH]);
int pierwsza_niezerowa4(int spr[COLORS] );
void policz_wartosci_kart(int (*policz)[COLORS][CARDS], int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH], int ilosc_kociolkow, kociol kociolki[MAX_NUMBER_OF_PILES]);
void sortuj_wzrostowo( int (*policz)[COLORS][CARDS]);
int  not_identical_values(int policz[][CARDS], char kolor[][COLORS_LENGTH]);
void  identical_values( int policz[][CARDS]);
int max(int ilosc_graczy, gracz *player);
int min(int ilosc_graczy, gracz *player);
void kolory_w_kociolkach(int ilosc_kociolkow, kociol *kociolki, int *koniec);
void wybuch(int ilosc_kociolkow, kociol *kociolki, int treshold, int *koniec);
void ilosc_kart_na_rekach_graczy(int ilosc_graczy, gracz *gracze, int *koniec);
void intro_game_info(int *nastepny, int ilosc_graczy, int active, int explosion, FILE **fptr7a);
int first_card( gracz *player, int active);
int the_pile(int ilosc_kociolkow, int active, gracz *gracze, kociol *kociolki, char kolor[][COLORS_LENGTH]);
void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr7a);
void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr7a);
void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr7a);
void wypisz_stan_gry7(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr7);
void wypisz_hand8(gracz *player, int i, const int wszystkie_karty);
void wypisz_deck8(gracz *player, int i, const int wszystkie_karty);
void wypisz_pile8(kociol *kociolki, int i, const int wszystkie_karty);
void wypisz_stan_gry8(int lg, int ki, gracz *gracze, kociol *kociolki);
int last_in_pile(kociol *kociolki, int ilosc_kociolkow, int active, gracz *gracze, char kolor[][COLORS_LENGTH], int dozwolony_kociol );
int last_deck(gracz *gracze, int active);
int first_in_expl_pile(kociol *kociolki, int dozwolony_pile);
void ilosc_kart_kolorow_u_gracza(int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH]);
void wypisz_odpornych(gracz player[7], char kolor[][COLORS_LENGTH], int ma_najwiecej_kart_koloru_m, int m );
void wypisz_ile_kart_maja_gracze(int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH] );
void kto_ma_najwiecej(int ilosc_graczy, int *ma_najwiecej_kart_koloru_m, int *czy_inny_gracz, int m , gracz *player);
void sumy_wartosci_na_kociolkach( kociol *kociolki, char kolorki[][COLORS_LENGTH], int ilosc_kociolkow);
int najmniejszy_kociol(kociol *kociolki, int ilosc_kociolkow);
int najmnijesza_wartosc_reka(gracz *gracze, int aktywny);
void indeksy_kart_o_danej_wartosci( gracz *gracze, int aktywny, int *ilosc, int (*indeksy)[CARDS], int najmniejsza_wartosc_na_rece);
void dopasuj_karty_do_odpowiednich_kociolkow(gracz *gracze, int aktywny, kociol *kociolki,  int indeksy[CARDS], char kolorki[][COLORS_LENGTH], int indkes_kociolka_z_najmnijesza_suma, int ilosc_kociolkow, int ilosc, int *indeks_najmniejszej_karty, int *indeks_najmnijeszy_kociol);
int najwieksza_wartosc_reka(gracz *gracze, int aktywny);

int main(){
char kolorki[COLORS][COLORS_LENGTH] = {{"green"}, {"blue"}, {"red"}, {"violet"}, {"yellow"}, {"white"}, {"black"}, {" "}};

int zadanie=1;

#ifndef TEST
//POCZATEK ZADANIE 1
cout << endl << "Trucizna-1, utworzenie talii"<<endl;

int piles = 0;
int zielone_ilosc = 0;
int zielone_wartosc = 0;
int niezielone_ilosc = 0;

//Zmienne w grze
    cin >> piles;
    cin >> zielone_ilosc;
    cin >> zielone_wartosc;
    cin >> niezielone_ilosc;

int *niezielone_wartosc = new int[niezielone_ilosc]; //tablica wartosci niezielonych kart

for(int i = 0; i<niezielone_ilosc; i++) 
    niezielone_wartosc[i] = 0; // wyzerowanie tablicy

for(int i=0; i<niezielone_ilosc; ++i) //przypisanie wartosci
    cin >> niezielone_wartosc[i];
    
const int all_cards=niezielone_ilosc+zielone_ilosc; //stala ilosc   

karta *talia = new karta[all_cards]; //utworzenie talii

for(int i=0; i<all_cards; i++)
    talia[i].wartosc = 0; // wyzerowanie tablicy


fopen("NIEPOTASOWANA_TALIA.txt","w"); //otworz plik
FILE *fptr1; 
fptr1 = fopen("NIEPOTASOWANA_TALIA.txt","w"); 
if(fptr1 == NULL) //w razie nieotworzenia pliku
{
    cout << "EROOR";  
    return 0;             
}

    for(int i=0; i<zielone_ilosc; ++i)
    {   talia[i].wartosc= zielone_wartosc; //przypisanie wartosci dla zieloych kart

        if(i==0)
        fprintf(fptr1,"%d ",talia[i].wartosc); //zapisanie w pliku

        else
        fprintf(fptr1," %d ",talia[i].wartosc); //zapisanie w pliku

        strcpy(talia[i].kolor,kolorki[0] ); //przypisanie zielonego koloru

            int results = fputs(talia[i].kolor, fptr1); //zapisanie w pliku
            if (results == EOF) //w razie bledu
            {
                cout << "ERROR" ;
                return 0;
            }
    }

    for(int j=1; j<=piles; j++)
    {
        for(int k=zielone_ilosc; k<all_cards; k++)
        {   
            talia[k].wartosc= niezielone_wartosc[k-zielone_ilosc]; //przypisanie wartosci dla niezieloych kart
            fprintf(fptr1," %d ",talia[k].wartosc); //zapisanie w pliku

            strcpy(talia[k].kolor,kolorki[j]); //przypisanie niezielonych kolorow

            int results = fputs(talia[k].kolor, fptr1); //zapisanie w pliku
            if (results == EOF) //w razie bledu
            {
                cout << "ERROR";
                return 0;
            }
        }
    }

fclose(fptr1); //zamknij plik

//uniknij memory leak
delete [] niezielone_wartosc;
delete [] talia;

//KONIEC ZADANIE 1
#endif
zadanie++;
#ifndef TEST
//POCZATEK ZADANIE 2

if(zadanie==2)
{
    cout << endl <<"Trucizna-2, rozdanie kart" << endl;

    int kolejka2 = 0;
    int liczba_graczy2 = 0;
    int kociolki_ilosc2 = 0;
    int zielone_ilosc2 = 0;
    int zielone_wartosc2 = 0;
    int niezielone_ilosc2 = 0;

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

utworz_zielone_karty(talia, zielone_ilosc2, &kolorki[0], zielone_wartosc2);
utworz_niezielone_karty(talia, zielone_ilosc2, niezielone_ilosc2, kociolki_ilosc2, niezielone_wartosc2, kolorki);

fopen("PO_ROZDANIU.txt","w"); //otworz plik
    FILE *fptr2; 

    fptr2 = fopen("PO_ROZDANIU.txt","w"); 
    if(fptr2 == NULL) //w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

kolejka2++; // kolejna runda

fprintf(fptr2, "active player = %d\n", kolejka2); 
fprintf(fptr2, "players number = %d\n", liczba_graczy2); 

rozdaj_karty( wszystkie_karty,liczba_graczy2,gracze, talia );

wypisz_stan_gry2(liczba_graczy2, kociolki_ilosc2, gracze, wszystkie_karty, kociolki, &fptr2);

fclose(fptr2);

//unikniecie memory leak
    delete [] talia;
    delete [] niezielone_wartosc2;
    delete [] gracze;
    delete [] kociolki;

//KONIEC ZADANIE 2
}
#endif

zadanie++;

if(zadanie==3){   
//POCZATEK ZADANIE 3
cout << endl << "Trucizna-3a, wczytanie stanu gry" << endl;

int spr_kolory[COLORS] ={0};
char input[MAX_INPUT_LENGTH]={0};

fopen("STAN_GRY3.txt","r"); //wczytaj informacje o grze
    FILE *fptr; 

    fptr = fopen("STAN_GRY3.txt","r"); 
    if(fptr == NULL) //w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

fgets (input, MAX_INPUT_LENGTH, fptr);
    int aktywny=get_value(input,16);

fgets (input, MAX_INPUT_LENGTH, fptr);
    int ilosc_graczy=get_value(input,17);

fgets (input, MAX_INPUT_LENGTH, fptr);
    int granica_wybuchu=get_value(input,22);
  

gracz *gracze = new gracz[ilosc_graczy+1];  //utworzenie graczy, gracze numerowani od "1"
for(int i=1; i<= ilosc_graczy; i++)
{
    gracze[i].hand = new karta[CARDS];
    gracze[i].deck = new karta[CARDS];
}

kociol *kociolki = new kociol[MAX_NUMBER_OF_PILES];  //utworzenie kociolkow, gracze numerowani od "1"

int policz_karty=0;

for(int j=1; j<=ilosc_graczy; j++ )
{
    fgets(input,MAX_INPUT_LENGTH,fptr); //wpisz informacje o hand gracza
    int reka=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    hand_input3( i, j, &reka, gracze, kolorki, input, &spr_kolory,&gracze[j].ilosc_kart_na_rece); //analiza informacji o hand gracza
    wyzeruj( &input);

    
    fgets(input,MAX_INPUT_LENGTH,fptr); //wpisz informacje o deck gracza
    int deck=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    deck_input3( i, j, &deck, gracze, kolorki, input, &spr_kolory); //analiza informacji o deck gracza
    wyzeruj( &input);

    zsumuj_karty_graczy(&policz_karty, reka,deck); //zsumuj karty do jednej puli
}

int ilosc_kociolkow=0;
int kolejna=0;

    for(int j=1; j<MAX_NUMBER_OF_PILES; j++ )
    {
        fgets(input,MAX_INPUT_LENGTH,fptr); //wpisz informacje o kociolkach

            if(input[0]>=48 && input[0]<=57)
            {
                ilosc_kociolkow++; 
                kociolki[j].pile = new karta[CARDS];  //utworz karty dla kociolka 
            }

        int pile=0; 

        for (int i=15; i<MAX_INPUT_LENGTH; i++)
        pile_input3( i, j, &pile, kociolki, kolorki, input, &spr_kolory,&kociolki[j].kolor_kart, &kolejna); //analiza informacji o kociolkach

        wyzeruj( &input);

        zsumuj_karty_z_kociolkow(&policz_karty, pile); //zsumuj karty do jednej puli
    }
    
    fclose(fptr); //koniec wczytywania danych

const int wszystkie_karty=policz_karty; //stala ilosc

wypisz_koniec3(ilosc_graczy, gracze, ilosc_kociolkow, kociolki);
//KONIEC ZADANIE 3


//POCZATEK ZADANIE 4
cout << endl <<"Trucizna-4, sprawdzenie zielonych kart" << endl;

int green_cards[MAX_NUMBER_OF_PLAYERS][CARDS]={0};

// znajdz przykladową zielona karte, a potem porownaj jej wartosc z innymi zielonymi kartami
int zielona_karta_info_1=0;
int zielona_karta_info_2=0;

int ilosc_zielonych_kart=0;
policz_zielone_karty(ilosc_graczy, ilosc_kociolkow, &zielona_karta_info_1,  &zielona_karta_info_2, &ilosc_zielonych_kart, gracze, kociolki, &green_cards);

if(ilosc_zielonych_kart == 0) cout << "Green cards does not exist" << endl;
else wypisz_stan_gry4(zielona_karta_info_1, zielona_karta_info_2, ilosc_zielonych_kart, green_cards, ilosc_graczy);

if( (wypisz_nierowne4(spr_kolory, kolorki)) == 1) // porownaj pierwsza niezerowa wartosc z innymi wartosciami w spr_kolory
cout << endl;

else//lub wypisz jesli rowne
wypisz_rowne4(spr_kolory);

//KONIEC ZADANIE 4


//POCZATEK ZADANIE 5
cout << endl <<"Trucizna-5, sprawdzenie wartosci kart" << endl;

int wartosci_kart_roznych_kolorow[COLORS][CARDS]={0};

policz_wartosci_kart(&wartosci_kart_roznych_kolorow, ilosc_graczy, gracze, kolorki, ilosc_kociolkow, kociolki);

sortuj_wzrostowo(&wartosci_kart_roznych_kolorow); //potrzebne do porownania

if((not_identical_values(wartosci_kart_roznych_kolorow, kolorki)) ==1) cout << endl;
else identical_values(wartosci_kart_roznych_kolorow);

//KONIEC ZADANIE 5


//POCZATEK ZADANIE 6
cout << endl << "Trucizna-6, sprawdzenie poprawnosci stanu gry" << endl;

int czy_konczyc=0;

ilosc_kart_na_rekach_graczy(ilosc_graczy, gracze, &czy_konczyc);

kolory_w_kociolkach(ilosc_kociolkow, kociolki, &czy_konczyc);

wybuch(ilosc_kociolkow, kociolki, granica_wybuchu, &czy_konczyc);

if(czy_konczyc==0) cout << "Current state of the game is ok" << endl; //nie ma problemow w stanie gry

//KONIEC ZADANIE 6


//POCZATEK ZADANIE 7A
cout << endl <<"Trucizna-7a - wykonanie prostego posuniecia" << endl;

//ustawienie aktywnego gracza, na koncu przy "return 0" druga czesc procesu ustawiania gracza(przygotowane na kolejna runde)
int nastepny=0;

//szukanie ostatniego indeksu w kociolku 
int dozwolony_kociol=the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki);
int pierwsza_karta=first_card(gracze, aktywny);
int ostatni_w_kociolku=last_in_pile(kociolki,ilosc_kociolkow, aktywny, gracze, kolorki, dozwolony_kociol);

//przekazanie karty z reki na kociol --> indkes karty w kotle jest o 1 wiekszy niz indeks ostatniej karty na tym kotle
kociolki[dozwolony_kociol].pile[ostatni_w_kociolku+1] = gracze[aktywny].hand[pierwsza_karta];

//usuniecie z reki graczy przekazywanej karty 
strcpy (gracze[aktywny].hand[pierwsza_karta].kolor,kolorki[7]);
gracze[aktywny].hand[pierwsza_karta].wartosc=0;

    //zapisz stan gry
    fopen("NOWY_STAN_GRY7A_STOS.txt","w");
    FILE *fptr7a; 

    fptr7a = fopen("NOWY_STAN_GRY7A_STOS.txt","w"); 
    if(fptr7a == NULL) //w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

    intro_game_info(&nastepny, ilosc_graczy, aktywny, granica_wybuchu, &fptr7a);
    wypisz_stan_gry7(ilosc_graczy, ilosc_kociolkow, gracze, wszystkie_karty, kociolki, &fptr7a);

    fclose(fptr7a);

//KONIEC ZADANIE 7A


//POCZATEK ZADANIE 7B

cout << endl <<"Trucizna-7b - obsługa eksplozji kociolka" << endl;

for(int j = 1;  j <= ilosc_kociolkow;  j++)
{
    int suma_wartosci_kart=0;

    for(int i = 0; i < CARDS;  i++)
    suma_wartosci_kart+=kociolki[j].pile[i].wartosc;
   
    if(suma_wartosci_kart > granica_wybuchu ) //wybuch
    {
        //policz karty w wybuchajacym kociolku -- potrzebne do stworzenia petli
        for(int i = 0; i < CARDS;  i++)
        if(kociolki[dozwolony_kociol].pile[i].wartosc != 0)
        kociolki[dozwolony_kociol].ilosc_kart_w_kociolku++;

        for(int usuwana_karta=1; usuwana_karta<=kociolki[dozwolony_kociol].ilosc_kart_w_kociolku; usuwana_karta++)
        {
            //znajdz indkes pierwszej karty w wybuchajacym kociolku
            int pierwsza_w_wybuchajacym_kotle=first_in_expl_pile(kociolki, dozwolony_kociol);

            //znajdz indkes ostatniej karty w hand deck aktywnego gracza
            int ostatnia_deck_akt_gracza=last_deck(gracze, aktywny);

            //w tym indkesie+1 umiesc karte z kociolka (utw. zmiennna kolejny indeks_kociol, kolejny_indkes_deck)
            gracze[aktywny].deck[ostatnia_deck_akt_gracza+1] = kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle];

            //usuniecie z kociolka zmienionej karty 
            strcpy (kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle].kolor,kolorki[7]);
            kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle].wartosc=0;

            //powtarzaj, dopoki liczba kart w tym kociolku=0;
        }
    }
}

//zapisz stan gry
fopen("NOWY_STAN_GRY7B_STOS.txt","w");
    FILE *fptr7b; 

    fptr7b = fopen("NOWY_STAN_GRY7B_STOS.txt","w"); 
    if(fptr7b == NULL) //w razie nieotworzenia pliku
    {
        cout << "ERROR";  
        return 0;             
    }

intro_game_info(&nastepny, ilosc_graczy, aktywny, granica_wybuchu, &fptr7b);
wypisz_stan_gry7(ilosc_graczy, ilosc_kociolkow, gracze, wszystkie_karty, kociolki, &fptr7b);

fclose(fptr7b);

//KONIEC ZADANIE 7B

//POCZATEK ZADANIE 8
cout << endl <<"Trucizna-8 - obsługa końca rundy" << endl;

int zakoncz_rozgrywke = 0;
//policz karty na rece u kazdego gracza
for(int j=1; j<=ilosc_graczy; j++)
{
    for(int i = 0; i < CARDS;  i++)
    {
        if(gracze[j].hand[i].wartosc != 0)
        zakoncz_rozgrywke++;
    }
}

//gracze nie maja kart na rece
if(zakoncz_rozgrywke == 0)
{
    ilosc_kart_kolorow_u_gracza(ilosc_graczy, gracze, kolorki); 
            
    //znajdz odpornych na kolory
    for(int m = 1; m < 7; m++)
    {
        int ma_najwiecej_kart_koloru_m=0;
        int czy_inny_gracz=0;

        kto_ma_najwiecej(ilosc_graczy, &ma_najwiecej_kart_koloru_m, &czy_inny_gracz, m, gracze);

        if(czy_inny_gracz==0)
        wypisz_odpornych(gracze, kolorki, ma_najwiecej_kart_koloru_m, m);
    }
    
    wypisz_ile_kart_maja_gracze(ilosc_graczy, gracze, kolorki);
}

else wypisz_stan_gry8(ilosc_graczy, ilosc_kociolkow, gracze, kociolki);


//POCZATEK ZADANIA DODATKOWEGO
int nowa_rozgrywka=0;
if(nowa_rozgrywka == 0)
{
cout << endl << endl << "WYMAGANIA DODATKOWE - wartosci czytane z pliku WymaganiaDadatkoweCZYTANIE.txt i zapisywane do WymaganiaDadatkoweZAPISANE.txt" << endl;

fopen("WymaganiaDadatkoweCZYTANIE.txt","r"); //czytaj informacje potrzebne do gry
    FILE *fptrD1; 

    fptrD1 = fopen("WymaganiaDadatkoweCZYTANIE.txt","r"); 
    if(fptrD1 == NULL) //w razie nieotworzenia pliku
    {
        cout << "ERROR";  
        return 0;             
    }

fgets (input, MAX_INPUT_LENGTH, fptrD1);
    int aktywny=get_value(input,16);

fgets (input, MAX_INPUT_LENGTH, fptrD1);
    int ilosc_graczy=get_value(input,17);

fgets (input, MAX_INPUT_LENGTH, fptrD1);
    int granica_wybuchu=get_value(input,22);
  

gracz *gracze = new gracz[ilosc_graczy+1];  //utworzenie graczy, numerowani od "1"
for(int i=1; i<= ilosc_graczy; i++)
{
    gracze[i].hand = new karta[CARDS];
    gracze[i].deck = new karta[CARDS];
}

kociol *kociolki = new kociol[MAX_NUMBER_OF_PILES];  //utworzenie kociolkow, numerowani od "1"

int policz_karty=0;


//Informacje o graczach
    for(int j=1; j<=ilosc_graczy; j++ )
    {
        fgets(input,MAX_INPUT_LENGTH,fptrD1); //wpisz informacje o hand gracza
        int hand_cards=0;
        for (int i=20; i < MAX_INPUT_LENGTH; i++)
        hand_input3( i, j, &hand_cards, gracze, kolorki, input, &spr_kolory,&gracze[j].ilosc_kart_na_rece); //analiza informacji o hand gracza
        wyzeruj( &input); //gotowe na kolejny input

        
        fgets(input,MAX_INPUT_LENGTH,fptrD1); //wpisz informacje o deck gracza
        int deck_cards=0;
        for (int i=20; i < MAX_INPUT_LENGTH; i++)
        deck_input3( i, j, &deck_cards, gracze, kolorki, input, &spr_kolory); //analiza informacji o deck gracza
        wyzeruj( &input); //gotowe na kolejny input

        zsumuj_karty_graczy(&policz_karty, hand_cards,deck_cards);
    }

//Informacje o kociolkach
int ilosc_kociolkow=0;
int kolejna=0;

    for(int j=1; j<MAX_NUMBER_OF_PILES; j++ )
    {
        fgets(input,MAX_INPUT_LENGTH,fptrD1); //wpisz informacje o kociolkach

            if(input[0]>=48 && input[0]<=57)
            {
                ilosc_kociolkow++; 
                kociolki[j].pile = new karta[CARDS];  //utworz karty dla kociolka 
            }

        int pile_cards=0; 

        for (int i=15; i<MAX_INPUT_LENGTH; i++)
        pile_input3( i, j, &pile_cards, kociolki, kolorki, input, &spr_kolory,&kociolki[j].kolor_kart, &kolejna); //analiza informacji o kociolkach

        wyzeruj( &input); //gotowe na kolejny input

        zsumuj_karty_z_kociolkow(&policz_karty, pile_cards); 
    }
    
    fclose(fptrD1);

const int wszystkie_karty=policz_karty; //stala ilosc

//dozwolone = mozemy polozyc tam karte
int dozwolony_kociol=0;
int dozwolona_karta=0;

int jak_chcesz_grac=0;
cout << "Jak chcesz grac? Wpisz: " << endl << "1 --> NORMALNIE" << endl << "2 --> NAJMNIEJSZA" << endl << "3 --> NAJWIEKSZA" << endl;
cin >> jak_chcesz_grac;
cout << endl << "Wybrales: ";
if (jak_chcesz_grac == 1)
{
     cout << "NORMLANIE" << endl;

//szukanie ostatniego indeksu w kociolku funckja last in pile
    dozwolony_kociol=the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki);
    dozwolona_karta=first_card(gracze, aktywny);
}
else if(jak_chcesz_grac == 2 || jak_chcesz_grac == 3 )
{
    //policz sume wartosci kart na kazdym kotle
    sumy_wartosci_na_kociolkach(kociolki, kolorki, ilosc_kociolkow);

    //najmniejszy kociol
    int indkes_kociolka_z_najmnijesza_suma = najmniejszy_kociol(kociolki, ilosc_kociolkow);

    if(jak_chcesz_grac == 2)
    {
        cout << "NAJMNIEJSZA" << endl;
        //znajdz najmeijsza wartosc na rece aktywnego gracza
        int najmniejsza_wartosc_na_rece = najmnijesza_wartosc_reka(gracze, aktywny);

        int ilosc = 0;
        int indeksy[CARDS] = {0};
        //znajdz indkesy kart z najmniejsza wartoscia i ich ilosc
        indeksy_kart_o_danej_wartosci(gracze, aktywny, &ilosc, &indeksy, najmniejsza_wartosc_na_rece);

        int indeks_najmniejszej_karty=0;
        int indeks_najmnijeszy_kociol=1;

        dopasuj_karty_do_odpowiednich_kociolkow(gracze, aktywny, kociolki,indeksy, kolorki,  indkes_kociolka_z_najmnijesza_suma,  ilosc_kociolkow, ilosc, &indeks_najmniejszej_karty, &indeks_najmnijeszy_kociol );

        cout << "indeks_najmnijeszy_kociol " << indeks_najmnijeszy_kociol << " " << gracze[aktywny].hand[indeks_najmniejszej_karty].wartosc << " " << gracze[aktywny].hand[indeks_najmniejszej_karty].kolor << endl;

        dozwolony_kociol=indeks_najmnijeszy_kociol;
        dozwolona_karta=indeks_najmniejszej_karty;
    }

    else
    {
        cout << "NAJWIEKSZA" << endl;     
        //znajdz najwieksza wartosc na rece aktywnego gracza
        int najwieksza_wartosc_na_rece = najwieksza_wartosc_reka(gracze, aktywny);
        int ilosc = 0;
        int indeksy[CARDS] = {0};
        //znajdz indkesy kart z najmniejsza wartoscia i ich ilosc
        indeksy_kart_o_danej_wartosci(gracze, aktywny, &ilosc, &indeksy, najwieksza_wartosc_na_rece);

        int indeks_najwiekszej_karty=0;
        int indeks_najmnijeszy_kociol=1;

        dopasuj_karty_do_odpowiednich_kociolkow(gracze, aktywny, kociolki,indeksy, kolorki,  indkes_kociolka_z_najmnijesza_suma,  ilosc_kociolkow, ilosc, &indeks_najwiekszej_karty, &indeks_najmnijeszy_kociol );

        cout << "najwiekszej " << indeks_najmnijeszy_kociol << " " << gracze[aktywny].hand[indeks_najwiekszej_karty].wartosc << " " << gracze[aktywny].hand[indeks_najwiekszej_karty].kolor << endl;

        dozwolony_kociol=indeks_najmnijeszy_kociol;
        dozwolona_karta=indeks_najwiekszej_karty;
    }
}

int ostatni_w_kociolku=last_in_pile(kociolki,ilosc_kociolkow, aktywny, gracze, kolorki, dozwolony_kociol);

//przekazanie karty z reki na kociol --> indkes karty w kotle jest o 1 wiekszy niz indeks ostatniej karty na tym kotle
kociolki[dozwolony_kociol].pile[ostatni_w_kociolku+1] = gracze[aktywny].hand[dozwolona_karta];


//usuniecie z reki graczy przekazywanej karty 
strcpy (gracze[aktywny].hand[dozwolona_karta].kolor,kolorki[7]);
gracze[aktywny].hand[dozwolona_karta].wartosc=0;

//wpisz to co teraz jest w plik 7a (NA STOS)
//wypisanie stanu poczatkowe gry
fopen("WymaganiaDadatkoweZAPISANE.txt","w"); //otworz plik
    FILE *fptrD2; //wskaznik na plik

    fptrD2 = fopen("WymaganiaDadatkoweZAPISANE.txt","w"); 
    if(fptrD2 == NULL) //w razie nieotworzenia pliku
    {
        cout << "ERROR";  
        return 0;             
    }

intro_game_info(&nastepny, ilosc_graczy, aktywny, granica_wybuchu, &fptrD2);
wypisz_stan_gry7(ilosc_graczy, ilosc_kociolkow, gracze, wszystkie_karty, kociolki, &fptrD2);

fclose(fptrD2);
//KONIEC ZADANIA DODATKOWEGO
}


//przygotowanie do kolejnej rundy
if(nastepny == 1)
{
    aktywny=1;
    nastepny=0;
}

else
    aktywny++;

//KONIEC ZADANIE 8

//unikniecie memory leak
delete [] gracze;
delete [] kociolki;
}

  

return 0;
}

void utworz_zielone_karty(karta *player, int ilosc_zielonych, char (*kolor)[COLORS_LENGTH], int zw)
{
   for(int i=0; i<ilosc_zielonych; ++i)
    {
        strcpy(player[i].kolor,(*kolor)); //przypisanie zielonego koloru
        player[i].wartosc= zw; //przypisanie wartosci dla zieloych kart
    }
}

void utworz_niezielone_karty(karta *player, int zi, int nzi, int ki, int *nzw, char kolorki[][COLORS_LENGTH])
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



void rozdaj_karty(int wszystkie_karty,  int lg, gracz *player , karta *talia)
{
    int nr_karty=0; 
    int numer_gracza=1;

        for(int i=0; i<wszystkie_karty; i++)
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
            if(player[i].hand[j].wartosc == 0)
            break;

            //wypisz karty danego gracza
            fprintf(*fptr2," %d ", player[i].hand[j].wartosc); //zapisanie wartosci
            int results = fputs(player[i].hand[j].kolor,*fptr2); //zapisanie koloru
            if (results == EOF) cout << "ERROR"; //w razie bledu    
        }
        
    fprintf(*fptr2,"\n");
}

void wypisz_deck2(gracz *player, int i, const int wszystkie_karty, FILE **fptr2)
{
    fprintf(*fptr2, "%d %s ",  i, "player deck cards:");

        for(int j = 0; j < wszystkie_karty; j++)
        {
            if(player[i].deck[j].wartosc == 0)
            break;

            fprintf(*fptr2," %d ", player[i].deck[j].wartosc); //zapisanie wartosci
            int results = fputs(player[i].deck[j].kolor,*fptr2); //zapisanie koloru
            if (results == EOF) cout << "ERROR"; //w razie bledu    
        }

    fprintf(*fptr2,"\n");
}

void wypisz_pile2(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr2)
{
    fprintf(*fptr2, "%d %s ",  i, "pile cards:");

        for(int j=0; j<wszystkie_karty; j++)
        {
            if(kociolki[i].pile[j].wartosc == 0)
            break;
            
            fprintf(*fptr2," %d ", kociolki[i].pile[j].wartosc); //zapisanie wartosci
            int results = fputs(kociolki[i].pile[j].kolor,*fptr2); //zapisanie koloru
            if (results == EOF) cout << "ERROR"; //w razie bledu    
        }

    fprintf(*fptr2,"\n");
}

void wypisz_stan_gry2(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr2)
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


int ustaw_wartosc(char znak1, char znak2)
{
    int wynik;               

        if (znak1==49)  wynik = 1;
        if (znak1==50)  wynik = 2;
        if (znak1==51)  wynik = 3;
        if (znak1==52)  wynik = 4;
        if (znak1==53)  wynik = 5;
        if (znak1==54)  wynik = 6;
        if (znak1==55)  wynik = 7;
        if (znak1==56)  wynik = 8;
        if (znak1==57)  wynik = 9;

        if(znak2==49 && znak1==48)   return wynik = 10;
        if(znak2==49 && znak1==49)   return wynik = 11; 
        if(znak2==49 && znak1==50)   return wynik = 12; 
        if(znak2==49 && znak1==51)   return wynik = 13; 
        if(znak2==49 && znak1==52)   return wynik = 14; 
        if(znak2==49 && znak1==53)   return wynik = 15; 
        if(znak2==49 && znak1==54)   return wynik = 16; 
        if(znak2==49 && znak1==55)   return wynik = 17; 
        if(znak2==49 && znak1==56)   return wynik = 18; 
        if(znak2==49 && znak1==57)   return wynik = 19;

        if(znak2==50 && znak1==48)   return wynik = 20;

    return wynik;
}



void hand_input3( int i, int j, int *reka, gracz *player,char  kolor[][COLORS_LENGTH], char znak[CARDS],int (*spr)[COLORS], int *number_of_cards)
{

        if(znak[i] == 110) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; (*number_of_cards)++; }
else    if(znak[i] == 117) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[1] ); (*reka)++; (*spr)[1]++; (*number_of_cards)++; }
else    if(znak[i] == 100) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[2] ); (*reka)++; (*spr)[2]++; (*number_of_cards)++; }
else    if(znak[i] == 118) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[3] ); (*reka)++; (*spr)[3]++; (*number_of_cards)++; }
else    if(znak[i] == 121) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[4] ); (*reka)++; (*spr)[4]++; (*number_of_cards)++; }
else    if(znak[i] == 104) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].hand[*reka].kolor,kolor[5] ); (*reka)++; (*spr)[5]++; (*number_of_cards)++; }
else    if(znak[i] == 99)  { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].hand[*reka].kolor,kolor[6] ); (*reka)++; (*spr)[6]++; (*number_of_cards)++; }
}



void deck_input3( int i, int j, int *deck, gracz *player,char  kolor[][COLORS_LENGTH], char znak[CARDS],int (*spr)[COLORS])
{
        if(znak[i] == 110) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
else    if(znak[i] == 117) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[1] ); (*deck)++; (*spr)[1]++; }
else    if(znak[i] == 100) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[2] ); (*deck)++; (*spr)[2]++; }
else    if(znak[i] == 118) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[3] ); (*deck)++; (*spr)[3]++; }
else    if(znak[i] == 121) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[4] ); (*deck)++; (*spr)[4]++; }
else    if(znak[i] == 104) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].deck[*deck].kolor,kolor[5] ); (*deck)++; (*spr)[5]++; }
else    if(znak[i] == 99)  { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].deck[*deck].kolor,kolor[6] ); (*deck)++; (*spr)[6]++; }
}


void pile_input3( int i, int j, int *pile, kociol *kociolki,char  kolor[][COLORS_LENGTH], char znak[CARDS],int (*spr)[COLORS], int (*kolorkart1)[COLORS][CARDS], int *kolejna )
{
    
            if(znak[i] == 110) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy(kociolki[j].pile[*pile].kolor,kolor[0] ); (*pile)++; }
    else    if(znak[i] == 117) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy(kociolki[j].pile[*pile].kolor,kolor[1] ); (*pile)++; (*spr)[1]++; (*kolorkart1)[1][*kolejna]++;   (*kolejna)++;}
    else    if(znak[i] == 100) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy(kociolki[j].pile[*pile].kolor,kolor[2] ); (*pile)++; (*spr)[2]++; (*kolorkart1)[2][*kolejna]++;   (*kolejna)++;}
    else    if(znak[i] == 118) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy(kociolki[j].pile[*pile].kolor,kolor[3] ); (*pile)++;(*spr)[3]++; (*kolorkart1)[3][*kolejna]++;   (*kolejna)++; }
    else    if(znak[i] == 121) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy(kociolki[j].pile[*pile].kolor,kolor[4] ); (*pile)++;(*spr)[4]++; (*kolorkart1)[4][*kolejna]++;   (*kolejna)++; }
    else    if(znak[i] == 104) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy(kociolki[j].pile[*pile].kolor,kolor[5] ); (*pile)++; (*spr)[5]++; (*kolorkart1)[5][*kolejna]++;   (*kolejna)++;}
    else    if(znak[i] == 99) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy(kociolki[j].pile[*pile].kolor,kolor[6] ); (*pile)++;(*spr)[6]++; (*kolorkart1)[6][*kolejna]++;   (*kolejna)++; }
}

int get_value(char znak[MAX_INPUT_LENGTH], int poczatek)
{
    int result=0, i=0;
    while(znak[poczatek+i]>=48 && znak[poczatek+i]<=57)  
    {
        result=result*10 + (znak[poczatek+i]-48);
        i++;
    }
    return result;
}

void zsumuj_karty_z_kociolkow(int *wszystkie, int nowe_karty)
{
    *wszystkie=*wszystkie+ nowe_karty;
}

void zsumuj_karty_graczy(int *wszystkie, int hand, int deck)
{
    *wszystkie=*wszystkie+ hand+deck ;
}

void wyzeruj(char (*input)[MAX_INPUT_LENGTH])
{
    for(int i=0; i < MAX_INPUT_LENGTH; i++)
    (*input)[i]=0;
}


void wypisz_koniec3(int ilosc_graczy, gracz gracze[MAX_NUMBER_OF_PLAYERS], int ilosc_kociolkow, kociol kociolki[MAX_NUMBER_OF_PILES] )
{
    for(int j = 1; j <= ilosc_graczy;  j++)
    {
        int ilosc_kart_na_rece=0;

        cout << j << " player has " ;

            for(int i = 0; i < CARDS;  i++)
            if(gracze[j].hand[i].wartosc != 0)
            ilosc_kart_na_rece++;

        cout << ilosc_kart_na_rece << " cards on hand" << endl;


        int ilosc_kart_z_eksplozji_kociolka=0;

        cout << j << " player has " ;

            for(int i = 0; i < CARDS;  i++)
            if(gracze[j].deck[i].wartosc != 0)
            ilosc_kart_z_eksplozji_kociolka++;

        cout << ilosc_kart_z_eksplozji_kociolka << " cards in front of him" << endl;
    }  

    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {
        int ilosc_kart_w_kociolku=0; 

            for(int i = 0; i < CARDS;  i++)
            if(kociolki[j].pile[i].wartosc != 0)
            ilosc_kart_w_kociolku++;

        cout << "there are " << ilosc_kart_w_kociolku << " cards on " << j << " pile" << endl;
    }
}



void policz_zielone_karty(int ilosc_graczy, int ilosc_kociolkow, int *zielona_karta_info_1, int *zielona_karta_info_2, int *pz, gracz player[MAX_NUMBER_OF_PLAYERS], kociol pot[MAX_NUMBER_OF_PILES], int (*gc)[MAX_NUMBER_OF_PLAYERS][CARDS] )
{
    for(int j = 1; j <= ilosc_graczy;  j++)
    {
        for(int i = 0; i < CARDS;  i++)
        {
            if ((strncmp(player[j].hand[i].kolor,"green",COLORS_LENGTH) == 0))
            {    
                (*gc)[j][i] = player[j].hand[i].wartosc;
                *zielona_karta_info_1=i;
                *zielona_karta_info_2=j;
                (*pz)++;
            }

            if ((strncmp(player[j].deck[i].kolor,"green",COLORS_LENGTH) == 0 ))
            {    
                (*gc)[j][i] = player[j].deck[i].wartosc;
                *zielona_karta_info_1=i;
                *zielona_karta_info_2=j;
                (*pz)++;
            }
        }
    }

    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {
        for(int i = 0; i < CARDS;  i++)
        {
            if ((strncmp (pot[j].pile[i].kolor,"green",COLORS_LENGTH) == 0))
            {    
                (*gc)[j][i] = pot[j].pile[i].wartosc;
                *zielona_karta_info_1=i;
                *zielona_karta_info_2=j;
                (*pz)++;   
            }
        }
    }   
}

void wypisz_stan_gry4(int x, int y, int pz, int gc[][CARDS], int ilosc_graczy)
{
    for(int j = 1; j <= ilosc_graczy;  j++)
    {   
        for(int i = 0; i < CARDS;  i++)
        {
            if (gc[j][i] != gc[y][x] &&  gc[j][i] != 0)
            {    
                cout << "Different green cards values occurred" << endl;
                break;
            }
        }
    
    }

    cout << "Found " << pz << " green cards, all with " << gc[y][x] << " value" << endl;
}


int pierwsza_niezerowa4(int spr[COLORS])//znajdz pierwszą niezerowa wartosc dla spr_kolory
{
    int do_testu=0;

    for(int i=1; i<=6; i++)
    {
        if(spr[i] != 0) 
        {
            do_testu = spr[i];
            break;
        }
    }

    return do_testu;
}

int wypisz_rowne4(int spr[COLORS])
{
    cout << "The number cards of all colors is equal: ";

    for(int i=1; i<=6; i++)
    {
        if(spr[i] != 0) 
        {
            cout << spr[i];
            break;
        }
    }
}

int wypisz_nierowne4(int spr[COLORS], char kolor[][COLORS_LENGTH])
{ 
    int porownuj_z = pierwsza_niezerowa4(spr);
        
    for(int i=1; i<=6; i++)
    { 
        if(porownuj_z != spr[i] && spr[i] != 0) 
        { 
            cout << "At least two colors with a different number of cards were found:" << endl;

            for(int j=1; j<=6; j++)
            if(spr[j] !=0)
            cout << kolor[j] << " cards are " << spr[j] << endl;

        return 1; 
        }
    }  
}
  

void policz_wartosci_kart(int (*policz)[COLORS][CARDS], int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH], int ilosc_kociolkow, kociol kociolki[MAX_NUMBER_OF_PILES] )
{
    int p=0;

    for(int j = 1; j <= ilosc_graczy;  j++)
    {
        for(int i = 0; i < CARDS;  i++)
        {  
            for(int m=1; m<=7; m++)
            {
                if(player[j].hand[i].wartosc != 0 && (strcmp(player[j].hand[i].kolor, kolor[m]))==0 )
                {
                    (*policz)[m][p]=player[j].hand[i].wartosc;
                    p++;
                }
                
                if(player[j].deck[i].wartosc != 0 && (strcmp(player[j].deck[i].kolor, kolor[m]))==0 )
                {                
                    (*policz)[m][p]=player[j].deck[i].wartosc;           
                    p++;
                }
            } 
        } 
    }

    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {
        for(int i = 0; i < CARDS;  i++)
        {  
            for(int m=1; m<=7; m++)
            {
                if(kociolki[j].pile[i].wartosc != 0 && (strcmp(kociolki[j].pile[i].kolor, kolor[m]))==0 )
                {
                    (*policz)[m][p]=kociolki[j].pile[i].wartosc;
                    p++;
                }
            }
        }
    }
}

void sortuj_wzrostowo( int (*policz)[COLORS][CARDS])
{
    for(int m=1; m<=7; m++)
    {
        for (int i = 0; i < CARDS; i++)                     //Loop for sortuj_wzrostowo ordering
        {
            for (int j = 0; j < CARDS; j++)             //Loop for comparing other values
            {   
                if((*policz)[m][j] != 0)
                if ((*policz)[m][j] > (*policz)[m][i])                //Comparing other array elements
                {
                    int tmp = (*policz)[m][i];         //Using temporary variable for storing last value
                    (*policz)[m][i] = (*policz)[m][j];            //replacing value
                    (*policz)[m][j] = tmp;             //storing last value
                }  
            }
        } 
    }
}


int not_identical_values(int policz[][CARDS], char kolor[][COLORS_LENGTH])
{
    for(int m = 1; m < 7; m++)
    {   
        for(int t=1; t<7; t++)
        {         
            for(int i=0;i<CARDS; i++)
            {
                if( policz[m][i] !=policz[t][i] && policz[m][i] != 0 && policz[t][i] != 0)
                {
                    cout << "The values of cards of all colors are not identical:" << endl;

                    for(int m = 1; m < 7; m++)
                    {
                        cout << kolor[m] << " cards values: ";

                            for(int i = 0; i < CARDS;  i++)
                            {
                                if(policz[m][i]!= 0)
                                cout << policz[m][i] << " " ; 
                            }

                        cout << endl;
                    }
                return 1;
                }
            }
        }
    }
}

void identical_values( int policz[][CARDS])
{
    cout << "The values of cards of all colors are identical:" << endl;

    for(int m = 0;  m < 7;  m++)
    {
        int koniec=0;
        for(int i = 0; i < CARDS;  i++)
        {
            if(policz[m][i] != 0)
            {
                cout << policz[m][i] << " ";
                koniec=1; 
            }
        }

        if(koniec==1)
        return; 
    }    
}


int max(int ilosc_graczy, gracz *player)
{
    int max=1;

        for(int j = 1; j <= ilosc_graczy;  j++)
        if (player[j].ilosc_kart_na_rece < player[max].ilosc_kart_na_rece )
        max = j;

    return max;
}

int min(int ilosc_graczy, gracz *player)
{
    int min=1;

        for(int j = 1; j <= ilosc_graczy;  j++)
        if (player[j].ilosc_kart_na_rece > player[min].ilosc_kart_na_rece )
        min = j;


    return min;
}

void kolory_w_kociolkach(int ilosc_kociolkow, kociol *kociolki, int *koniec)
{
    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {  
    int zapisz=0;
    int wypisanie =0;
        for(int m = 1; m < 7; m++)
        {   
            for(int i = 0; i < CARDS;  i++)
            if(kociolki[j].kolor_kart[m][i] != 0){
            
                wypisanie++;
                if(wypisanie==1)
                zapisz=m;

                if(m!=zapisz){
                    cout << "Two different colors were found on the " << j <<" pile" << endl;

                    *koniec=1;
                break;
                }
                
            }
            
        }
    
    } 
}

void wybuch(int ilosc_kociolkow, kociol *kociolki, int treshold, int *koniec)
{
    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {
        for(int i = 0; i < CARDS;  i++)
        {
            kociolki[j].suma_wartosci_kart=kociolki[j].suma_wartosci_kart+kociolki[j].pile[i].wartosc;
        }
        
        if(kociolki[j].suma_wartosci_kart > treshold ) {
            cout << "Pile number " << j <<" should explode earlier" << endl;
            *koniec=1;
        }
            
    }
}

void ilosc_kart_na_rekach_graczy(int ilosc_graczy, gracz *gracze, int *koniec)
{
    if(gracze[min(ilosc_graczy, gracze)].ilosc_kart_na_rece-gracze[max(ilosc_graczy, gracze)].ilosc_kart_na_rece >= 2)
    {
        cout << "The number of players cards on hand is wrong" << endl;
        *koniec=1;
    }
}


void intro_game_info(int *nastepny, int ilosc_graczy, int active, int explosion, FILE **fptr7a)
{
    if(active==ilosc_graczy)
    {
        *nastepny=1;
        fprintf(*fptr7a, "active player = 1\n");
    }
    else
    fprintf(*fptr7a, "%s %d\n","active player =" ,active+1);

    fprintf(*fptr7a, "%s %d\n","players number =" ,ilosc_graczy);
    fprintf(*fptr7a, "%s %d\n","explosion threshold =" ,explosion);
}

int first_card( gracz *player, int active)
{
    int first_card_index=0;

        for(int i = 0; i < CARDS; i++)
        {
            if (player[active].hand[i].wartosc != 0 )
            {
                first_card_index = i;
                break;
            }
        }

    return first_card_index;
}



int the_pile(int ilosc_kociolkow, int active, gracz *gracze, kociol *kociolki, char kolor[][COLORS_LENGTH])
{   
    if( strcmp(gracze[active].hand[first_card(gracze,active)].kolor, kolor[0]) == 0) //zielony
    return 1;

    int dozwolony_kociol = 0;

    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {  
        int zapisz = 0;
        int wypisanie = 0;

        for(int m = 0;  m < 7;  m++)
        {   
            for(int i = 0; i < CARDS;  i++)
            if(kociolki[j].kolor_kart[m][i] != 0)
            {
                if(m!=0)
                {
                    kociolki[j].indeks_koloru_w_kotle=m;

                    if(strcmp(gracze[active].hand[first_card( gracze, active)].kolor,kolor[m]) == 0)
                    dozwolony_kociol=j;   
                }
            }  
        }
    }

    return dozwolony_kociol;
}

void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr7a)
{
    fprintf(*fptr7a, "%d %s",  i, "player hand cards:");

    for(int j=0; j<wszystkie_karty; j++)
    {
        //koniec wypisywania kart dla danego gracza
        if(player[i].hand[j].wartosc!=0)
        {
            //wypisza karty danego gracza
            fprintf(*fptr7a," %d ", player[i].hand[j].wartosc); //zapisanie wartosci
            int results = fputs(player[i].hand[j].kolor,*fptr7a); //zapisanie koloru 
            if (results == EOF) cout << "ERROR" ; //w razie bledu
        }
    }

    fprintf(*fptr7a,"\n");
}

void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr7a)
{
    fprintf(*fptr7a, "%d %s",  i, "player deck cards:");

    for(int j=0; j<wszystkie_karty; j++)
    {
        if(player[i].deck[j].wartosc!=0)
        {
            fprintf(*fptr7a," %d ", player[i].deck[j].wartosc); //zapisanie wartosci

            int results = fputs(player[i].deck[j].kolor,*fptr7a); //zapisanie koloru 
            if (results == EOF) cout << "ERROR" ; //w razie bledu
        } 
    }

    fprintf(*fptr7a,"\n");
}

void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr7a)
{
    fprintf(*fptr7a, "%d %s",  i, "pile cards:");

    for(int j=0; j<wszystkie_karty; j++)
        {
            if(kociolki[i].pile[j].wartosc!=0)
            {
                fprintf(*fptr7a," %d ", kociolki[i].pile[j].wartosc); //zapisanie wartosci

                int results = fputs(kociolki[i].pile[j].kolor,*fptr7a); //zapisanie koloru 
                if (results == EOF) cout << "ERROR" ; //w razie bledu
            } 
        }

    fprintf(*fptr7a,"\n");
}

void wypisz_stan_gry7(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr7)
{
    for(int i=1; i<=lg; i++)
    {
        wypisz_hand(gracze, i, wszystkie_karty, fptr7);

        wypisz_deck(gracze, i, wszystkie_karty, fptr7);
    }

    for(int i=1; i<=ki; i++)
        wypisz_pile(kociolki, i,wszystkie_karty, fptr7);
}

int last_deck(gracz *gracze, int active)
{
    int last_in_deck=0;

        for(int i = 0; i < CARDS;  i++)
        if (gracze[active].deck[i].wartosc !=0)
        last_in_deck = i+1;

    return last_in_deck;
}

int first_in_expl_pile(kociol *kociolki, int dozwolony_pile)
{
    int pierwsza_w_wybuchajacym_kotle=0;

        for(int i = 0; i < CARDS;  i++)
        if (kociolki[dozwolony_pile].pile[i].wartosc !=0)
        {
            pierwsza_w_wybuchajacym_kotle = i;
            break;
        }

    return pierwsza_w_wybuchajacym_kotle;
}

void wypisz_hand8(gracz *player, int i)
{
    cout << i << " player hand cards: ";

        for(int j=0; j<CARDS; j++)
        if(player[i].hand[j].wartosc!=0)
        cout << player[i].hand[j].wartosc << " " << player[i].hand[j].kolor << " ";

    cout << endl;
}

void wypisz_deck8(gracz *player, int i)
{
    cout << i << " player deck cards: ";

        for(int j=0; j<CARDS; j++)
        if(player[i].deck[j].wartosc!=0)
        cout << player[i].deck[j].wartosc << " " << player[i].deck[j].kolor << " ";
        
    cout << endl;
}

void wypisz_pile8(kociol *kociolki, int i)
{
    cout << i << " pile cards: ";

        for(int j=0; j<CARDS; j++)
        if(kociolki[i].pile[j].wartosc!=0)
        cout << kociolki[i].pile[j].wartosc << " " << kociolki[i].pile[j].kolor << " ";

    cout << endl;
}

void wypisz_stan_gry8(int lg, int ki, gracz *gracze, kociol *kociolki)
{
     for(int i=1; i<=lg; i++)
    {
        wypisz_hand8(gracze, i);
        wypisz_deck8(gracze, i);
    }

    for(int i=1; i<=ki; i++)
        wypisz_pile8(kociolki, i);  
}

int last_in_pile(kociol *kociolki, int ilosc_kociolkow, int active, gracz *gracze, char kolor[][COLORS_LENGTH], int dozwolony_kociol )
{
    int ostatni_na_stosie=0;

        for(int i = 0; i < CARDS;  i++)
        {
            if (kociolki[dozwolony_kociol].pile[i].wartosc !=0)
            ostatni_na_stosie = i;
        } 

    return ostatni_na_stosie;
}

void ilosc_kart_kolorow_u_gracza(int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH])
{
    for(int j=1; j<=ilosc_graczy ; j++)
    {   
        for(int m=0;m<7; m++)
        {
            int ilosc=0;

            for(int i = 0; i < CARDS;  i++)
            {
                if(strcmp(player[j].deck[i].kolor,kolor[m]) == 0)
                ilosc++;  
            }
            player[j].ilosc_kart_kolorow[m]=ilosc;
        }
    }     
}
     
void wypisz_odpornych(gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH], int ma_najwiecej_kart_koloru_m, int m )
{
    cout << "Na kolor " << kolor[m] << " odporny jest gracz " << ma_najwiecej_kart_koloru_m <<endl;

    //wyzerowanie wartosci dla kart danego koloru u gracza odpornego na dany kolor
    for(int i=0;i<CARDS; i++)
    {
        if(strcmp(player[ma_najwiecej_kart_koloru_m].deck[i].kolor,kolor[m]) == 0)
        player[ma_najwiecej_kart_koloru_m].deck[i].wartosc=0;
    } 
}

void wypisz_ile_kart_maja_gracze(int ilosc_graczy, gracz player[MAX_NUMBER_OF_PLAYERS], char kolor[][COLORS_LENGTH] )
{
    for(int j=1;j<=ilosc_graczy;j++)
    {
        int ilosc_kart_na_koniec=0;

        for(int i=0; i<400; i++)
        {
            if(player[j].deck[i].wartosc != 0)
            {
                if(strcmp(player[j].deck[i].kolor,kolor[0])==0)
                ilosc_kart_na_koniec += 2;

                else
                ilosc_kart_na_koniec++;
            }
        }

        cout << "Wynik gracza " << j << " = " << ilosc_kart_na_koniec << endl;
    }
}

void kto_ma_najwiecej(int ilosc_graczy, int *ma_najwiecej_kart_koloru_m, int *czy_inny_gracz, int m , gracz *player)
{
    for(int j = 1; j <= ilosc_graczy;  j++)
    { 
        if(player[j].ilosc_kart_kolorow[m]==player[*ma_najwiecej_kart_koloru_m].ilosc_kart_kolorow[m])
        (*czy_inny_gracz)++;

        else if(player[j].ilosc_kart_kolorow[m]>player[*ma_najwiecej_kart_koloru_m].ilosc_kart_kolorow[m])
        {
            *ma_najwiecej_kart_koloru_m=j;
            *czy_inny_gracz=0;
        }
    }
        
}

void sumy_wartosci_na_kociolkach( kociol *kociolki, char kolorki[][COLORS_LENGTH], int ilosc_kociolkow)
{
    for(int j = 1;  j <= ilosc_kociolkow;  j++)
    {
        int suma=0;
        for(int i = 0; i < CARDS;  i++)
        {
            kociolki[j].suma_wartosci_kart += kociolki[j].pile[i].wartosc;

            if(kociolki[j].pile[i].wartosc != 0 && strcmp(kociolki[j].pile[i].kolor, kolorki[0])!=0 )
            strcpy( kociolki[j].kolor, kociolki[j].pile[i].kolor );
        }
    }
}

int najmniejszy_kociol(kociol *kociolki, int ilosc_kociolkow)
{
    int indkes_kociolka_z_najmnijesza_suma = 1;

        for(int k = 1; k<= ilosc_kociolkow; k++)
        if(kociolki[k].suma_wartosci_kart <=  kociolki[indkes_kociolka_z_najmnijesza_suma].suma_wartosci_kart )
        indkes_kociolka_z_najmnijesza_suma =k;

    return indkes_kociolka_z_najmnijesza_suma;
}

int najmnijesza_wartosc_reka(gracz *gracze, int aktywny)
{
    int najmniejsza_wartosc_na_rece=CARDS;

        for(int i = 0; i < CARDS;  i++)
        if(gracze[aktywny].hand[i].wartosc <= najmniejsza_wartosc_na_rece  && gracze[aktywny].hand[i].wartosc != 0)
        najmniejsza_wartosc_na_rece=gracze[aktywny].hand[i].wartosc;
        
    return najmniejsza_wartosc_na_rece;     
}

void indeksy_kart_o_danej_wartosci( gracz *gracze, int aktywny, int *ilosc, int (*indeksy)[CARDS], int najmniejsza_wartosc_na_rece)
{
    for(int i = 0; i < CARDS;  i++)
    if(gracze[aktywny].hand[i].wartosc == najmniejsza_wartosc_na_rece )
    {
        cout << "Karty: " << gracze[aktywny].hand[i].wartosc << " " << gracze[aktywny].hand[i].kolor << endl;
        (*indeksy)[*ilosc]=i;
        (*ilosc)++;
    }
}

void dopasuj_karty_do_odpowiednich_kociolkow(gracz *gracze, int aktywny, kociol *kociolki,  int indeksy[CARDS], char kolorki[][COLORS_LENGTH], int indkes_kociolka_z_najmnijesza_suma, int ilosc_kociolkow, int ilosc, int *indeks_najmniejszej_karty, int *indeks_najmnijeszy_kociol)
{
int zapisz_indeks[MAX_NUMBER_OF_PILES]={MAX_NUMBER_OF_PILES};
int suma_po_polozeniu[MAX_NUMBER_OF_PILES]={999};
int czy_zielony=0;
int zajety=0;
    
    for(int i = 0; i < ilosc; i++)
    {
        if( strcmp(gracze[aktywny].hand[indeksy[i]].kolor, kolorki[0]) ==0 ) //zielona
        {   
            czy_zielony++;
            zapisz_indeks[indkes_kociolka_z_najmnijesza_suma] = indeksy[i];
            break;
        }

        else//niezielona
        {
            for(int k = 1; k <= ilosc_kociolkow; k++)
            {
            if(strcmp(gracze[aktywny].hand[indeksy[i]].kolor, kociolki[k].kolor) == 0) //istnieje kociolek w kolorze karty 
                {
                    suma_po_polozeniu[k] = kociolki[k].suma_wartosci_kart + gracze[aktywny].hand[indeksy[i]].wartosc;
            
                    zapisz_indeks[k] = indeksy[i];
                    zajety = indeksy[i];
                }
            }    
        
            if(zajety != indeksy[i]) //nie istnieje kociolek w kolorze karty 
            {
                for(int j = 1;  j <= ilosc_kociolkow;  j++)
                {
                    if(strcmp(gracze[aktywny].hand[indeksy[i]].kolor, kociolki[j].kolor) == 0 || kociolki[j].suma_wartosci_kart == 0)
                    {
                        suma_po_polozeniu[j] = kociolki[j].suma_wartosci_kart + gracze[aktywny].hand[indeksy[i]].wartosc;
                                
                        zapisz_indeks[j] = indeksy[i];
                    }
                }
            }
        }
    }

    if(czy_zielony != 0) //zielona karta od razu do najmnijeszego kociolka
    {
        *indeks_najmnijeszy_kociol = indkes_kociolka_z_najmnijesza_suma;
        *indeks_najmniejszej_karty = zapisz_indeks[indkes_kociolka_z_najmnijesza_suma];
    }
    
    else
    {
        for(int k=1; k<=ilosc_kociolkow;k++)
        if(suma_po_polozeniu[k]!=0)
        *indeks_najmnijeszy_kociol = k;

        for(int k = 1; k <= ilosc_kociolkow; k++)
        {
            if(suma_po_polozeniu[k] <= suma_po_polozeniu[*indeks_najmnijeszy_kociol] && suma_po_polozeniu[k] != 0)
            {
                *indeks_najmnijeszy_kociol = k;
                *indeks_najmniejszej_karty = zapisz_indeks[k];
            }
        }
    }

}

int najwieksza_wartosc_reka(gracz *gracze, int aktywny)
{
    int najwieksza_wartosc_na_rece=1;

    for(int i = 0; i < CARDS;  i++)
    if(gracze[aktywny].hand[i].wartosc >= najwieksza_wartosc_na_rece )
    najwieksza_wartosc_na_rece = gracze[aktywny].hand[i].wartosc;

    return najwieksza_wartosc_na_rece;
}



