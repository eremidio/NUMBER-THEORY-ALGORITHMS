//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO class_number4.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o class_number4 class_number4.cpp 


//Cabeçalho
#include"class_number4.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  vector<struct class_number_pair> class_number_vector;
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n(≳5): ";
    cin>>n;

    //Computando o número de classe de discriminantes fundamentais em um intervalo
    class_number_vector=compute_class_number_fundamental_discriminante(n);
    
    for(auto c:class_number_vector) cout<<"h("<<c.d<<")="<<c.h<<", ";
    cout<<"...\n";

  //Finalizando a aplicação
  return 0;

}
 
