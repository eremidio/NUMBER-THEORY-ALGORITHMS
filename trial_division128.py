#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE DIVISÃO POR TENTATIVA E ERRO PARA CALCULA FATORES PRIMOS DE UM INTEIRO DE 128 BITS



#IMPORTANDO BIBLIOTECAS
from math import sqrt

 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES PROGRAMA PRINCIPAL

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

