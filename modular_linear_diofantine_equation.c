//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADASNO ARQUIVO modular_linear_diofantine_equation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o modular_linear_diofantine_equation modular_linear_diofantine_equation.c -lm


//Cabeçalho
#include"modular_linear_diofantine_equation.h"

//Função principal 
int main(){

  //Variáveis locais
  int64_t a, b, n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Equação diofantina linear a ser resolvida: ax=b (mod n)\n");
    printf("a: ");
    scanf("%li", &a);
    printf("b: ");
    scanf("%li", &b);
    printf("n: ");
    scanf("%li", &n);    

    //Resolvendo a equação linear
    modular_linear_diofantine_equation(a, b, n);

  //Resultado
  return 0;

          }
