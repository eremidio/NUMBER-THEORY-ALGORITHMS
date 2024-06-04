//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO linear_diofantine_equation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o linear_diofantine_equation linear_diofantine_equation.c


//Cabeçalho
#include"linear_diofantine_equation.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t a, b, c, d;
  
  //Procedimentos 
    //Recebendo input do usuário
    printf("Equação diofantina linear a ser resolvida: ax+by+cz=d\n");
    printf("a: ");
    scanf("%li", &a);
    printf("b: ");
    scanf("%li", &b);
    printf("c: ");
    scanf("%li", &c);
    printf("d: ");
    scanf("%li", &d);

    //Resolvendo o sistema de equações diofantinas lineares
    linear_diofantine_equation2(a, b, c, d);


  //Finalizando a aplicação
  return 0;

          }
