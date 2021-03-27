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

int get_value(char znak[MAX_INPUT_LENGTH], int poczatek);
int ustaw_wartosc(char znak1, char znak2);
void hand_input3( int i, int j, int *reka, gracz *player,char  kolor[][10], char znak[MAX_INPUT_LENGTH]);
void deck_input3( int i, int j, int *deck, gracz *player,char  kolor[][10], char znak[MAX_INPUT_LENGTH]);
void wypisz_koniec3(int ig, gracz player[7]);
void zsumuj_karty_graczy(int *wszystkie, int hand, int deck);
void wyzeruj(char (*input)[MAX_INPUT_LENGTH]);



int main()
{
   

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


fopen("STAN_GRY3A.txt","r");//otworz plik
    FILE *fptr; //wskaznik na plik

    fptr = fopen("STAN_GRY3A.txt","r"); 
    if(fptr == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

fgets (input, MAX_INPUT_LENGTH, fptr);
    int aktywny=get_value(input,16);

fgets (input, MAX_INPUT_LENGTH, fptr);
    int ilosc_graczy=get_value(input,17);


gracz *gracze = new gracz[ilosc_graczy+1];  //utworzenie graczy, gracze numerowani od "1"
for(int i=1; i<= ilosc_graczy; i++)
{
    gracze[i].hand = new karta[CARDS];
    gracze[i].deck = new karta[CARDS];
}

int policz_karty=0;

for(int j=1; j<=ilosc_graczy; j++ )
{
    fgets(input,MAX_INPUT_LENGTH,fptr); //wpisz informacje o hand gracza
    int reka=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    hand_input3( i, j, &reka, gracze, kolorki, input);//analiza informacji o hand gracza
    wyzeruj( &input);

    
    fgets(input,MAX_INPUT_LENGTH,fptr);//wpisz informacje o deck gracza
    int deck=0;
    for (int i=20; i < MAX_INPUT_LENGTH; i++)
    deck_input3( i, j, &deck, gracze, kolorki, input);//analiza informacji o deck gracza
    wyzeruj( &input);

    zsumuj_karty_graczy(&policz_karty, reka,deck);//zsumuj karty do jednej puli
    
}

const int wszystkie_karty=policz_karty; //ilosc kart w calej talii jest stala



  wypisz_koniec3(ilosc_graczy, gracze);

fclose(fptr);
delete [] gracze;

return 0;
}



 void wypisz_koniec3(int ig, gracz gracze[7])
  {
    for(int j=1; j<=ig; j++)
    {

    int ilosc_kart_na_rece=0;
            cout << j << " player has " ;
           for(int i=0; i<CARDS; i++)
        {
            if(gracze[j].hand[i].wartosc != 0)
                ilosc_kart_na_rece++;
        }

                cout << ilosc_kart_na_rece << " cards on hand" << endl;


    int ilosc_kart_z_eksplozji_kociolka=0;

            cout << j << " player has " ;
           
            for(int i=0; i<CARDS; i++)
            {
                if(gracze[j].deck[i].wartosc != 0)
                ilosc_kart_z_eksplozji_kociolka++;
            }

            cout << ilosc_kart_z_eksplozji_kociolka << " cards in front of him" << endl;

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


void hand_input3( int i, int j, int *reka, gracz *player,char  kolor[][10], char znak[500])
{

                    if(znak[i] == 110) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 117) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 100) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 118) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 121) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 104) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
            else    if(znak[i] == 99) { player[j].hand[*reka].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].hand[*reka].kolor,kolor[0] ); (*reka)++; }
}



void deck_input3( int i, int j, int *deck, gracz *player,char  kolor[][10], char znak[500])
{
    if(znak[i] == 110) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-6], znak[i-7]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 117) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 100) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-4], znak[i-5]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 118) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 121) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-2], znak[i-3]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 104) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-3], znak[i-4]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
            else    if(znak[i] == 99) { player[j].deck[*deck].wartosc = ustaw_wartosc(znak[i-5], znak[i-6]); strcpy( player[j].deck[*deck].kolor,kolor[0] ); (*deck)++; }
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
