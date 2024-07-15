#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VARIANTE DO TESTE DE PRIMALIDADE FERMAT CAPAZ DE DETECTAR NÚMEROS DE CARMICHAEL

'''
PARA REFERÊNCIAS: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/strong_fermat_primality_test.h
                  https://arxiv.org/pdf/math/0604376


'''

#----------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS
from math import gcd, log

#----------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def strong_fermat_primality_test_1024bit(n:int)->bool:
  '''Função que implementa a variante determinística do teste de Fermat que detecta números de Carmichael'''
  #Casos bases:
  if(n<2):
    return False
  if(n in {2,3,5,7,11,13,17}):
    return True


  #Variáveis locais
  mod:int=0
  max_mod:int=int(2*log(n)*log(n))


  #Procedimentos
  #Etapa 1: teste de Fermat nas bases 2,3,5 para rápida detecção de compostos
  if(pow(2, (n-1), n)!=1 or pow(3, (n-1), n)!=1  or pow(5, (n-1), n)!=1 ):
    return False


  #Etapa 2: detectando números de Carmichael que satisfazem o pequeno teorema de Fermat
  for b in range(2, max_mod+1, 1):
   if(gcd(n, b)>1):
    return False

   mod=(b-1)*n
   if( pow(b, n, mod)!=b):
     return False

  #Caso passe nos testes acima um primo foi encontrado
  return True


