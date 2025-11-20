//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO fibonacci_golden_ratio.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fibonacci_golden_ratio fibonacci_golden_ratio.c -lm -lgmp


//Cabeçalho
#include"fibonacci_golden_ratio.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t n;
  mpf_t golden_ratio;
  mpf_init2(golden_ratio, 8192);


  //Procedimento
    //Computando a razão de ouro
    compute_golden_ratio(golden_ratio);
    gmp_printf("φ: %.500Ff\n", golden_ratio);

    //Recebendo o input do usuário
    printf("[Inteiro] n: ");
    scanf("%lu", &n);

    //Computando e exibindo o n-ésimo número de Fibonacci
    compute_nth_fibonnaci_number(n, golden_ratio);

    //Limpando o cachê de memória
    mpf_clear(golden_ratio);


  //Finalizando a aplicação
  return 0;

}

