//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO sum_of_squares_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o sum_of_squares_function sum_of_squares_function.cpp



//Cabeçalho
#include"sum_of_squares_function.h"
using namespace std;



//Função principal
int main(){

  //Variáveis locais
  int64_t k, n;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n: ";
    cin>>n;
    cout<<"[Inteiro] k: ";
    cin>>k;

    //Calculando o número de partições
    compute_sum_of_squares_function<int64_t>(k, n);

  //Finalizando a aplicação
  return 0;

}
