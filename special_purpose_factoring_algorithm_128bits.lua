--VAMOS ESCREVER  UM PROGRAMA PARA FATORAR INTEIROS SEMIPRIMOS DE 128 BITS EM LUA

--[[
O PRESENTE PROGRAMA IMPLEMENTA UM ALGORITMO SIMPLES DESCRITO NO SEGUINTE ARTIGO: https://dl.acm.org/doi/10.1145/2393216.2393246
UMA VERSÃO PARA INTEIROS DE 64-BITS ESTÁ DISPONÍVEL NESTE REPOSITÓRIO ESCRITO EM C.
--]]



--FUNÇÕES

--Função que decompõe ukm número semiprimo em dois fatores primos quando onúmero em questão possui fatores de mesma ordem de grandeza
function special_purpose_factorization(N)

 --Variáveis locais
 local n=math.floor(math.sqrt(N)) --Step2.1
 local iteration=1

 local p=0
 local q=0
 local n0=0
 local q0=0
 local r0=0
 local n1=0
 local q1=0
 local r1=0
 local nk=0
 local qk=0
 local rk=0
 local d=0
 local k=0

 --Procedimentos

 --1: Ajuste inicial de variáveis (steps 2.2, 2.3)
 q0=math.floor(N/n)
 r0=(N%n)
 n0=n


 --2: Loop principal
 print("Iteração    Divisor    Quociente   Resto\n-------------------------------------------------------------\n")

 while(true) do
  print(iteration.." " .. n0 .." ".. q0 .." ".. r0)
  iteration=iteration+1

  --2.4: Condições que determinam o fim da execução do algoritmo
  if(r0==0) then
   p=n0
   q=q0
   break
  end

  if(r0==q0) then
   p=n0+1
   q=q0
   break
  end

 
  
  while(true) do --Loop secundário
   if(r0>q0) then --2.5: Reajuste no valor das variáveis
    n0=n0+math.floor(r0/q0);
    r0=r0 -(math.floor(r0/q0)*q0);
    q0=q0;
   end

   --2.6: Cálculo dos possíveis divisores de N
   if(r0<q0) then
    n1=(n0+1)
    q1=(q0-1)
    r1=(n0-q0+r0+1)
   end 

   --Step2.7:
   if(q1<=r1) then
    r0=r1-q1
    q0=q1
    n0=n0+1
   else
    break
   end

  end --FIM do loop secundário

  -- Step2.8:
  d=r1-r0
  k=math.ceil( (d/(-2)) +((math.sqrt((d*d)+(4*(d+q0-r1))))/2) )


  --Step2.9:
  rk=r1+((k-1)*(d+k))
  nk=n0+k
  qk=q0-k

  --Step2.10: Atualizando variáveis para a próxima iteração
  n0=nk+1
  q0=qk
  r0=rk-qk
  

 end --FIM do loop principal

 --Resultado da execução do algoritmo
 print("------------------------------------------------------------\n")
 print("Fatores de ".. N.." encontrados: ".. p ..", ".. q)


end --FIM DA FUNÇÃO special_purpose_factorization




--PROGRAMA PRINCIPAL

--Recebendo input do usuário
io.write("Digite um número inteiro que será fatorado: ")

local number=io.read("*n")


--Executando o algoritmo
special_purpose_factorization(number)



