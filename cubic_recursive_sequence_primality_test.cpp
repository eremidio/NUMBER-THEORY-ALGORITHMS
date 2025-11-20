//VAMOS CRIAR UM PROGRAMA PARA TESTA AS ROTINAS CRIADAS NO ARQUIVO cubic_recursive_sequence_primality_test.h
//COMPILAR O PROGRAMA COM O COMANDO: g++ -o cubic_recursive_sequence_primality_test cubic_recursive_sequence_primality_test.cpp -O2


//Cabeçalho
#include"cubic_recursive_sequence_primality_test.h"
#include<iostream>
using namespace std;

//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimenntos
    //Recebendo input do usuário
    cout<<"[Inteiro]  n: ";
    cin>> n;

    //Aplicando o teste de primalidade
    if(cubic_recursive_sequence_primality_test(n))
      cout<<n<<" é primo.\n";
    else cout<<n<<" não é primo.\n";

  //Finalizando a aplicação
  return 0;

}
