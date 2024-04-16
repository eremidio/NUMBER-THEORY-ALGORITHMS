#VAMOS CRIAR UM PROGRAMA QUER IMPLMENTA O MÉTODO DE FATORAÇÃO DE WILLIAMS PARA INTEIROS DE 128 BITS 

'''

Nota: usaremos funções contidas na biblioteca matemática de Python para operar com valores da magnitude de 128 bits.
PARA MAIORES REFERÊNCIAS: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/williams_factorization.c

'''

#----------------------------------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
from math import gcd, factorial


#----------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

def williams_factorization_method(n:int)->int:
    '''Função que implementa o algoritmo de Williams para inteiros de 128 bits (até 10^30)'''
    
    #Variáveis locais
    A:int=2
    M:int=0
    x:int=0
    y:int=0
    factor:int=1

    #Procedimentos
    #Loop principal: A<5000000
    while(A<1000001):

        #Cálculo do fatorial de A (fator que determina a suavidade do fator primo a ser buscado)
        M=factorial(A)
        x=A    
        y=((A*A)-2)%n


        #Loop sobre os bits de A!
        while(M>1):
            if((M&1)):
                x=((x*y)-A)%n
                y=((y*y)-2)%n

            if(not (M&1)):
                y=((x*y)-A)%n
                x=((x*x)-2)%n
            
            #Bit shift
            M>>=1

        #Cálculo de um possível fator
        factor=gcd((x-2), n)
        if(factor>1 and factor<n):
            return factor

        #Atualizando variáveis para a próxima interação
        A+=1


    #Resultado em caso de falha 
    return factor



#----------------------------------------------------------------------------------------------------------------------------------------------
#PROGRAMA PRINCIPAL

#RECEBENDO INPUT DO USUÁRIO
n:int = int(input('Digite um inteiro a ser fatorado:'))


#EXECUTANDO O ALGORITMO
prime_factor:int=williams_factorization_method(n)
print("\nFatores de {} encontrados:  {} e {}".format(n, prime_factor, (n//prime_factor)))


