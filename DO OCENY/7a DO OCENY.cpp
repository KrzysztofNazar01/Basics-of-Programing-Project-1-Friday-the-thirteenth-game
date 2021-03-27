#include  <iostream>
#include  <string.h>
#include <stdio.h>              

using namespace std;
 
struct karta
{
    int wartosc=0;
    char kolor[10]="0";
};

struct gracz{

    int ilosc_kart_na_rece=0;
    karta hand[1000];

    int ilosc_kart_z_eksplozji_kociolka=0;
    karta deck[500];
    
    int ilosc_kart_kolorow[8]={0};
    int indeksy_kolorow_na_ktore_odporny_jest_gracz[7]={8};

    int ilosc_kart_na_koniec=0;
    int punkty=0;
};

struct kociol{
    
    karta pile[1000];
    int ilosc_kart_w_kociolku=0;
    int kolor_kart[8][100]= {0};
    int suma_wartosci_kart=0;
    int indeksy_kolorow_w_kotle[3]={10};
};


void zmiana( int *wartosc, char *znak,  char *znak1, char *znak2, char *znak3,char *znak4,char *znak5,char *znak6, char *znak7, char (*kolor_karty)[10], char  kolor[][10], int (*spr)[8]);
int ustaw_wartosc(char znak1, char znak2);



    

void zmianag( int *wartosc, char *znak,  char *znak1, char *znak2, char *znak3,char *znak4,char *znak5,char *znak6, char *znak7, char (*kolor_karty)[10], char  kolor[][10], int (*spr)[8], int *ikr);

void zmianak( int *wartosc, char *znak,  char *znak1, char *znak2, char *znak3,char *znak4,char *znak5,char *znak6, char *znak7, char (*kolor_karty)[10], char  kolor[][10], int (*spr)[8], int (*kolorkart1)[8][100], int *a)
{

                    if(*znak == 110) { *wartosc = ustaw_wartosc(*znak6, *znak7); strcpy((*kolor_karty),kolor[0] );  }
            else    if(*znak == 117) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[1] ); (*spr)[1]++; (*kolorkart1)[1][*a]++;   (*a)++; }   
            else    if(*znak == 100) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[2] ); (*spr)[2]++; (*kolorkart1)[2][*a]++;   (*a)++;  }    
            else    if(*znak == 118) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[3] ); (*spr)[3]++; (*kolorkart1)[3][*a]++;   (*a)++; }   
            else    if(*znak == 121) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[4] ); (*spr)[4]++;(*kolorkart1)[4][*a]++;   (*a)++;  }   
            else    if(*znak == 104) { *wartosc = ustaw_wartosc(*znak3, *znak4); strcpy((*kolor_karty),kolor[5] ); (*spr)[5]++; (*kolorkart1)[5][*a]++;   (*a)++; }   
            else    if(*znak == 99 ) { *wartosc = ustaw_wartosc(*znak5, *znak6); strcpy((*kolor_karty),kolor[6] ); (*spr)[6]++; (*kolorkart1)[6][*a]++;   (*a)++; }   
}

int max(int ig, gracz *player)
{int max=1;
    for(int j=1; j<=ig; j++)
    {
        if (player[j].ilosc_kart_na_rece < player[max].ilosc_kart_na_rece ){
            max = j;
        }
    }
    return max;
}


void wybuch(int ik, kociol *kociolki, int treshold, int *koniec, FILE **fptr)
{
    for(int j=1; j<=ik; j++)
    {
        for(int i=0; i<1000; i++)
        {
            kociolki[j].suma_wartosci_kart=kociolki[j].suma_wartosci_kart+kociolki[j].pile[i].wartosc;
        }
        
        if(kociolki[j].suma_wartosci_kart > treshold ) {
            cout << "Pile number " << j <<" should explode earlier" << endl;
            fprintf(*fptr, "%s %d %s","Pile number" ,j, "should explode earlier\n");

            *koniec=1;
        }
            
    }
}


void intro_info(int *nastepny, int ig, int active, int explosion, FILE **fptr)
{
    if(active==ig)
    {
        *nastepny=1;

        cout << "active player = 1" << endl;
        fprintf(*fptr, "active player = 1\n");
    }
    else
    {
        cout << "active player = " << active+1 << endl;
        fprintf(*fptr, "%s %d\n","active player =" ,active+1);
    }

    cout << "players number = "<< ig << endl;
    fprintf(*fptr, "%s %d\n","players number =" ,ig);
 
    cout << "explosion threshold = " << explosion << endl;
    fprintf(*fptr, "%s %d\n","explosion threshold =" ,explosion);

}

int first_card( gracz *player, int active)
{
    int first_card_index=0;
        for(int i=0; i<1000; i++)
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

void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr);
void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr);
void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr);
void wypisz_koncowy(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr);


int main()
{
   kociol kociolki[7];
   
    
    char name[7][5000]={0};
    char name2[7][5000]={0};
    char tablica[100]={0};
    char tablica3[100]={0};
    char kociolwejscie[7][5000] = {0};
    int ilosc_kociolkow=0;
    const int wszystkie_karty=500;
    char kolorki[8][10] = {  
            {"green"} ,  /*  row 0 */
            {"blue"} ,   /*  row 1 */
            {"red"}  ,   /*  row 2 */
            {"violet"},  /*  row 3 */
            {"yellow"},  /*  row 4 */
            {"white"},   /*  row 5 */
            {"black"},   /*  row 6 */
            {" "}
    };

int granica_wybuchu=0;
int spr_kolory[8] ={0};

cin.getline(tablica, 500);
    char *active_player = strrchr(tablica, ' ') + 1;
    int aktywny=*active_player-48;
    
cin.getline(tablica, 500);
    char *players = strrchr(tablica, ' ') + 1;
    int ilosc_graczy =*players-48; 

cin.getline(tablica3, 100);
    granica_wybuchu=(tablica3[22]-48)*10+tablica3[23]-48;


gracz *gracze = new gracz[ilosc_graczy+1];  //utworzenie graczy, gracze numerowani od "1"

for(int j=1; j<=ilosc_graczy; j++ )
{
    cin.getline(name[j],5000, '\n');

    for (int i=20; i<5000; i++)
    {  
           zmiana( &gracze[j].hand[i].wartosc, &name[j][i],  &name[j][i-1], &name[j][i-2], &name[j][i-3], &name[j][i-4], &name[j][i-5],  &name[j][i-6],  &name[j][i-7],  &gracze[j].hand[i].kolor, kolorki, &spr_kolory);
                                     
    }



cin.getline(name2[j],5000,'\n');

    for (int i=20; i<5000; i++)
    {   zmiana( &gracze[j].deck[i].wartosc, &name2[j][i],  &name2[j][i-1], &name2[j][i-2], &name2[j][i-3], &name2[j][i-4], &name2[j][i-5],  &name2[j][i-6],  &name2[j][i-7],  &gracze[j].deck[i].kolor, kolorki,&spr_kolory);    
    }
}


int y=0;
for(int j=1; j<7; j++ )
{
        cin.getline(kociolwejscie[j],5000, '\n');

       
            if(kociolwejscie[j][0]>=48 && kociolwejscie[j][0]<=57) ilosc_kociolkow++; 
            
        
            for (int i=15; i<5000; i++)
            {  
                   zmianak( &kociolki[j].pile[i].wartosc, &kociolwejscie[j][i],  &kociolwejscie[j][i-1], &kociolwejscie[j][i-2], &kociolwejscie[j][i-3], &kociolwejscie[j][i-4], &kociolwejscie[j][i-5],  &kociolwejscie[j][i-6],  &kociolwejscie[j][i-7],  &kociolki[j].pile[i].kolor, kolorki, &spr_kolory, &kociolki[j].kolor_kart, &y);    
     
            }
}



fopen("program.txt","w");//otworz plik
    FILE *fptr; //wskaznik na plik

    fptr = fopen("program.txt","w"); 
    if(fptr == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }

 //ustawienie aktywnego gracza, na koncu przy "return 0" druga czesc procesu ustawiania gracza(przygotowane na kolejna runde)
int next=0;


intro_info(&next, ilosc_graczy, aktywny, granica_wybuchu, &fptr);

 
      



//szukanie ostatniego indeksu w kociolku
int last_in_pile=0;
for(int i=1; i<=1000; i++)
{
    if (kociolki[the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki)].pile[i].wartosc >
        kociolki[the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki)].pile[last_in_pile].wartosc &&
        kociolki[the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki)].pile[i].wartosc !=0)
    {
        last_in_pile = i;
    }
      
}

//przekazanie karty z reki na kociol --> indkes karty w kotle jest o 1 wiekszy niz indeks ostatniej karty na tym kotle
kociolki[the_pile(ilosc_kociolkow, aktywny, gracze, kociolki, kolorki)].pile[last_in_pile+1]=gracze[aktywny].hand[first_card( gracze, aktywny)];


//usuniecie z reki graczy przekazywanej karty 
strcpy (gracze[aktywny].hand[first_card( gracze, aktywny)].kolor,kolorki[8]);
gracze[aktywny].hand[first_card( gracze, aktywny)].wartosc=0;


//wypisanie stanu poczatkowe gry
wypisz_koncowy(ilosc_graczy, ilosc_kociolkow, gracze, wszystkie_karty, kociolki, &fptr);


if(next==1){
    aktywny=1;
    next=0;
}

else
    aktywny++;
return 0;
}



void zmiana( int *wartosc, char *znak,  char *znak1, char *znak2, char *znak3,char *znak4,char *znak5,char *znak6, char *znak7, char (*kolor_karty)[10], char  kolor[][10], int (*spr)[8])
{

                    if(*znak == 110) { *wartosc = ustaw_wartosc(*znak6, *znak7); strcpy((*kolor_karty),kolor[0] ); }
            else    if(*znak == 117) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[1] ); (*spr)[1]++;}   
            else    if(*znak == 100) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[2] ); (*spr)[2]++; }    
            else    if(*znak == 118) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[3] ); (*spr)[3]++;}   
            else    if(*znak == 121) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[4] ); (*spr)[4]++;}   
            else    if(*znak == 104) { *wartosc = ustaw_wartosc(*znak3, *znak4); strcpy((*kolor_karty),kolor[5] ); (*spr)[5]++;}   
            else    if(*znak == 99 ) { *wartosc = ustaw_wartosc(*znak5, *znak6); strcpy((*kolor_karty),kolor[6] ); (*spr)[6]++;}   
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


void wypisz_hand(gracz *player, int i, const int wszystkie_karty , FILE **fptr)
{
    cout << i << " player hand cards: ";
    fprintf(*fptr, "%d %s",  i, "player hand cards:");

        for(int j=0; j<wszystkie_karty; j++)
        {
            //koniec wypisywania kart dla danego gracza
            if(player[i].hand[j].wartosc!=0)
            {
                //wypisza karty danego gracza
                cout << player[i].hand[j].wartosc << " " << player[i].hand[j].kolor << " ";
                
                fprintf(*fptr," %d ", player[i].hand[j].wartosc);//zapisanie w pliku
                int results = fputs(player[i].hand[j].kolor,*fptr);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                }
            }
            
        }
        cout << endl;
        fprintf(*fptr,"\n");
}

void wypisz_deck(gracz *player, int i, const int wszystkie_karty, FILE **fptr)
{
    cout << i << " player deck cards: ";
fprintf(*fptr, "%d %s",  i, "player deck cards:");
            for(int j=0; j<wszystkie_karty; j++)
            {
                if(player[i].deck[j].wartosc!=0)
                {
                    cout << player[i].deck[j].wartosc << " " << player[i].deck[j].kolor << " ";
                    fprintf(*fptr," %d ", player[i].deck[j].wartosc);//zapisanie w pliku

                    int results = fputs(player[i].deck[j].kolor,*fptr);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                    {
                        cout << "ERROR" ;
                    }
                }
                
            }
            cout << endl;
            fprintf(*fptr,"\n");
}

void wypisz_pile(kociol *kociolki, int i, const int wszystkie_karty, FILE **fptr)
{
    cout << i << " pile cards: ";
fprintf(*fptr, "%d %s",  i, "pile cards:");
        for(int j=0; j<wszystkie_karty; j++)
            {
                if(kociolki[i].pile[j].wartosc!=0)
                {
                   cout << kociolki[i].pile[j].wartosc << " " << kociolki[i].pile[j].kolor << " ";
                   fprintf(*fptr," %d ", kociolki[i].pile[j].wartosc);//zapisanie w pliku

                    int results = fputs(kociolki[i].pile[j].kolor,*fptr);//zapisanie w pliku
                    if (results == EOF) //w razie bledu
                    {
                        cout << "ERROR" ;
                    } 
                }
                
            }
           cout << endl;
               fprintf(*fptr,"\n");
}

void wypisz_koncowy(int lg, int ki, gracz *gracze, const int wszystkie_karty, kociol *kociolki, FILE **fptr)
{
     for(int i=1; i<=lg; i++)
    {
        wypisz_hand(gracze, i, wszystkie_karty, fptr);

        wypisz_deck(gracze, i, wszystkie_karty, fptr);
        
    
    }

    for(int i=1; i<=ki; i++)
    {
        wypisz_pile(kociolki, i,wszystkie_karty, fptr);
    }   
}



