#VAMOS CRIAR UM MÓDULO EM PYTHON PARA GERAR NÚMEROS PRIMOS

'''
NOTA: no presente algoritmo o usuário deve suprir uma semente para geração de números primos.
Isto pode ser feito de duas formas: recebendo input direto ou usando um gerador de números
pseudoaleatórios dentro do limite desejado.

'''
#----------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS
from strong_fermat_primality_test_1024bit import strong_fermat_primality_test_1024bit
import gmpy2


#----------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def preculling_step(n:int)->bool:
  '''Função usada para rápida detecção de compostos'''

  #Etapa 1: testes envolvendo classes residuais mod 210
  if((n%210) not in {1, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139,
                    143, 149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209}):
    return False 



  #Etapa 2: teste por fatores primos até 1000 usando o algoritmo de Euclides
  common_factor_list:list=[2305567963945518424753102147331756070, 3383080509296917481189798760796480670771162183, 262025664754470334382813071883984477441, 49766523393936228750138598082752980119549, 1227453540237014997887615651109181957903188941, 253056306993037840092244562196981381959, 879031892818978804933065306274691112009314693, 16866467815653776127243907167629319108817, 83623435734606723958852552002152901629917681, 500139990716305530696933027389294139003181]


  for tester in  common_factor_list:
    if(gmpy2.gcd(tester, n)>2):
      return False


  #Caso um número  passe nos testes acima um forte candidato a primo foi encontrado
  return True 


#2
def prime_generator(n:int)->None:
  '''Função usada para gerar uma tripla ou dupla números primos'''

  #Restrição a inteiros superiores a 1013:
  if(n<1013):
    print("Semente para geração de números primos muito pequena")
    return

  #Checando se o número em questão é primo:
  if(preculling_step(n)==False):
    print(n, ' não é primo')
  elif(strong_fermat_primality_test_1024bit(n)==True):
    print(n, '  é primo')
  else:
    print(n, ' não é primo')


  #Variáveis locais
  n_minus:int=n-1
  n_plus:int=n+1


  #Procedimentos
  #Gerando o menor primo superior ao número em questão
  while(1):
    if(preculling_step(n_plus)==True and strong_fermat_primality_test_1024bit(n_plus)==True):
      break
    else:
      n_plus+=1

  #Gerando o maior primo inferior ao número em questão
  while(1):
    if(preculling_step(n_minus)==True and strong_fermat_primality_test_1024bit(n_minus)==True):
      break
    else:
      n_minus-=1


  #Resultado da execução do algoritmo
  print('Antecessor na sequência de números primos: ', n_minus)
  print('Sucessor na sequência de números primos: ', n_plus)

