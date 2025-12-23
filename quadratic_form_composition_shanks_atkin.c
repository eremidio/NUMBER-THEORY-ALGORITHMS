//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO NO ARQUIVO quadratic_form_composition_shanks_atkin.h
//COMPILAR ESTE PROGRAMACOM O COMANDO: gcc -o quadratic_form_composition_shanks_atkin quadratic_form_composition_shanks_atkin.c -lm


//Cabeçalho
#include"quadratic_form_composition_shanks_atkin.h"


//Função principal
int main(){

  //Variáveis locais
  struct binary_quadratic_form f1, f2, f3;  


  //Procedimentos
    //Recebendo input do usuário
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] a:");
    scanf("%li", &f1.a);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] b:");
    scanf("%li", &f1.b);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] c:");
    scanf("%li", &f1.c);
    
    f1=reduce_quadratic_form(f1);
    if(f1.a < 0){
        f1.a = -f1.a;
        f1.b = -f1.b;
        f1.c = -f1.c;
    }
    print_binary_quadratic_form(f1); printf("\n");
    printf("[Discriminante] Δ(f1): %li\n", binary_quadratic_form_discriminant(f1));


  
    //Aplicando o algoritmo de composição  e duplicação de formas quadráticas 
    printf("[Duplicação de formas quadráticas] ");
    f2=NUDUPL(f1);
    print_binary_quadratic_form(f2); printf("\n");
    printf("[Discriminante] Δ(f2): %li\n", binary_quadratic_form_discriminant(f2));

    printf("[Composição de formas quadráticas] ");
    f3=NUCOMP(f1, f2);
    print_binary_quadratic_form(f3); printf("\n");
    printf("[Discriminante] Δ(f3): %li\n", binary_quadratic_form_discriminant(f3));
    printf("\n");

  //Finalizando a aplicação
  return 0;

} 
