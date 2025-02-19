//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO fibonacci_generating_function.h
//COMPILAR ESTE PROGRANA COM O COMANDO: g++ -o fibonacci_generating_function fibonacci_generating_function.cpp -O2


//Cabeçalho
#include"fibonacci_generating_function.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  polynomial<int64_t> fib_poly;
  vector<int64_t> fibonacci_numbers;
  int64_t n;


  //Procedimento
    //Recebendo input do usuário
    cout<<"[Inteiro] n(≳10): ";
    cin>>n;

    //Calculando a aproximação formal da série geradora da sequência de Fibonacci
    fib_poly=generate_fibonacci_polynomial<int64_t>(n);
    cout<<"Parcial da série geradora da sequência de Fibonacci:\n";
    cout<<"F(x) = ...+ "<<fib_poly.algebraic()<<"\n\n";


    //Exibindo a sequência de Fibonacci
    fibonacci_numbers=compute_fibonacci_numbers<int64_t>(fib_poly);

    for(auto fib:fibonacci_numbers){
      cout<<"F("<<n<<")="<<fib<<", ";
      n--;
    }
    cout<<"...\n\n";    

  //Finalizando a aplicação
  return 0;

}

