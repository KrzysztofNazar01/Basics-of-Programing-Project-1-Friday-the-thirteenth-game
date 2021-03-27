#include <stdio.h>
#include <iostream>

using namespace std;


int main () {
   FILE *fp;
   char input[1000]={0};

   fp = fopen("file.txt","r");
   while(cin.getline(input,100)) {
      input = fgets(fp);
      if( feof(fp) ) { 
         break ;
      }
      
   }
   fclose(fp);
   
   return(0);
}