#VAMOS CRIAR UM SCRIPT AWK PARA ANALISAR O ARQUIVO OBTIDO COM O PROGRAMA DO ARQUIVO abc_conjecture.c
#USAR ESTE SCRIPT COM COMANDO: awk -f abc_conjecture.awk ABC_TEST.txt

#Recebendo input do usuário
BEGIN{

  counter = 0
  epsilon = 0
  printf "[Parâmetro que define a qualidade de uma tripla ordenada] ε (ε>0 e ε<1): "
  getline epsilon < "-"
  
  epsilon+=1

  printf "Lista de triplas ordenadas encontradas satisfazendo a condição q(a,b,c)>{1+ε}:\n"

}


#Loop principal determinando quais triplas ordenadas possuem a qualidade mínima especificada
NR>=4 && $4>=epsilon{
  print $0
}



