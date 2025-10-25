//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO cyclotomic_polynomials2.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o cyclotomic_polynomials2 cyclotomic_polynomials2.cpp -O2



//Cabeçalho
#include"cyclotomic_polynomials2.h"
using namespace std;


//Função principal
int main(){

//Variáveis locais
 int64_t n;
  
 //Procedimentos
  //Recebendo input do usuário
  cout<<"Digite um inteiro: ";
  cin>> n;

   //Calculando o n-ésimo polinômio ciclotômico
   polynomial<int64_t> n_cyclotomic_polynomial = compute_cyclotomic_polynomial<int64_t>(n);
   cout<<"Φ("<<n<<", x)="<< n_cyclotomic_polynomial.algebraic()<<'\n';


 //Finalizando a aplicação
 return 0;

}
