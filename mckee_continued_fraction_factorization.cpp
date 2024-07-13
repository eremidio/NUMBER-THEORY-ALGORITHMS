//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO mckee_continued_fraction_factorization.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o mckee_continued_fraction_factorization mckee_continued_fraction_factorization.cpp -O2


//Cabeçalho
#include"mckee_continued_fraction_factorization.hpp"
using namespace std;



//Função principal
int main(){

  //Variáveis locais
  int64_t N;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"Inteiro a ser fatorado: ";
    cin>>N;

    //Executando o algoritmo de Mckee
    mckee_continued_fraction_factorization(N);

  //Finalizando a aplicação
  return 0;

}
