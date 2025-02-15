//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CIRADAS NO ARQUIVO integer_partition_generating_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o integer_partition_generating_function integer_partition_generating_function.cpp -O3 -lboost_system



//Cabeçalho
#include"integer_partition_generating_function.h"
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
using namespace boost::multiprecision;
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
    compute_integer_partitions<cpp_int>(n);

  //Finalizando a aplicação
  return 0;

}
