//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO euler_function_qseries.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o euler_function_qseries euler_function_qseries.cpp


//Cabeçalho
#include"euler_function_qseries.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  polynomial<int64_t> euler_function_qseries;
  vector<int64_t> generalized_pentagonal_numbers;
  vector<int64_t> integer_partition;
  int64_t n;


  //Procedimento
    //Recebendo input do usuário
    cout<<"[Inteiro] n(≳100): ";
    cin>>n;

    //Calculando a aproximação formal da função de Euler
    euler_function_qseries=compute_euler_function_qseries<int64_t>(n);
    cout<<"Expansão formal da função de Euler:\n";
    cout<<"Φ(x) = ...+ "<<euler_function_qseries.algebraic()<<"\n\n";

    //Calculando os números pentagonais generalizados
    cout<<"Lista de números pentagonais generalizados (gk): \n";
    generalized_pentagonal_numbers=compute_generalized_pentagonal_numbers<int64_t, int64_t>(euler_function_qseries);
    for(auto gk:generalized_pentagonal_numbers) cout<<gk<< ", ";
    cout<<"...\n\n";

    //Calculando a função partição
    cout<<"Lista de valores da função partição p(n): \n";
    integer_partition=compute_integer_partition_function<int64_t, int64_t>(generalized_pentagonal_numbers, n);
    int64_t counter=0;

    for(auto pn:integer_partition){
      cout<<"p("<<counter<<") = "<<pn<< ", ";
      counter++;
    }
    cout<<"...\n\n";


  //Finalizando a aplicação
  return 0;

}


