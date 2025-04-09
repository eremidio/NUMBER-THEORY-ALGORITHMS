//VAMOS CRIAR UM PROGRAMA PARA TESTARAS ROTINAS CRIADAS NO ARQUIVO strong_lucas_pseudoprime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o strong_lucas_pseudoprime_test strong_lucas_pseudoprime_test.cpp -O2


//Cabeçalho
#include"strong_lucas_pseudoprime_test.h"
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
    if(strong_lucas_primality_test(n, Yes)==true)
      printf("Primo encontrado!\n");
    else printf("Número composto.\n");


  //Finalizando a aplicação
  return 0;
}
