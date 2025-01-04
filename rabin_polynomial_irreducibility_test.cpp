//VAMOS CRIAR UMPROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO rabin_polynomial_irreducibility_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o rabin_polynomial_irreducibility_test rabin_polynomial_irreducibility_test.cpp


//Cabeçalho
#include"rabin_polynomial_irreducibility_test.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  polynomial<int64_t> f_poly;
  int64_t field_characteristic;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Característica-primo base de GF(p)] p: ";
    cin>> field_characteristic;

    f_poly.set();
    cout<<"f(x): "<<f_poly.algebraic()<<'\n';
    
    //Redução dos coeficientes do polinômio
    for (auto& c:f_poly.polynomial_coefficients) c%=field_characteristic;
    cout<<"f(x) mod ("<<field_characteristic<<"): "<<f_poly.algebraic()<<'\n';

    //Teste de irredutibilidade 
    if(rabin_irredutibility_criterion<int64_t>(f_poly, field_characteristic)==true)
      cout<<"f(x) é irredutível em GF("<<field_characteristic<<")\n";
    else cout<<"f(x) não é irredutível em GF("<<field_characteristic<<")\n";


  //Finalizando a aplicação
  return 0;

}
