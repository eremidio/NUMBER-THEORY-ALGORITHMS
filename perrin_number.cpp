//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO perrin_number.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o perrin_number perrin_number.cpp -O2


//Cabeçalho
#include"perrin_number.h"
using namespace std;

//Função principal
int main(){

  //Variáveis locais
  Matrix<int64_t> perrin1, perrin2, perrin3;
  int64_t n;

  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] n: ";
    cin>> n;

    //Calculando as matrizes que definem o coeficientes de Perrin
    perrin1=perrin_matrix_positive_n<int64_t>(n);
    perrin2=perrin_matrix_negative_n<int64_t>(n);
    perrin3=modular_perrin_matrix<int64_t>(n, n);

    //Exbindo o resultado do cálculo
    cout<<"P("<<n<<"): "<<perrin1.matrix[0][0]<<'\n';
    cout<<"P("<<(n+1)<<"): "<<perrin1.matrix[1][0]<<'\n';
    cout<<"P("<<(n+2)<<"): "<<perrin1.matrix[2][0]<<'\n';

    cout<<"P("<<(-n)<<"): "<<perrin2.matrix[0][0]<<'\n';
    cout<<"P("<<(1-n)<<"): "<<perrin2.matrix[1][0]<<'\n';
    cout<<"P("<<(2-n)<<"): "<<perrin2.matrix[2][0]<<'\n';

    cout<<"P("<<n<<") mod "<<n<<": "<<perrin3.matrix[0][0]<<'\n';
    cout<<"P("<<(n+1)<<") mod "<<n<<": "<<perrin3.matrix[1][0]<<'\n';
    cout<<"P("<<(n+2)<<") mod "<<n<<": "<<perrin3.matrix[2][0]<<'\n';
    
  //Resultado
  return 0;

}
