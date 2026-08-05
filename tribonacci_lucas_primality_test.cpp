//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO tribonacci_lucas_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o tribonacci_lucas_primality_test tribonacci_lucas_primality_test.cpp -O2


//Cabeçalho
#include"tribonacci_lucas_primality_test.h"
#include<iostream>
using namespace std;

//Função principal
int main(){

  //Variáveis locais
  uint64_t n;

  //Procedimenntos
    //Recebendo input do usuário
    cout<<"[Inteiro]  n: ";
    cin>> n;

    //Aplicando o teste de primalidade
    if(tribonacci_lucas_primality_test(n))
      cout<<n<<" é primo.\n";
    else cout<<n<<" não é primo.\n";


  //Finalizando a aplicação
  return 0;

}
