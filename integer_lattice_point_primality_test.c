//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO integer_lattice_point_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o integer_lattice_point_primality_test integer_lattice_point_primality_test.c -O2 -lm


//Cabeçalho
#include"integer_lattice_point_primality_test.h"

//Função principal
int main(){

  //Variáveis locais
  uint64_t n;

  //Procedimentos
    //Recebendo input do usuário
    printf("Inteiro a ser testado: ");
    if(scanf("%lu", &n)!=1) return 0;

    //Testando a primalidade do número em questão
    if(integer_lattice_point_primality_test(n))
      printf("%lu é primo.\n", n);
    else printf("%lu não é primo.\n", n);


  //Resultado
  return false;

}
