//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO shanks_class_group_factorization.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o shanks_class_group_factorization shanks_class_group_factorization.c -lm -lpari


//Cabeçalho
#include<pari/pari.h>
#include"shanks_class_group_factorization.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t N;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%li", &N);

    //Computando o discriminante fundamental D e o número de classe associado
    int64_t D=generate_fundamental_discriminant(N);
    printf("[Discriminante fudamental] D: %li\n", D);
    int64_t hD;

    //-------------------------------------------------------------

        /*
          NOTA: Para que o algoritmo funcione corretamente é necessário que se compute o número de classe 
                de um corpo quadrático imaginário cujo discriminante é fundamental, tal tarefa é 
                extremamente complicada. E no presente momento a minha melhor implementação é razoável
                para valores apenas da ordem de 10^13. Por esta razão usaremos a biblioteca PARI/GP para 
                tal tarefa. Este pedaço de código pode ser encapsulado em uma função se necessário.
          
                Apenas o valor de h(D) é necessário no algoritmo principal. Uma possibilidade é usar o
                interpretador gp ou outra biblioteca externa para se obter o valor de h(D) rapidamente 
                para inteiros de até 64 bits e manualmente passar este argumento para a função principal.

                Argumentos heurísticos sugerem que no geral h(D) é altemente divisível por pequenos primos
                e tem valor da ordem de O(√D) (mais precisamente no intevalo [√D-Cln(|D|), √D+Cln(|D|)]
                para uma constante C). Uma possibilidade é a escolha de formas aleatórias e testar todos 
                os valores possíveis de h(D) neste intervalo, evitando assim a necessidade de se computar
                h(D) exatamente. Tal estratégia é adotada, por exemplo, no algoritmo subexponencial de 
                Schnorr–Seysen–Lenstra.
        */

        //Inicializando o PARI
        pari_init(1000000/*bytes para Stack*/, 500000/*bytes para objetos locais*/);

        //Convertendo inteiro para tipo numérico GEN (padrão PARI/GP)
        GEN N0 = stoi(D);

        //Computando o número de classe
        GEN class_num = qfbclassno0(N0, 0);

        //Estocando o valor em uma variável tipo C
        hD = itos(class_num);

        //Finalizando o PARI
        pari_close();
    //-------------------------------------------------------------

    printf("[Número de classe associado a Q(√%li)] h(D): %li\n", D, hD);

    //Fatorando números inteiros usando o algoritmo de Shanks
    shanks_class_group_factorization(N, D, hD);


  //Finalizando a aplicação
  return 0;

}
