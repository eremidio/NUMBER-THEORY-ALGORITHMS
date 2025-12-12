//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO generalized_dirichlet_character.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o generalized_dirichlet_character generalized_dirichlet_character.c -lm  


//Cabeçalho
#include"generalized_dirichlet_character.h"


//Função principal
int main(){

  //Varíaveis locais
  int64_t p, q, m1, m2;
  struct unity_root_q u1, u2, u3;
  struct unity_root_pq u4, u5, u6;

  
  //Procedimento
    //Recebendo input do usuário
    printf("[Primo] q: ");
    scanf("%li", &q);

    rechoice_p:    
    printf("[Primo que divide (q-1)] p: ");
    scanf("%li", &p);
    if((q-1)%p!=0) goto rechoice_p;

    printf("[Inteiro] m1: ");
    scanf("%li", &m1);    
    
    printf("[Inteiro] m2: ");
    scanf("%li", &m2);

    //Computando raízes da unidade módulo q
    u1=set_unity_root_q(m1, q);
    u2=set_unity_root_q(m2, q);
    u3=unity_root_q_mul(&u1, &u2);

    printf("χ(%li; %li) = ", q, m1);
    print_unit_root_q(&u1, Zeta);
    printf("\n");

    printf("χ(%li; %li) = ", q, m2);
    print_unit_root_q(&u2, Zeta);
    printf("\n");
  
    printf("χ(%li; %li)χ(%li; %li) = ", q, m1, q,m2);
    print_unit_root_q(&u3, Zeta);
    printf("\n");  

    //Computando raízes da unidade módulo q de ordem
    u4=set_unity_root_pq(m1, p, q);
    u5=set_unity_root_pq(m2, p, q);
    u6=unity_root_pq_mul(&u4, &u6);

    printf("χ(%li, %li; %li) = ", p, q, m1);
    print_unit_root_pq(&u4, Zeta);
    printf("\n");

    printf("χ(%li, %li; %li) = ", p, q, m2);
    print_unit_root_pq(&u5, Zeta);
    printf("\n");
  
    printf("χ(%li, %li; %li)χ(%li, %li; %li) = ", p, q, m1, p, q, m2);
    print_unit_root_pq(&u6, Zeta);
    printf("\n");  


  //Finalizando a aplicação
  return 0;


}
