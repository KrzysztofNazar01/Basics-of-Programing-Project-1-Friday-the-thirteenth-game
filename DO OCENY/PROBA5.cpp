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



int ustaw_wartosc(char znak1, char znak2);
void hand_input( int i, int j, int *reka, gracz *player,char  kolor[][10], char znak[MAX_INPUT_LENGTH],int (*spr)[8], int *number_of_cards);
void deck_input( int i, int j, int *deck, gracz *player,char  kolor[][10], char znak[MAX_INPUT_LENGTH],int (*spr)[8]);
void pile_input( int i, int j, int *pile, kociol *kociolki,char  kolor[][10], char znak[500],int (*spr)[8], int (*kolorkart1)[8][100], int *kolejna );
int get_value(char znak[MAX_INPUT_LENGTH], int poczatek);
void zsumuj_karty_z_kociolkow(int *wszystkie, int nowe_karty);
void zsumuj_karty_graczy(int *wszystkie, int hand, int deck);
void wyzeruj(char (*input)[MAX_INPUT_LENGTH]);

void intro_info(int *nastepny, int ig, int active, int explosion, FILE **fptr7b);
int first_card( gracz *player, int active);
int the_pile(int ik, int active, gracz *gracze, kociol *kociolki, char kolor[][10]);
void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr7b);
void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr7b);
void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr7b);
void wypisz_koncowy7B(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr7b);

int last_in_pile(kociol *kociolki, int ik, int active, gracz *gracze, char kolor[][10], int dozwolony_kociol );
int last_deck(gracz *gracze, int active);
int first_in_expl_pile(kociol *kociolki, int dozwolony_pile);

int main()
{
  
   
    
    char name[7][5000]={0};
    char name2[7][5000]={0};
    char tablica[100]={0};
    char tablica3[100]={0};
    char kociolwejscie[7][5000] = {0};
    
    const int wszystkie_karty=CARDS;
   char input[MAX_INPUT_LENGTH]={0};

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

int spr_kolory[8] ={0};


cin.getline(input, MAX_INPUT_LENGTH);
    int aktywny=get_value(input,16);

cin.getline(input, MAX_INPUT_LENGTH);
    int ilosc_graczy =get_value(input,17);

cin.getline(input, MAX_INPUT_LENGTH);
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
    cin.getline(input,MAX_INPUT_LENGTH); //wpisz informacje o hand gracza
    int reka=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    hand_input( i, j, &reka, gracze, kolorki, input, &spr_kolory, &gracze[j].ilosc_kart_na_rece);//analiza informacji o hand gracza
    wyzeruj( &input);

    
    cin.getline(input,MAX_INPUT_LENGTH);//wpisz informacje o deck gracza
    int deck=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    deck_input( i, j, &deck, gracze, kolorki, input, &spr_kolory);//analiza informacji o deck gracza
    wyzeruj( &input);

    zsumuj_karty_graczy(&policz_karty, reka,deck);//zsumuj karty do jednej puli
    
}
// for(int j=1; j<=ilosc_graczy; j++)
// for(int i=0;i<CARDS; i++)
// if(gracze[j].hand[i].wartosc !=0)
// cout <<gracze[j].hand[i].wartosc <<" " << gracze[j].hand[i].kolor << endl;

int ilosc_kociolkow=0;
int kolejna=0;
for(int j=1; j<MAX_NUMBER_OF_PILES; j++ )
{
        cin.getline(input,MAX_INPUT_LENGTH);//wpisz informacje o kociolkach

       
            if(input[0]>=48 && input[0]<=57)
            {
                ilosc_kociolkow++; 
                kociolki[j].pile = new karta[CARDS];  //utworz karty dla kociolka 
            }

            int pile=0; 

            for (int i=15; i<MAX_INPUT_LENGTH; i++)
            pile_input( i, j, &pile, kociolki, kolorki, input, &spr_kolory,&kociolki[j].kolor_kart, &kolejna); //analiza informacji o kociolkach

            wyzeruj( &input);

    zsumuj_karty_z_kociolkow(&policz_karty, pile); //zsumuj karty do jednej puli
}


fopen("NOWY_STAN_GRY7.txt","w");//otworz plik
    FILE *fptr7b; //wskaznik na plik

    fptr7b = fopen("NOWY_STAN_GRY7.txt","w"); 
    if(fptr7b == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }



int next=0;

intro_info(&next, ilosc_graczy, aktywny, granica_wybuchu, &fptr7b);




//szukanie ostatniego indeksu w kociolku funckja last in pile
int dozwolony_kociol=the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki);
int pierwsza_karta=first_card(gracze, aktywny);


//przekazanie karty z reki na kociol --> indkes karty w kotle jest o 1 wiekszy niz indeks ostatniej karty na tym kotle
kociolki[dozwolony_kociol].pile[last_in_pile(kociolki,ilosc_kociolkow, aktywny, gracze, kolorki, dozwolony_kociol) +1] =gracze[aktywny].hand[pierwsza_karta];



//usuniecie z reki graczy przekazywanej karty 
strcpy (gracze[aktywny].hand[first_card( gracze, aktywny)].kolor,kolorki[8]);
gracze[aktywny].hand[first_card( gracze, aktywny)].wartosc=0;


for(int j=1; j<=ilosc_kociolkow; j++)
{
    for(int i=0; i<CARDS; i++)
    {
        kociolki[j].suma_wartosci_kart=kociolki[j].suma_wartosci_kart+kociolki[j].pile[i].wartosc;
    }
    
    if(kociolki[j].suma_wartosci_kart > granica_wybuchu ) {
        //cout << "Pile number " << j <<" should explode earlier" << endl;
        //policz karty w wybuchajacym kociolku -- potrzebne do stworzenia petli
         for(int i=0; i<CARDS; i++)
                { 
                    if(kociolki[dozwolony_kociol].pile[i].wartosc !=0){
                        kociolki[dozwolony_kociol].ilosc_kart_w_kociolku++;
                    }
                }


        for(int a=1; a<=kociolki[dozwolony_kociol].ilosc_kart_w_kociolku; a++)
        {

        //znajdz indkes pierwszej karty w wybuchajacym kociolku
        int pierwsza_w_wybuchajacym_kotle=first_in_expl_pile(kociolki, dozwolony_kociol);

        //znajdz indkes ostatniej karty w deck aktywnego gracza
        int ostatnia_deck_akt_gracza=last_deck(gracze, aktywny);

     
        //w tym indkesie+1 umiesc karte z kociolka (utw. zmiennna kolejny indeks_kociol, kolejny_indkes_deck)
        gracze[aktywny].deck[ostatnia_deck_akt_gracza+1] = kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle];

    
        //usuniecie z kociolka zmienionej karty 
        strcpy (kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle].kolor,kolorki[8]);
        kociolki[dozwolony_kociol].pile[pierwsza_w_wybuchajacym_kotle].wartosc=0;

        //powtarzaj, dopoki liczba kart w tym kociolku=0;
        }
      
    }
        
}


//wypisanie stanu poczatkowe gry
wypisz_koncowy7B(ilosc_graczy, ilosc_kociolkow, gracze, wszystkie_karty, kociolki, &fptr7b);




//przenies funckje do main
//otworz plik
//sprawdz czy dziala




if(next==1){
    aktywny=1;
    next=0;
}

else
    aktywny++;

return 0;
}


void intro_info(int *nastepny, int ig, int active, int explosion, FILE **fptr7b)
{
    if(active==ig)
    {
        *nastepny=1;

        cout << "active player = 1" << endl;
        fprintf(*fptr7b, "active player = 1\n");
    }
    else
    {
        cout << "active player = " << active+1 << endl;
        fprintf(*fptr7b, "%s %d\n","active player =" ,active+1);
    }

    cout << "players number = "<< ig << endl;
    fprintf(*fptr7b, "%s %d\n","players number =" ,ig);
 
    cout << "explosion threshold = " << explosion << endl;
    fprintf(*fptr7b, "%s %d\n","explosion threshold =" ,explosion);

}

int first_card( gracz *player, int active)
{
    int first_card_index=0;
        for(int i=0; i<CARDS; i++)
        {
            if (player[active].hand[i].wartosc != 0 )
            {
                 first_card_index= i;
                 break;
            }
        }
        return first_card_index;

}


int the_pile(int ik, int active, gracz *gracze, kociol *kociolki, char kolor[][10])
{   
    
    //zielony
    if( strcmp(gracze[active].hand[first_card(gracze,active)].kolor, kolor[0]) == 0)
    return 1;

    int dozwolony_kociol=0;

    for(int j=1; j<=ik; j++)
    {  
        int zapisz=0;
        int wypisanie =0;

            for(int m=0; m<7; m++)
            {   
                for(int i=0; i<100; i++)
                if(kociolki[j].kolor_kart[m][i] != 0)
                {
                    if(m!=0)
                    {
                        kociolki[j].indeksy_kolorow_w_kotle[1]=m;

                        if(strcmp(gracze[active].hand[first_card( gracze, active)].kolor,kolor[m]) == 0)
                            {   
                                dozwolony_kociol=j;
                                
                            }    
                    }
                }  
            }
    }
    return dozwolony_kociol;
}


int last_in_pile(kociol *kociolki, int ik, int active, gracz *gracze, char kolor[][10], int dozwolony_kociol ){
int ostatni_na_stosie=0;
   for(int i=0; i<CARDS; i++)
{
    if (kociolki[dozwolony_kociol].pile[i].wartosc >
        kociolki[dozwolony_kociol].pile[ostatni_na_stosie].wartosc &&
        kociolki[dozwolony_kociol].pile[i].wartosc !=0)
    {
        ostatni_na_stosie = i;
    }
      
} 
return ostatni_na_stosie;
}


int last_deck(gracz *gracze, int active)
{
    int last_in_deck=0;

        for(int i=1; i<CARDS; i++)
        {   
            if (gracze[active].deck[i].wartosc > gracze[active].deck[last_in_deck].wartosc && gracze[active].deck[i].wartosc !=0)
            {
                last_in_deck = i+1;
            }
        }
return last_in_deck;
}
int first_in_expl_pile(kociol *kociolki, int dozwolony_pile)
{
    int pierwsza_w_wybuchajacym_kotle=0;
    for(int i=0; i<CARDS; i++)
                {   
                    if ( kociolki[dozwolony_pile].pile[i].wartosc !=0)
                    {
                        pierwsza_w_wybuchajacym_kotle = i;
                        break;
                    }
                }

    return pierwsza_w_wybuchajacym_kotle;
}









void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr7b)
{
    cout << i << " player hand cards: ";
    fprintf(*fptr7b, "%d %s",  i, "player hand cards:");

        for(int j=0; j<wszystkie_karty; j++)
        {
            //koniec wypisywania kart dla danego gracza
            if(player[i].hand[j].wartosc!=0)
            {
                //wypisza karty danego gracza
                cout << player[i].hand[j].wartosc << " " << player[i].hand[j].kolor << " ";
                
                fprintf(*fptr7b," %d ", player[i].hand[j].wartosc);//zapisanie w pliku
                int results = fputs(player[i].hand[j].kolor,*fptr7b);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
            
        }
        cout << endl;
        fprintf(*fptr7b,"\n");
}

void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr7b)
{
    cout << i << " player deck cards: ";
fprintf(*fptr7b, "%d %s",  i, "player deck cards:");
            for(int j=0; j<wszystkie_karty; j++)
            {
                if(player[i].deck[j].wartosc!=0)
                {
                    cout << player[i].deck[j].wartosc << " " << player[i].deck[j].kolor << " ";
                    fprintf(*fptr7b," %d ", player[i].deck[j].wartosc);//zapisanie w pliku

                    int results = fputs(player[i].deck[j].kolor,*fptr7b);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                    {
                        cout << "ERROR" ;
                    }
                }
                
            }
            cout << endl;
            fprintf(*fptr7b,"\n");
}

void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr7b)
{
    cout << i << " pile cards: ";
fprintf(*fptr7b, "%d %s",  i, "pile cards:");
        for(int j=0; j<wszystkie_karty; j++)
            {
                if(kociolki[i].pile[j].wartosc!=0)
                {
                   cout << kociolki[i].pile[j].wartosc << " " << kociolki[i].pile[j].kolor << " ";
                   fprintf(*fptr7b," %d ", kociolki[i].pile[j].wartosc);//zapisanie w pliku

                    int results = fputs(kociolki[i].pile[j].kolor,*fptr7b);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                    {
                        cout << "ERROR" ;
                    } 
                }
                
            }
           cout << endl;
               fprintf(*fptr7b,"\n");
}

void wypisz_koncowy7B(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr7b)
{
     for(int i=1; i<=lg; i++)
    {
        wypisz_hand(gracze, i, wszystkie_karty, fptr7b);

        wypisz_deck(gracze, i, wszystkie_karty, fptr7b);
        
    
    }

    for(int i=1; i<=ki; i++)
    {
        wypisz_pile(kociolki, i,wszystkie_karty, fptr7b);
    }   
}













int ustaw_wartosc(char znak1, char znak2){
int wynik;               

                         if (znak1==49)                      wynik =1;
                         if (znak1==50)                      wynik =2;
                         if (znak1==51)                      wynik =3;
                         if (znak1==52)                      wynik =4;
                         if (znak1==53)                      wynik =5;
                         if (znak1==54)                      wynik =6;
                         if (znak1==55)                      wynik =7;
                         if (znak1==56)                      wynik =8;
                         if (znak1==57)                      wynik =9;

                         if(znak2==49 && znak1==48)   return wynik =10;
                         if(znak2==49 && znak1==49)   return wynik =11; 
                         if(znak2==49 && znak1==50)   return wynik =12; 
                         if(znak2==49 && znak1==51)   return wynik =13; 
                         if(znak2==49 && znak1==52)   return wynik =14; 
                         if(znak2==49 && znak1==53)   return wynik =15; 
                         if(znak2==49 && znak1==54)   return wynik =16; 
                         if(znak2==49 && znak1==55)   return wynik =17; 
                         if(znak2==49 && znak1==56)   return wynik =18; 
                         if(znak2==49 && znak1==57)   return wynik =19;

                         if(znak2==50 && znak1==48)   return wynik =20;

        
return wynik;
}



void hand_input( int i, int j, int *reka, gracz *player,char  kolor[][10], char znak[500],int (*spr)[8], int *number_of_cards)
{

                    if(znak[i] == 110) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; (*number_of_cards)++; }
            else    if(znak[i] == 117) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[1] ); (*reka)++; (*spr)[1]++; (*number_of_cards)++; }
            else    if(znak[i] == 100) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[2] ); (*reka)++; (*spr)[2]++; (*number_of_cards)++; }
            else    if(znak[i] == 118) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[3] ); (*reka)++; (*spr)[3]++; (*number_of_cards)++; }
            else    if(znak[i] == 121) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[4] ); (*reka)++; (*spr)[4]++; (*number_of_cards)++; }
            else    if(znak[i] == 104) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].hand[*reka].kolor,kolor[5] ); (*reka)++;(*spr)[5]++; (*number_of_cards)++;  }
            else    if(znak[i] == 99) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].hand[*reka].kolor,kolor[6] ); (*reka)++; (*spr)[6]++; (*number_of_cards)++; }
}



void deck_input( int i, int j, int *deck, gracz *player,char  kolor[][10], char znak[500],int (*spr)[8])
{
    if(znak[i] == 110) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 117) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[1] ); (*deck)++; (*spr)[1]++; }
            else    if(znak[i] == 100) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[2] ); (*deck)++; (*spr)[2]++; }
            else    if(znak[i] == 118) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[3] ); (*deck)++; (*spr)[3]++; }
            else    if(znak[i] == 121) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[4] ); (*deck)++; (*spr)[4]++; }
            else    if(znak[i] == 104) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].deck[*deck].kolor,kolor[5] ); (*deck)++;(*spr)[5]++; }
            else    if(znak[i] == 99) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].deck[*deck].kolor,kolor[6] ); (*deck)++; (*spr)[6]++; }
}


void pile_input( int i, int j, int *pile, kociol *kociolki,char  kolor[][10], char znak[500],int (*spr)[8], int (*kolorkart1)[8][100], int *kolejna )
{
    if(znak[i] == 110) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( kociolki[j].pile[*pile].kolor,kolor[0] ); (*pile)++; }
            else    if(znak[i] == 117) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( kociolki[j].pile[*pile].kolor,kolor[1] ); (*pile)++; (*spr)[1]++; (*kolorkart1)[1][*kolejna]++;   (*kolejna)++;}
            else    if(znak[i] == 100) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( kociolki[j].pile[*pile].kolor,kolor[2] ); (*pile)++; (*spr)[2]++; (*kolorkart1)[2][*kolejna]++;   (*kolejna)++;}
            else    if(znak[i] == 118) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( kociolki[j].pile[*pile].kolor,kolor[3] ); (*pile)++;(*spr)[3]++; (*kolorkart1)[3][*kolejna]++;   (*kolejna)++; }
            else    if(znak[i] == 121) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( kociolki[j].pile[*pile].kolor,kolor[4] ); (*pile)++;(*spr)[4]++; (*kolorkart1)[4][*kolejna]++;   (*kolejna)++; }
            else    if(znak[i] == 104) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( kociolki[j].pile[*pile].kolor,kolor[5] ); (*pile)++; (*spr)[5]++; (*kolorkart1)[5][*kolejna]++;   (*kolejna)++;}
            else    if(znak[i] == 99) { kociolki[j].pile[*pile].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( kociolki[j].pile[*pile].kolor,kolor[6] ); (*pile)++;(*spr)[6]++; (*kolorkart1)[6][*kolejna]++;   (*kolejna)++; }
}


int get_value(char znak[MAX_INPUT_LENGTH], int poczatek)
{
    int result=0;
    int i=0;
    while(znak[poczatek+i]>=48 && znak[poczatek+i]<=57)  
    {
        result=result*10 + (znak[poczatek+i]-48);
        i++;
    }
    return result;
}

    
void zsumuj_karty_z_kociolkow(int *wszystkie, int nowe_karty){
    *wszystkie=*wszystkie+ nowe_karty;
}
void zsumuj_karty_graczy(int *wszystkie, int hand, int deck){
    *wszystkie=*wszystkie+ hand+deck ;
}
void wyzeruj(char (*input)[MAX_INPUT_LENGTH])
{
    
    for(int i=0; i < MAX_INPUT_LENGTH; i++)
    {
        (*input)[i]=0;
    }
    
}