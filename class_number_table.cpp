//VAMOS CRIAR UM PROGRAMA PARA TABULAR NÚMEROS DE CLASSE DE CORPOS ALGÉBRICOS QUADRÁTICOS IMAGINÁRIOS
//COMPILAR ESTE PROGRAMA COM O COMANDO:  g++ -o class_number_table class_number_table.cpp -O3


//Cabeçalho
#include"class_number4.h"
#include<fstream>
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  fstream class_number_file;
  vector<struct class_number_pair> class_number_vector;
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n(≳5): ";
    cin>>n;

    //Abrindo um arquivo para estocar os dados da simulação 
    class_number_file.open("class_number_table.txt", ios::out|ios::app);
    if(class_number_file.is_open()) cout<<"OK!\n\n";

    //Computando o número de classe de discriminantes fundamentais em um intervalo e registrando os dados em um arquivo
    class_number_vector=compute_class_number_fundamental_discriminante(n);

    class_number_file<<"D    h(-D)\n";
    for(auto c:class_number_vector)
      class_number_file<<(-c.d)<<"   "<<c.h<<"\n";


    //Fechando o arquivo
    class_number_file.close();


  //Finalizando a aplicação
  return 0;

}
 

