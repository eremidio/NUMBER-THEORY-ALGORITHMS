//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO pell_equation.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pell_equation pell_equation.c -lm -O2


//Cabeçalho
#include"pell_equation.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("n: ");
    if(scanf("%li", &n)!=1) return 0;

    //Calculando as soluções da equação de Pell usando convergentes da solução em frações continuadas
    pell_equation(n);


  //Finalizando a aplicação
  return 0;


}
