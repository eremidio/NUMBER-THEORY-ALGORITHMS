//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO irrational_root_approximation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o irrational_root_approximation irrational_root_approximation.c -lgmp


//Cabeçalho
#include"irrational_root_approximation.h"


//Programa principal
int main(){

  //Variáveis locais
  unsigned long n;
  int ord;

  //Procedimentos
    //Recebendo input do usuário
    printf("Radicando: ");
    scanf("%lu", &n);
    printf("Número de aproximações para √%li: ", n);
    scanf("%i", &ord);

    //Calculando convergentes de raízes irracionais
    irrational_root_approximation(n, ord);


  //Finalizando a aplicação
  return 0;

}
