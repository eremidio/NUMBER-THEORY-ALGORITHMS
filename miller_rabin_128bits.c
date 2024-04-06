//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO miller_rabin_128bits.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o miller_rabin_128bits miller_rabin_128bits.c -O2 -lm


//Cabeçalho
#include"miller_rabin_128bits.h"

//Função principal
int main(){
//Variáveis locais
__int128_t number;
char number_string[45];

//Recebendo o input
printf("Número a ser testado: ");
if(scanf("%s", number_string)!=1)
return 0;
number=scanf128(number_string);

//Usando o teste de Miller-Rabin para inteiros de 128 bits
if(miller_rabin128(number)==true)
printf("O número em questão é (forte candidato a) primo.\n");
else
printf("O número em questão é composto.\n");

//Finalizando a aplicação
return 0;
          }
