--VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA PENEIRA DE ESRATÓSTENES SEGMENTADA EM LUA


--###########################################################################################################################################
--PARTE 1: PENEIRA DE ERATÓSTENES BÁSICA PARA COMPUTAR PRIMOS ATÉ A RAÍZ QUADRADA DO LIMITE 

function basic_eratosthenes_sieve(limit)

 --Variáveis locais
 local root=math.floor(math.sqrt(limit))
 local number_table={}
 local prime_table={}
 local prime_index=1
 local n=0
 local current_prime=2


 --Procedimentos
 --Inicializando o array de números inteiros
 for i = 1, root, 1 do
  number_table[i]=i 
 end

 --Descartando números menores que 2
 number_table[0]=nil
 number_table[1]=nil


 --Loop principal
 while((current_prime*current_prime)<=root) do

  --Eliminando múltiplos de primos do conjunto
  for x=(current_prime*current_prime), root, current_prime do
   number_table[x]=nil
  end

  --Computando o próximo número primo da lista
  for y=(current_prime+1), root, 1 do
   if (number_table[y] ~= nil) then
    current_prime=y
    break
   end

  end

 end


 --Resgistrando os números primos encontrados
 for j = 1, root, 1 do

  if(number_table[j] ~= nil) then
   prime_table[prime_index]=number_table[j]
   prime_index=prime_index+1
  end

 end

--Resultado
return prime_table

end

--###########################################################################################################################################
--PARTE 2: PENEIRA SEGMENTADA ALGORITMO PRINCIPAL

function segmented_sieve(limit, sieve_size)
 -- Caso trivial: limit<30
 local prime_seed = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}

 if limit <= 30 then
  for i = 1, 10, 1 do
   if prime_seed[i] < limit then
    io.write(prime_seed[i] .. ", ")
   end   
  end

  io.write("...\n")
  return
 end

 -- Variáveis locais
 local prime_root_table = basic_eratosthenes_sieve(limit)
 local max_root = 0
 local element = prime_root_table[#prime_root_table]+1
 local tester=0
 local minimum=0

 
 --Procedimento
 --1: Printando os primos gerados até a raíz quadrada do limite
 for _, prime in ipairs(prime_root_table) do
  io.write(prime..", " )
 end


 --2: Loop principal
 while(element<limit) do


  --2.1: gerando o intervalo de segmentação
  local segmentation_interval={}

  for i=1, sieve_size, 1 do

   segmentation_interval[i]=element
   element=element+1
   if(element>limit) then
    break
   end

  end

  max_root=math.floor(math.sqrt(segmentation_interval[#segmentation_interval]))


  --2.2: Peneira no intervalo de segmentação
  for j =1, #prime_root_table, 1 do

   --Checando se a peneira no seguimento atual está completa
   if(prime_root_table[j]>max_root) then
    break
   end

   --Loop sobre o intervalo de segmentação
   for k=1, #segmentation_interval, 1 do
    if(segmentation_interval[k]%prime_root_table[j]==0) then
     segmentation_interval[k]=0
    end
   end

  end


  --2.3: printando os primos em um intervalo de segmentação
  for _, primes in ipairs(segmentation_interval) do
   if(primes>0) then
    io.write(primes..", " )
   end
  end
  
 end--Fim do loop principal


io.write("...\n")--Fim da função que computa peneira segmentada
end


--###########################################################################################################################################
--PROGRAMA PRINCIPAL

--Recebendo input do usuário
io.write("Limitante superior para sua sequência de primos: ") 
local m_limit=io.read("*n")

io.write("Intervalo de segmentação: ") 
local m_sieve_size=io.read("*n")

--Computando números primos usando a peneira de Eratóstenes segmentada
segmented_sieve(m_limit, m_sieve_size)

