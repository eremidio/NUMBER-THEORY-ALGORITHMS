#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO POLLARD ρ-1 PARA FATORAR NÚMEROS INTEIROS

'''
O ALGORITMO DE POLLARD-RHO (p-1) FAZ USO DO CHAMADO PEQUENO TEOREMA DE FERMAT QUE AFIRMA QUE:
"QUE PARA QUAISQUER NÚMEROS COPRIMOS a E p, ISTO É, TAL QUE mdc(a, p) = 1, TEMOS QUE a^(p-1)≡1 (mod p)".
COMO EXEMPLO SEJAM a=2, p=3, a^(p-1)=2^(3-1)=4≡1 (mod 3).
SIMILARMENTE PARA a=4, p=7 TEMOS QUE a^(p-1)=4^(7-1)=4096≡1 (mod 7). 

SEJA n UM NÚMERO COMPOSTO, QUALQUER FATOR f NÃO TRIVIAL DE n OBEDECE AS RELAÇÕES f < n E f<n^(1/2).
SEJAM p, q DOIS NÚMEROS NO INTERVALO [0, n-1]. p≡q (mod n), APENAS NOS CASOS EM QUE p E q SÃO IDÊNTICOS.
SEJAM p E q DOIS NÚMEROS PRIMOS E SUPONHA QUE n SEJA UM PRODUTO DESTES DOIS FATORES PRIMOS.
SEJA (p-1) UM FATOR PRIMO DE UM NÚMERO l DE MODO QUE l=k(p-1), ONDE k É UM INTEIRO QUALQUER.
PELO TEOREMA DE FERMAT TEMOS QUE: a^l≡(a^(p-1))^k (mod p)≡1.
USANDO ESTES RESULTADOS OBTEMOS QUE p DIVIDE a^l, E POR SUPOSIÇÃO p É UM FATOR PRIMO DE n.
ASSIM O mdc(a^l-1, n) INCLUIRÁ p COM CERTEZA. O PROBLEMA RESIDE ENTÃO EM ENCONTRAR UM VALOR DE l ADEQUADO.


PARA MAIORES INFORMAÇÕES: 
https://en.wikipedia.org/wiki/Pollard%27s_p_−_1_algorithm

'''
#--------------------------------------------------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS USADAS
import gmpy2

#--------------------------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES USADAS NO ALGORITMO
def fill_prime_buffer(B1:int)->list:
 '''Função que preenche um buffer de números primos usados no algoritmo'''
 prime_list:list=[]#Lista de números primos

 for i in range(B1+1):
  if(gmpy2.is_prime(i)==True):
   prime_list.append(i)

 return prime_list


def fill_power_prime_buffer(B1:int, largest_prime:int, power:int, n:int)->list:
 '''Função que aloca potências da diferença de primos entre dois intervalos B1 e B2 para o estágio 2 do algoritmo de Pollard ρ-1'''

 #Variáveis locais
 current_prime:int=largest_prime
 next_prime:int=0
 prime_differenece:int=0
 prime_power_list:list=[]

 #Procedimentos: Loop principal sobre primos em um intervalo (B1, B2] com B2=100*B1
 for x in range((largest_prime+1), ((100*B1)+1), 1):
  if(gmpy2.is_prime(x)==True):

   next_prime=x
   prime_difference=(next_prime-current_prime)  
   prime_power_list.append(gmpy2.powmod(2, prime_difference, n))

    
   #Atualizando variáveis para a próxima iteração   
   current_prime=next_prime


 #Resultado
 return prime_power_list



#--------------------------------------------------------------------------------------------------------------------------------------------------------------
#ALGORITMO DE POLLARD (ρ-1)
def pollard_rho_minusone_factorization(n:int, smoothness:int)->int:
 '''Função que calcula um fator primo dado uma base de primos'''

 #Caso trivial:
 if((n%2)==0):
  return 2, (n//2)


 #Etapa 1: prenchendo um buffer de fatores primos e ajustando variáveis no algoritmo
 prime_list:list=fill_prime_buffer((smoothness+1))
 M:int=1
 factor:int=1
 power:int=0

 #Etapa2: Calculando o expoente M usado no algoritmo
 for p in prime_list:
  s = int(gmpy2.log(n)/gmpy2.log(p))
  M*=int(pow(p, s))

  #Etapa 3: Cálculo do fatores primos
  power = gmpy2.powmod(2, M, n) - 1
  factor= gmpy2.gcd(power, n)

  if(factor>1):
   return factor


 #Etapa 4: estágio 2 do algoritmo 

 #Etapa 4.1: Pré-computando uma de lista de potência da maior exponencial computada no estágio 1 do algoritmo caso um fator não tenha sido encontrado no estágio
 stage2_list:list=fill_power_prime_buffer(B1, prime_list[len(prime_list)-1], (power+1), n)
 power+=1 #Ajuste de variáveis

 #Etapa 4.2: busca por fatores primos
 for modular_prime_power in stage2_list:

  power=gmpy2.mul(power, modular_prime_power)%n

  factor= gmpy2.gcd((power-1), n)
  if(factor>1):
   print("Fator encontrado no estágio 2 do algoritmo")
   return factor

 return factor


#--------------------------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÃO PRINCIPAL
#RECEBENDO INPUT DO USUÁRIO
n:int = int(input('Digite um inteiro a ser fatorado:'))
B1:int = int(input('Digite um limite para a base de primos usados no algoritmo:'))

#EXECUTANDO O ALGORITMO
prime_factor:int=pollard_rho_minusone_factorization(n, B1)
print("Fatores de {} encotrados:  {} e {}".format(n, prime_factor, (n//prime_factor)))

 
