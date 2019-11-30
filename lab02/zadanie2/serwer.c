#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void wpisz(char tresc[50])
{
  int bufor_wyniki = open("wyniki",O_RDWR);
  write(bufor_wyniki,"SERWER: ",8);
  write(bufor_wyniki, tresc,50);
  unlink("lockfile");
  close(bufor_wyniki);
}
int main()
{
  while(1)
    {
      if(access("lockfile",F_OK) != -1)
      {
          int bufor_dane = open("dane", O_RDWR);
          if(bufor_dane < 0)
          { 
            char blad[27] = "Nie mozna otworzyc bufora\n";
            wpisz(blad);
            break;
          }
          else
          {
            char slowo[50] = "";
            char tresc[50] = "";
            while(1)
            {
              read(bufor_dane, slowo, 50);
              close(bufor_dane);
              printf("%s \n", slowo);
              printf("Podaj tresc wiadomosci.\n");
              fgets(tresc,50,stdin);
              wpisz(tresc);
              break;
            }
          }
        }
      }
  printf("\n");
  return 0;
}