//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO pell_cubic_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o pell_cubic_primality_test pell_cubic_primality_test.c -lm -O2


//Cabeçalho
#include"pell_cubic_primality_test.h"
#include<cstdio>
using namespace std;


//Função principal
int main(){

  //Váriaveis
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"Digite um número que será testado: ";
    cin>> n;

    //Executando o teste
    if(pell_cubic_primality_test(n)==true)
      printf("Primo encontrado!\n");
    else printf("Número composto.\n");


  //Finalizando a aplicação
  return 0;

}
