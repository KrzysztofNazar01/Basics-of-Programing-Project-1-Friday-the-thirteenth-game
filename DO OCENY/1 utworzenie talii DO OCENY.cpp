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


int main(){
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

    int kociolki =0;
    int zielone_ilosc=0;
    int zielone_wartosc=0;
    int niezielone_ilosc=0;

//wpisywanie danych do utworzenia gry
        cin >> kociolki;
        cin >> zielone_ilosc;
        cin >> zielone_wartosc;
        cin >> niezielone_ilosc;
    

const int wszystkie_karty=niezielone_ilosc+zielone_ilosc; //ilosc kart w calej talii


    int *niezielone_wartosc = new int[niezielone_ilosc]; //tablica wartosci niezielonych kart

    for(int i = 0; i<niezielone_ilosc; i++) 
        niezielone_wartosc[i] = 0; // wyzerowanie tablicy

    for(int i=0; i<niezielone_ilosc; ++i) //przypisanie wartosci
        cin >> niezielone_wartosc[i];
        


karta *talia = new karta[wszystkie_karty]; //utworzenie talii

    for(int i=0; i<wszystkie_karty; i++)
        talia[i].wartosc = 0; // wyzerowanie tablicy


fopen("NIEPOTASOWANA_TALIA.txt","w");//otworz plik
FILE *fptr; //wskaznik na plik
 // use appropriate location if you are using MacOS or Linux
   fptr = fopen("NIEPOTASOWANA_TALIA.txt","w"); 
    if(fptr == NULL)//w razie nieotworzenia pliku
    {
        cout << "EROOR";  
        return 0;             
    }


    for(int i=0; i<zielone_ilosc; ++i)
        {   talia[i].wartosc= zielone_wartosc; //przypisanie wartosci dla zieloych kart

            if(i==0)
            fprintf(fptr,"%d ",talia[i].wartosc);//zapisanie w pliku

            else
            fprintf(fptr," %d ",talia[i].wartosc);//zapisanie w pliku

            strcpy(talia[i].kolor,kolorki[0] ); //przypisanie zielonego koloru

                int results = fputs(talia[i].kolor, fptr);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR" ;
                    return 0;
                }
        }

    for(int j=1; j<=kociolki; j++)
        {
            for(int k=zielone_ilosc; k<wszystkie_karty; k++)
            {   
                talia[k].wartosc= niezielone_wartosc[k-zielone_ilosc]; //przypisanie wartosci dla niezieloych kart
                fprintf(fptr," %d ",talia[k].wartosc); //zapisanie w pliku

                strcpy(talia[k].kolor,kolorki[j]); //przypisanie niezielonych kolorow

                int results = fputs(talia[k].kolor, fptr);//zapisanie w pliku
                if (results == EOF) //w razie bledu
                {
                    cout << "ERROR";
                    return 0;
                }
                
            }
        }
    


 
   
   fclose(fptr); //zamknij plik

//usuwanie tablic - unikniemy memory leak
    delete [] niezielone_wartosc;
    delete [] talia;

return 0;
}
