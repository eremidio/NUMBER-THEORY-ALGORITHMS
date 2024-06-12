//VAMOS CRIAR UM PROGRAMA QUE TESTA A CONJECTURA DE COLLATZ
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o collatz_conjecture collatz_conjecture.cpp

/*
PARA MAIORES INFORMAÇÕES SOBRE A CONJECTURA DE COLLATZ: https://en.wikipedia.org/wiki/Collatz_conjecture
*/



//Cabeçalho
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

//Função principal

int main(){

  //Variáveis usadas no programa
  long long int valor, contador;
  long long int* ponteiro=(long long int*)malloc(sizeof(long long int));
  fstream arquivo;

  //Procedimentos
    //Abrindo um arquivo para estocar os dados altere o nome do arquiv caso queira executar mais de uma simulação 
    arquivo.open("3to1.txt", ios::out|ios::app);

    if(arquivo.is_open())
      cout<<"OK!\n\n";

    //Entrada de dados do usuário
    cout<<"Digite um número inteiro maior que 1 para que possamos testar a conjectura 3n+1:\n";
    cin>>valor;
    contador=0;
    arquivo<<"Valor inicial: "<<valor<<".\n";

    //Loop principal
    do{
       contador= contador+1;
       switch(valor%2){
        case 0:
          {*ponteiro=valor/2; break;};
        case 1:
          {*ponteiro=3*valor+1; break;};
       };



      //Exibindo a sequência de resultados na tela e salvando o conteúdo no arquivo
      cout<<*ponteiro<<"\n";
      arquivo<<*ponteiro<<"\n";

      //Atualizando a variável principal
      valor=*ponteiro;

    }while(valor!=1);

  //Exbindo  o resuçltado de execução do algoritmo
  cout<<contador <<" iterações até cair no loop principal\n";
  arquivo<<"Número de iterações para alcançar o loop principal: "<<contador<<"\n";


  //Fechando o arquivo, limpando o cachê de memória e encerrando o programa
  arquivo.close();
  free(ponteiro);
  return 0;

}
