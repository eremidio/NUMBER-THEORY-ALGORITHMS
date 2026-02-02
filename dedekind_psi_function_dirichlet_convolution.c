//VAMOS CRIA UM PROGRAMA PARA TESTAR AS FUNÇÕES CXRIADAS NO ARQUIVO dedekind_psi_function_dirichlet_convolution.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o dedekind_psi_function_dirichlet_convolution dedekind_psi_function_dirichlet_convolution.c -O2


//Cabeçalho
#include"dedekind_psi_function_dirichlet_convolution.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Calculando a função de psi de Dedekind no intervalo {1,2,...,n}
    int32_t* dedekind_psi_array = compute_dedekind_psi_function(n);

    for(int32_t i=1; i<=n; ++i) printf("ψ(%i)=%i, ", i, dedekind_psi_array[i]);
    printf("...\n");


    //Limpando o cachê de memória
    if(dedekind_psi_array) free(dedekind_psi_array); dedekind_psi_array=NULL;


  //Finalizando a aplicação
  return 0;

}
