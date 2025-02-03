//VAMOS CRIAR UM PROGRAMA PARA TESTAR MAS ROTINAS CRIADAS NO ARQUIVO divisor_counting_lambert_series.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o divisor_counting_lambert_series divisor_counting_lambert_series.cpp


//Cabeçalho
#include"divisor_counting_lambert_series.h"
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
    compute_divisor_counting_function<int64_t>(n);

  //Finalizando a aplicação
  return 0;

} 
