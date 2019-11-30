#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void odczyt(){
  FILE *buforo  = fopen("wyniki", "r");
  if(buforo){
    char slowo[50];
    char c;
    while((c = fscanf(buforo, "%s", slowo)) != EOF){
      printf("%s " , slowo); }
    printf("\n");
    fclose(buforo); }
  else printf("Nie mozna odczytac zawartosci bufora.\n");
}

void serwer(){
  while(open("lockfile", O_CREAT|O_EXCL, 0) == -1){
    printf("Serwer zajety, prosze czekac\n");
    sleep(5); }
}

void czyscbufor(){
  FILE *buforc = fopen("dane", "w");
  if(buforc){
    char cz[1] = "";
    fprintf(buforc, "%s", cz);
    fclose(buforc); }
}

int main(int argc, char *argv[]){

  char tekst[50];
  int bufor = open("dane", O_RDWR);
  
  czyscbufor();

  printf("Podaj tresc wiadomosci:\n");
  fgets(tekst,50,stdin);
  write(bufor, tekst, 50);
  close(bufor);

  serwer();

  while(1)
  {
    if(access("lockfile", F_OK) == -1)
    {
      odczyt();
      break;
    }
  }
  return 0;
}