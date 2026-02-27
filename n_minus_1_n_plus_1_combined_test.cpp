//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO n_minus_1_n_plus_1_combined_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o n_minus_1_n_plus_1_combined_test n_minus_1_n_plus_1_combined_test.cpp -lboost_system

//Cabeçalho
#include"n_minus_1_n_plus_1_combined_test.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  string number_string;
  int64_t B;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"Número a ser testado: ";
    cin>> number_string;
    cpp_int n(number_string);

    cout<<"[Parâmetro de profundidade do algoritmo] B: ";
    cin>> B;

    //Testando a primalidade do número em questão
    if(n_minus_one_n_plus_one_combined_primality_test(n, B)==true)
      cout<<n<< " é primo\n";
    else cout<<n<< " não é primo\n";


  //Finalizando o programa
  return 0;

}
