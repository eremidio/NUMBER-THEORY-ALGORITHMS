//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADASNO ARQUIVO garner_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o garner_algorithm garner_algorithm.c -lm


//Cabeçalho
#include"int128.h"
#include"garner_algorithm.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t k, i;
  int64_t N=1;
  __int128_t  x;

  //Procedimentos
    //Recebendo input do usuário
    printf("Usuário digite o número de equações modulares: ");
    scanf("%li",&k);

    //Preenchendo os arrays contendo os valores de a(i) e n(i)
    int64_t a[k], n[k];

    for(i=0; i<k; ++i){
      printf("Entre com o valor de n(%li): ", i);
      scanf("%li", &n[i]);
      printf("Entre com o valor de a(%li): ", i);
      scanf("%li", &a[i]);
      N*=n[i];
    }; 

    for(i=0; i<k; ++i)
    printf("x ≡ %li mod(%li)\n", a[i], n[i]);

    //Computando valor de x e exibindo o resultado
    x=garner_algorithm(a, n, k);
    printf("[Solução] x = "); printf128(x);
    printf("[Congruente]M = %li\n", N);


  //Finalizando a palicação
  return 0;

};

