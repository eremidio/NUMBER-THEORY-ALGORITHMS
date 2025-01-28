//VAMOS CRIAR UM PROGRAMA PARA TESTAR MAS ROTINAS CRIADAS NO ARQUIVO sum_of_divisors_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o sum_of_divisors_lambert_series sum_of_divisors_lambert_series.cpp


//Cabeçalho
#include"sum_of_divisors_lambert_series.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  int n;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n: ";
    cin>>n;

    //Calculando o número de partições
    compute_sum_of_divisors<int64_t>(n);

  //Finalizando a aplicação
  return 0;

}
