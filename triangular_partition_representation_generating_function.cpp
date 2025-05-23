//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO triangular_partition_representation_generating_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o triangular_partition_representation_generating_function triangular_partition_representation_generating_function.cpp


//Cabeçalho
#include"triangular_partition_representation_generating_function.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  int64_t n, k;


  //Procedimento
    //Recebendo input do usuário
    cout<<"[Inteiro] n(≳100): ";
    cin>>n;

    cout<<"[Inteiro] k: ";
    cin>>k;


    //Computando a função geradora da função de contagem de partições triangulares
    polynomial<int64_t> triangular_polynomial=compute_triangular_partition_generating_function<int64_t>(n, k);
    cout<<"[Função geradora de partições triângulares] p(x) = "<<triangular_polynomial.algebraic()<<'\n';


    //Computando números de partições triângulares
    vector<int64_t> generalized_triangular_partition_number=compute_triangular_partition_function<int64_t,  int64_t>
                                                            (triangular_polynomial, n);

    cout<<"\nNúmero de partições triangulares com "<< k<< " elementos: ";
    for(int64_t j=0; j<generalized_triangular_partition_number.size(); ++j)
      cout<<"t("<<k<<", "<<j<<")="<<generalized_triangular_partition_number[j]<<", ";
    cout<<"...\n";


  //Finalizando a aplicação
  return 0;


}
