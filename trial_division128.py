#VAMOS CRIAR UM PROGRAMA  QUE IMPLMENTA  O ALGORITMO DE DIVISÃO POR TENTATIVA E ERRO PARA CALCULA FATORES PRIMOS DE UM INTEIRO DE 128 BITS


#IMPORTANDO BIBLIOTECAS
from math import sqrt

 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES 

def miller_rabin128(n:int)->bool:
 '''Função que implementa o teste de Miller-Rabin para inteiros até 10^25, será usado como subrotina no algoritmo principal'''

 #Variáveis locais
 prime_seed:int = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]
 n_even:int = (n-1)
 s:int = 0
 d:int=0
 is_prime = False

 #Procedimentos
 #Caso base:
 if(n<2):
  return False
 
 #Testes com primos inferiores a 100
 for prime in prime_seed:
  if(n == prime):
   return True
  if((n%prime)==0):
   return False



 #Cálculo dos parâmetros s e d usados no algoritmo  
 while((n_even%2) == 0):
  n_even //= 2
  s += 1
 d = n_even


 #Loop principal usando a base de primos 
 for a in prime_seed:
  if(a>=n):
   break

  x:int =pow(a, d, n)
  if(x == 1 or x == n - 1):
   continue 

  for i in range(s - 1):

   x = pow(x, 2, n)
   if(x == n-1):
    is_prime = True
    break

  if(is_prime==False):
   return False

 return True




def trial_division(n:int)->list:
    '''Função que implementa o algoritmo da tentativa de divisão para fatorar números inteiros'''
    #Variáveis locais
    primes210:list=[2,3,5,7]
    prime_seed:list=[1,11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139, 143, 149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209]
    root:int=int(sqrt(n))
    prime_factors:list=[]
    divisor:int=0

    #Procedimentos
    #Teste por fatores 2,3,5,7
    for  small_primes in primes210:
        if((n%small_primes)==0):
          prime_factors.append(small_primes)
          while((n%small_primes)==0):
              n//=small_primes

    if(miller_rabin128(n)==True):
        prime_factors.append(n)
        return prime_factors

    #Loop principal com otimização 210k+r
    for x in range(n):

        if(divisor>root or n==1):
            break

        for prime in prime_seed:
            divisor=210*x+prime

            if((n%divisor)==0 and divisor>1):
                prime_factors.append(divisor)
                while((n%divisor)==0):
                    n//=divisor
                if(miller_rabin128(n)==True):
                    prime_factors.append(n)
                    return prime_factors

                    
    #Fatores superiores a n^(1/2)
    if(n>1):
        prime_factors.append(n)
        
    #Resultado           
    return prime_factors


#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#PROGRAMA PRINCIPAL

#Recebendo input do usuário
n:int=int(input('Digite um inteiro: '))

#Excutando o algoritmo de tentativa por divisão e erro
prime_factor_list:list=trial_division(n)

#Exibindo o resultado da execução do algoritmo
print('Eis os fatores primos de ', n, '=', prime_factor_list)

if(len(prime_factor_list)==1):
    print(n, 'é primo.')
