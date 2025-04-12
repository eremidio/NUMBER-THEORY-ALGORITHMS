//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO sylvester_cyclotomic_numbers.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o sylvester_cyclotomic_numbers sylvester_cyclotomic_numbers.cpp -lm -O2 


//Cabeçalho
#include"sylvester_cyclotomic_numbers.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  int64_t n, P, Q;

  
  //Procedimentos
    //Recebendo input do usuario
    cout<<"[Inteiro] n: ";
    cin>>n;
    cout<<"[Inteiro - parâmetro da sequência de Lucas] P: ";
    cin>>P;
    cout<<"[Inteiro - parâmetro da sequência de Lucas] Q: ";
    cin>>Q;


    //Computando os números ciclotômicos de Sylvester em um intervalo
    vector<cpp_int> sylvester_cyclotomic_vector=compute_sylvester_cyclotomic_numbers(P, Q, n);
    for(int64_t i=0; i<=n; ++i)  cout<<"Q("<<i<<")= "<<sylvester_cyclotomic_vector[i]<<", ";
    cout<<"...\n";

    //Teste de primalidade de Ward
    cout<<"Primos inferiores a 40: \n";
    for(int64_t j=2; j<40; ++j){
      if(ward_primality_test(j, sylvester_cyclotomic_vector)==true) cout<<j<<", ";
    }
    cout<<"...\n";


  //Finalizando a aplicação
  return 0;

}

