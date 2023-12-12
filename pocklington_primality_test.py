#VAMOS CRIAR UM ARQUIVO, QUE CONTÉM O ALGORITMO DE POCKLINGTON PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO

#EXPLICAÇÃO DO ALGORITMO
'''
O TESTE DE PRIMALIDADE DE POCKLINGTON É UM DOS TESTES DE PRIMALIDADE MAIS EFICIENTES QUE EXISTEM SE COMBINADO COM UM EFICIENTE MÉTODO DE FATORAÇÃO DE NÚMEROS
INTEIROS.

ESTE MÉTODO BASEIA-SE NO SEGUINTE TEOREMA:
SEJA n UM NÚMERO INTEIRO TAL QUE (n-1)=a.b, COM a > n^(1/2) E mmc(a, b) = 1. SE PARA CADA FATOR PRIMO p DE a EXISTIR UM x TAL QUE mmc(x^[(n-1)/p], n)=1 E 
x^(n-1) = 1 (mod n) ENTÃO n É PRIMO.

ESTE É UM ALGORITMO QUE SE BASEIA NA ORDEM DE UM GRUPO PARA TESTAR A PRIMALIDADE DE UM INTEIRO E UMA VARIANTE DA SEGUINTE PROPOSIÇÃO GERAL:
DADO UM INTEIRO n E DOIS INTEIROS a, s,  TAL QUE a^s=1 (mod n) E PARA CADA DIVISOR PRIMO p DE s a^(s/p) ≠ 1 (mod n); SE s>n^(1/2) ENTÃO n É PRIMO. 

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pocklington_primality_test

'''
#IMPORTANDO BIBLIOTECAS
import math


#FUNÇÕES AUXILIARES

#Função que implementa o algoritmo de Euclides
def euclides_algorithm(a:int, b:int)->int:
 '''Algoritmo de Euclides'''
 remainder:int=1
 while(remainder>0):
  remainder=(a%b)
  a=b
  b=remainder

 #Resultado
 return a


'''TESTE USE UM # APÓS O MESMO'''
#print(euclides_algorithm(1446545613132100, 2654651132132133125))

#Função que implementa a exponenciação binária
def bin_pow(a:int, b:int)->int:
 '''Exponenciação binária''' 
 result:int=1

 while(b>0):#Loop principal
  if((b&1)):
   result*=a
  
  a*=a #Atualizando variável
  b>>=1 #Atualizando variável
  
 return result

#Função que implementa a exponenciação binária modular
def mod_bin_pow(a:int, b:int, m:int)->int:
 '''Exponenciação binária''' 
 result:int=1

 while(b>0):#Loop principal
  if((b&1)):
   result=((result%m)*(a%m))%m
  
  a=((a%m)*(a%m))%m #Atualizando variável
  b>>=1 #Atualizando variável
  
 return result

'''TESTE USE UM # APÓS O MESMO'''
#print(bin_pow(11, 3500))
#print(mod_bin_pow(11, 3500, 3))


#Função que fatora um número inteiro e aloca fatores não respetidos em um array usaremos tentativa por divisão com otimização 6k+1
def extract_prime_factors(n:int)->list:
 '''Função que fatora um número inteiro e aloca seus fatores primos em um array'''
 #Variáveis locais
 divisors:list=[1, 7, 11, 13, 17, 19, 23, 29]
 factors:list=[]#Lista de fatores primos

 #Cálculos de fatores 2, 3, 5
 if((n%2)==0):
  factors.append(2)
  while((n%2)==0):
   n//=2

 if((n%3)==0):
  factors.append(3)
  while((n%3)==0):
   n//=3

 if((n%5)==0):
  factors.append(5)
  while((n%5)==0):
   n//=5

 #Fim do algoritmo
 if(n==1):
  factors = factors
  return factors

 #Loop principal
 #1ª iteração
 for i in range(1,8,1):
  if((n%divisors[i])==0):
   factors.append(divisors[i])
   n//=divisors[i]
   while((n%divisors[i])==0):
    n//=divisors[i]

 #Fim do algoritmo
 if(n==1):
  factors = factors
  return factors

 #Demais iterações
 root:int=int(math.sqrt(n))

 while(divisors[0]<root):
  #Atualizando a lista de possíveis divisores
  new_divisors:list=[x+30 for x in divisors]
  divisors=new_divisors

  #Teste de divisibilidade pelos elementos da lista
  for i in range(8):
   if((n%divisors[i])==0):
    factors.append(divisors[i])
    n//=divisors[i]
   while((n%divisors[i])==0):
    n//=divisors[i]

  #Fim do algoritmo
  if(n==1):
   factors = factors
   return factors

 #Fatores superiores a raiz quadrada do número a ser fatorado
 if(n>1):
  factors.append(n)
  factors = factors
 return factors

'''TESTE USE UM # APÓS O MESMO'''
#print(extract_prime_factors(654654132132132))
#print(extract_prime_factors(6546541321321327897902))


#Função que reduz um inteiro a ser fatorado a um valor maior do que sua raíz quadrada
def reduce_number(n:int):
 '''Função que reduz um inteiro a ser fatorado'''

 #Redução por fatores primos inferiores a 1000 usando o algoritmo de Euclides para números superiores a 10^7
 common_factor_list:list=[2305567963945518424753102147331756070, 3383080509296917481189798760796480670771162183, 262025664754470334382813071883984477441, 49766523393936228750138598082752980119549, 1227453540237014997887615651109181957903188941, 253056306993037840092244562196981381959, 879031892818978804933065306274691112009314693, 16866467815653776127243907167629319108817, 83623435734606723958852552002152901629917681, 500139990716305530696933027389294139003181]
 if(n>1e7):
  for count in range(101):
   for x in common_factor_list:
    common_reducer:int=euclides_algorithm(x, n)
    if(common_reducer>1):
     n//=common_reducer

 #Variáveis locais
 limit:int=int(math.sqrt(n))
 limit2:int=int(math.sqrt(limit))
 current_value:int=int(n)

 #Loop principal com otimização 6k+1
 if(n>1e16):
  for y in range(1001, (limit2+1), 6):
   while((n%y)==0):
    n//=y
   while((n%(y+2))==0):
    n//=(y+2)
 else:
  for y in range(1001, (limit+1), 6):
   while((n%y)==0):
    n//=y
   while((n%(y+2))==0):
    n//=(y+2)

 #Resultado
 return n


'''TESTE USE UM # APÓS O MESMO'''
#print(reduce_number(21231321321328798465165165))
#print(reduce_number(9877987441698798766546163513213213))


#Função que determina um certficado de primalidade para um dado fator primo
def find_certificate(n:int, prime_factor:int)->int:
 '''Função que determina um certificado de primaliadade para um número inteiro'''
 #Variáveis locais
 exponent:int=(n-1)
 exponent2:int=(exponent//prime_factor)
 found:bool==false
 tester_list:list=[2, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255, 257, 259, 261, 263, 265, 267, 269, 271, 273, 275, 277, 279, 281, 283, 285, 287, 289, 291, 293, 295, 297, 299, 301, 303, 305, 307, 309, 311, 313, 315, 317, 319, 321, 323, 325, 327, 329, 331, 333, 335, 337, 339, 341, 343, 345, 347, 349, 351, 353, 355, 357, 359, 361, 363, 365, 367, 369, 371, 373, 375, 377, 379, 381, 383, 385, 387, 389, 391, 393, 395, 397, 399, 401, 403, 405, 407, 409, 411, 413, 415, 417, 419, 421, 423, 425, 427, 429, 431, 433, 435, 437, 439, 441, 443, 445, 447, 449, 451, 453, 455, 457, 459, 461, 463, 465, 467, 469, 471, 473, 475, 477, 479, 481, 483, 485, 487, 489, 491, 493, 495, 497, 499, 501, 503, 505, 507, 509, 511, 513, 515, 517, 519, 521, 523, 525, 527, 529, 531, 533, 535, 537, 539, 541, 543, 545, 547, 549, 551, 553, 555, 557, 559, 561, 563, 565, 567, 569, 571, 573, 575, 577, 579, 581, 583, 585, 587, 589, 591, 593, 595, 597, 599, 601, 603, 605, 607, 609, 611, 613, 615, 617, 619, 621, 623, 625, 627, 629, 631, 633, 635, 637, 639, 641, 643, 645, 647, 649, 651, 653, 655, 657, 659, 661, 663, 665, 667, 669, 671, 673, 675, 677, 679, 681, 683, 685, 687, 689, 691, 693, 695, 697, 699, 701, 703, 705, 707, 709, 711, 713, 715, 717, 719, 721, 723, 725, 727, 729, 731, 733, 735, 737, 739, 741, 743, 745, 747, 749, 751, 753, 755, 757, 759, 761, 763, 765, 767, 769, 771, 773, 775, 777, 779, 781, 783, 785, 787, 789, 791, 793, 795, 797, 799, 801, 803, 805, 807, 809, 811, 813, 815, 817, 819, 821, 823, 825, 827, 829, 831, 833, 835, 837, 839, 841, 843, 845, 847, 849, 851, 853, 855, 857, 859, 861, 863, 865, 867, 869, 871, 873, 875, 877, 879, 881, 883, 885, 887, 889, 891, 893, 895, 897, 899, 901, 903, 905, 907, 909, 911, 913, 915, 917, 919, 921, 923, 925, 927, 929, 931, 933, 935, 937, 939, 941, 943, 945, 947, 949, 951, 953, 955, 957, 959, 961, 963, 965, 967, 969, 971, 973, 975, 977, 979, 981, 983, 985, 987, 989, 991, 993, 995, 997, 999]

 #Busca por candidatos primos inferiores a 10000
 for i in tester_list:
  if(mod_bin_pow(i, exponent, n)==1 and euclides_algorithm((bin_pow(i, exponent2)-1), n)==1):
   return i

 #Caso de Falha
 return 0
 
#Função que implementa o teste de primalidade de Pocklington-Lehmers
def pocklington_primality_test(n:int)->bool:
 '''Função que implementa o teste de primalidade de Pocklington'''
 #Etapa 1: calculando algum fator de (n-1)> n^(1/2)
 a_factor:int=reduce_number((n-1))

 #Etapa 2: fatorando o fator encontrado na etapa anterior:
 prime_list:list=extract_prime_factors(a_factor)

 #Etapa 3: calculando certficados de primalidade para os fatores primos encontrados na etapa anterior
 certifier_list:list=[]

 for prime in prime_list:
  certifier:int=find_certificate(n, prime)
  if(certifier==0):
   print("Teste inconclusivo!\n")
   return False
  else:
   certifier_list.append(certifier)

 certifier_list=certifier_list


 #Etapa 4: gerando certificado de primalidade e exibindo resultado caso algum primo seja encontrado
 certificate=zip(certifier_list, prime_list)
 print('Número primo encontrado!\nCertificado de primalidade:')
 print(set(certificate))
 return True
