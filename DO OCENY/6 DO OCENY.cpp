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

int min(int ig, gracz *player)
{
int min=1;
        for(int j=1; j<=ig; j++)
        {
            if (player[j].ilosc_kart_na_rece > player[min].ilosc_kart_na_rece ){
                min = j;
            }   
        }
return min;
}

void kolory_w_kociolkach(int ik, kociol *kociolki, int *koniec, FILE **fptr )
{
for(int j=1; j<=ik; j++)
{  
int zapisz=0;
int wypisanie =0;
    for(int m=1; m<7; m++)
    {   
        for(int i=0; i<100; i++)
        if(kociolki[j].kolor_kart[m][i] != 0){
         
            wypisanie++;
            if(wypisanie==1)
            zapisz=m;

            if(m!=zapisz){
                cout << "Two different colors were found on the " << j <<" pile" << endl;
                fprintf(*fptr, "%s %d %s", "Two different colors were found on the" ,j, "pile\n");

                *koniec=1;
            break;
            }
            
        }
        
    }
 
} 
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

void ilosc_kart_na_rekach_graczy(int ig, gracz *gracze, int *koniec,FILE **fptr )
{
    if(gracze[min(ig, gracze)].ilosc_kart_na_rece-gracze[max(ig, gracze)].ilosc_kart_na_rece >= 2){
    cout << "The number of players cards on hand is wrong" << endl;
    fprintf(*fptr,"The number of players cards on hand is wrong\n");

    *koniec=1;
}

}

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
           zmianag( &gracze[j].hand[i].wartosc, &name[j][i],  &name[j][i-1], &name[j][i-2], &name[j][i-3], &name[j][i-4], &name[j][i-5],  &name[j][i-6],  &name[j][i-7],  &gracze[j].hand[i].kolor, kolorki, &spr_kolory, &gracze[j].ilosc_kart_na_rece);
                                     
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


int end=0;

ilosc_kart_na_rekach_graczy( ilosc_graczy, gracze, &end, &fptr);

kolory_w_kociolkach(ilosc_kociolkow, kociolki, &end, &fptr);

wybuch(ilosc_kociolkow, kociolki, granica_wybuchu, &end, &fptr);


    if(end==0)
    {
         cout << "Current state of the game is ok";
    fprintf(fptr,"Current state of the game is ok\n");

    }
   
return 0;
}


void zmianag( int *wartosc, char *znak,  char *znak1, char *znak2, char *znak3,char *znak4,char *znak5,char *znak6, char *znak7, char (*kolor_karty)[10], char  kolor[][10], int (*spr)[8], int *ikr)
{

                    if(*znak == 110) { *wartosc = ustaw_wartosc(*znak6, *znak7); strcpy((*kolor_karty),kolor[0] ); (*ikr)++; }
            else    if(*znak == 117) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[1] ); (*spr)[1]++; (*ikr)++;}   
            else    if(*znak == 100) { *wartosc = ustaw_wartosc(*znak4, *znak5); strcpy((*kolor_karty),kolor[2] ); (*spr)[2]++; (*ikr)++;}    
            else    if(*znak == 118) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[3] ); (*spr)[3]++; (*ikr)++;}   
            else    if(*znak == 121) { *wartosc = ustaw_wartosc(*znak2, *znak3); strcpy((*kolor_karty),kolor[4] ); (*spr)[4]++; (*ikr)++;}   
            else    if(*znak == 104) { *wartosc = ustaw_wartosc(*znak3, *znak4); strcpy((*kolor_karty),kolor[5] ); (*spr)[5]++; (*ikr)++;}   
            else    if(*znak == 99 ) { *wartosc = ustaw_wartosc(*znak5, *znak6); strcpy((*kolor_karty),kolor[6] ); (*spr)[6]++; (*ikr)++;}    
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
   


