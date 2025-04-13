//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lucas_sequence_generating_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o lucas_sequence_generating_function lucas_sequence_generating_function.cpp -O2


//Cabeçalho
#include"lucas_sequence_generating_function.h"
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
    cout<<"[Inteiro-Número de termos na sequência] n: ";
    cin>>n;

    //Teste 1: computando os números de Mersenne
    cout<<"Números de Mersenne: ";
    std::vector<cpp_int> mersenne_vector=compute_lucas_sequence_first_kind<cpp_int>(3,2,n);
    for(int64_t i=0; i<=n; i++) cout<<"M("<<i<<")= "<<mersenne_vector[i]<<", ";
    cout<<"...\n\n";
        
    //Teste 2: computando os números de Jacobsthal-Lucas
    cout<<"Números de Jacobsthal-Lucas: ";
    std::vector<cpp_int> jacobstal_lucas_vector=compute_lucas_sequence_second_kind<cpp_int>(1,(-2),n);
    for(int64_t i=0; i<=n; i++) cout<<"J("<<i<<")= "<<jacobstal_lucas_vector[i]<<", ";
    cout<<"...\n";
        

  //Finalizando a aplicação
  return 0;

}
