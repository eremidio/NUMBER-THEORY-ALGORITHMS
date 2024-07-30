//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO lucas_sequence_matrix.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o lucas_sequence_matrix lucas_sequence_matrix.cpp -O2


//Cabeçalho
#include"lucas_sequence_matrix.h"
#include<stdint.h>
#include<iostream>
using namespace std;

//Função principal
int main(){

  //Variáveis locais
  int64_t P, Q;
  int64_t n;
  int64_t vn, un, un1, vn1;
  Matrix<int64_t> lucas_sequence;
  Matrix<int64_t> modular_lucas_sequence;

    
  //Procedimentos
    //Recebendo input do usuário
    cout<<"Parâmetro P: ";
    cin>>P;
    cout<<"Parâmetro Q: ";
    cin>>Q;
    cout<<"n: ";
    cin>>n;

    //Calculando a matriz das sequências de Lucas
    lucas_sequence=lucas_sequence_matrix<int64_t, int64_t>(P, Q, n);
    un1=lucas_sequence.matrix[0][0];
    vn1=lucas_sequence.matrix[0][1];
    un=lucas_sequence.matrix[1][0];
    vn=lucas_sequence.matrix[1][1];
    cout<<"U("<<(n+1)<<") = "<<un1<<'\n';
    cout<<"U("<<n<<") = "<<un<<'\n';
    cout<<"V("<<(n+1)<<") = "<<vn1<<'\n';
    cout<<"V("<<n<<") = "<<vn<<'\n';

    //Calculando a matriz das sequências de Lucas a menos de uma relação de congruência
    modular_lucas_sequence=lucas_sequence_modular_matrix<int64_t, int64_t>(P, Q, n, n);
    un1=modular_lucas_sequence.matrix[0][0];
    vn1=modular_lucas_sequence.matrix[0][1];
    un=modular_lucas_sequence.matrix[1][0];
    vn=modular_lucas_sequence.matrix[1][1];
    cout<<"U("<<(n+1)<<") mod "<<n<< " = "<<un1<<'\n';
    cout<<"U("<<n<<") mod "<<n<< " = "<<un<<'\n';
    cout<<"V("<<(n+1)<<") mod "<<n<< " = "<<vn1<<'\n';
    cout<<"V("<<n<<") mod "<<n<< " = "<<vn<<'\n';
  

  //Finalizando a aplicação
  return 0;


}
