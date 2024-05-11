//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fibonacci_matrix.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: clang++ -o fibonacci_matrix fibonacci_matrix.cpp -O2


//Cabeçalho
#include"fibonacci_matrix.h"
using namespace std;


//Função principal
int main(){

 //Variáveis locais
 uint64_t fib;
 int n;

 //Procedimentos
  //Recebendo input do usuário
  cout<<"Digite um inteiro (n): ";
  cin>>n;


  //Calculando o n-ésimo termo da sequência de Fibonacci
  fib=fibonacci_matrix(n);
  cout<<"F("<<n<<"): "<<fib<<'\n';


 //Finalizando a aplicação
 return 0;

          }; 
