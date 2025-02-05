//VAMOS CRIAR UM PROGRAMA PARA TESTAR ALGUMAS ROTINAS CRIADAS NO ARQUIVO quadratic_frobenius_primality_test_polynomial_version.H
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_frobenius_automorphism quadratic_frobenius_automorphism.c


//Cabeçalho
#include"quadratic_frobenius_primality_test_polynomial_version.h"


//Função principal
int main(){

  //Variáveis locais
  struct frobenius_polynomial identity={1,0}/*f(x)=x*/;
  struct frobenius_polynomial p1, p2, p3, p4, p5, p6;


  //Procedimentos: checando o automorfismo (aritmética) de Fröbenius em corpos finitos
    /*USAREMOS OS PARÂMETROS: n=7, b=1, c=3 NOS TESTES DA ARITMÉTICA*/

    //Testando a relações do teste de Fröbenius
      //1:  x^((n+1)/2) mod (n, x²-bx-c) ∈ Z
      p1=frobenius_automorphism(identity, 4, 7, 1, 3); 
      printf("p1(x)=%lix+%li.\n", ((int64_t)(p1.x1)), ((int64_t)(p1.x0)));

      //2: x^(n+1) mod (n, x²-bx-c) =(-c)
      p2=frobenius_automorphism(identity, 8, 7, 1, 3); 
      printf("p2(x)=%lix+%li.\n", ((int64_t)(p2.x1)), ((int64_t)(p2.x0)));

      //3: teste similar ao de Miller-Rabin para detecção de raízes não triviais n²-1=(2^r)s
      //3.1: x^s mod (n, x²-bx-c) ≠ 1  
      p3=frobenius_automorphism(identity, 3, 7, 1, 3); 
      printf("p3(x)=%lix+%li.\n", ((int64_t)(p3.x1)), ((int64_t)(p3.x0)));

      //3.2: x^s(2^j) mod (n, x²-bx-c) ≠ (-1)  para j=0, 1,..,(r-2)
      p4=frobenius_automorphism(identity, 6, 7, 1, 3); 
      printf("p4(x)=%lix+%li.\n", ((int64_t)(p4.x1)), ((int64_t)(p4.x0)));

      p5=frobenius_automorphism(identity, 12, 7, 1, 3); 
      printf("p5(x)=%lix+%li.\n", ((int64_t)(p5.x1)), ((int64_t)(p5.x0)));
      
      p6=frobenius_automorphism(identity, 24, 7, 1, 3); 
      printf("p6(x)=%lix+%li.\n", ((int64_t)(p6.x1)), ((int64_t)(p6.x0)));


  //Finaliznado a aplicação
  return 0;

}
