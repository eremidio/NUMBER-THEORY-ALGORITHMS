//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO baby_step_giant_step_binary.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o baby_step_giant_step_linear baby_step_giant_step_linear.c -O2 -lm



//Cabeçalho
#include"baby_step_giant_step_linear.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t a, c, m, log;


  //Procedimentos 
    //Recebendo input do usuário
    printf("Base: ");
    if(!scanf("%li", & a)) return 0;
    printf("Logaritmando: ");
    if(!scanf("%li", & c)) return 0;
    printf("Módulo: ");
    if(!scanf("%li", & m)) return 0;


    //Cálculo do logaritmo discreto
    log =baby_step_giant_step_linear(a, c, m);
    printf("Logaritmo de %li na base %li mod %li é %li.\n", c, a, m, log);


  //Finalizando a aplicação
  return 0;

          }
