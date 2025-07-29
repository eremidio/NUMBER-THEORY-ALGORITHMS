//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO chebyshev_polynomials_primality_test.h
//COMPILAR ESTE PROGRAMA COM O SEGUINTE COMANDO: g++ -o chebyshev_polynomials_primality_test chebyshev_polynomials_primality_test.cpp -O2 -lboost_system


//Cabeçalho
#include"chebyshev_polynomials_primality_test.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  string number_string;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n: ";
    cin>>number_string;
    cpp_int n(number_string);


    //Teste de primalidade usando polinômios de Chebyshev
    if(chebyshev_primality_test(n)) cout<<n<<" é primo.\n";
    else  cout<<n<<" não é primo.\n";

  //Finalizando a aplicação
  return 0;

}
