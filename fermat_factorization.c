//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fermat_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fermat_factorization fermat_factorization.c -lm -O2


//Cabeçalho
#include"fermat_factorization.h"

//Função principal
int main(){

  //Variáveis locais
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%li", &n)!=1) return 0;

    //Fatorando o número em questão
    fermat_factorization_method(n);

  //Finalizando a aplicação
  return 0;
  
}
