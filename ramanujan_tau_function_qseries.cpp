//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS CRIADAS NO ARQUIVO ramanujan_tau_function_qseries.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o ramanujan_tau_function_qseries ramanujan_tau_function_qseries.cpp -O3 -lboost_system


//Cabeçalho
#include"ramanujan_tau_function_qseries.h"
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
using namespace boost::multiprecision;
using namespace std;



//Função principal
int main(){

  //Variáveis locais
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n: ";
    cin>>n;

    //Calculando a função τ(n) usando séries q
    compute_ramanujan_tau_function<cpp_int>(n);

  //Finalizando a aplicação
  return 0;

}
