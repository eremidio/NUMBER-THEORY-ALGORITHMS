//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cloitre_conjecture.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cloitre_conjecture cloitre_conjecture.c -lm -O2 -lgmp


//Cabeçalho
#include"cloitre_conjecture.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%lu", &n)!=1) return 0;

    //Gerando primos recursivamente usando a relação de Cloitre
    printf("Primos gerados usando a relação recursiva de Cloitre: ");
    cloitre_recursive_prime_generation(n);


  //Finalizando a aplicação
  return 0;

}
