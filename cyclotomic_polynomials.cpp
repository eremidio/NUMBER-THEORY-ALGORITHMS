//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cyclotomic_polinomials.hpp
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o  cyclotomic_polynomials cyclotomic_polynomials.cpp -lm -O2


//Cabeçalho
#include"cyclotomic_polynomials.hpp"
using namespace std;


//Função principal
int main(){

 //Variáveis locais
 int32_t n;
  
 //Procedimentos
  //Recebendo input do usuário
  cout<<"Digite um inteiro: ";
  cin>> n;

 //Calculando o n-ésimo polinômio ciclotômico
 polynomial<int32_t> n_cyclotomic_polynomial=generate_cyclotomic_polynomial(n);
 cout<<"Φ("<<n<<", x)="<< n_cyclotomic_polynomial.algebraic()<<'\n';


 //Teste de primalidade usando polinômio ciclotômicos
 cout<<"Digite um inteiro cuja primalidade será testada: ";
 cin>>n;

 if(cyclotomic_polynomial_prime_test(n)==true)
  cout<< n <<" é primo.\n";
 else
  cout<< n <<" não é primo.\n";



 //Finalizando a aplicação
 return 0;

          }
