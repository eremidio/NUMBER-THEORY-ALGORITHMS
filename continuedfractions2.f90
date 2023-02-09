!Vamos escrever um programa que é capaz de calcular a expansão em frações continuadas de um número qualquer
!Quatro casos serão de interesse: número de euler, pi, raízesquadradas e números racionais

program continuedfractions2
implicit none
!****************
!Definição de variáveis
real(kind=kind(1.0d0))::valor, parte_decimal, radicando, fracao
real(kind=kind(1.0d0)), parameter::pi=4.0d0*atan(1.0d0)
real(kind=kind(1.0d0)), parameter::euler=exp(1.0)
integer::parte_inteira, parte_inteira2, resto, denominador, denominador_temp, numerador
integer:: i, contador, escolha

!****************
!Explicação do programa
write(*,*)"Este programa determina os coeficientes de expansão em frações parciais de número qualquer."
write(*,*)"Dado um número real qualquer r e uma seqûencia de inteiros a(0), a(1),a(2), ... ."
write(*,*)"Sua expansão em frações continuada denotada também por r=[a(0); a(1), a(2), ...] é"
write(*,*)"r=a(0)+____1____"
write(*,*)"        a(1)+____1____  "
write(*,*)"              a(2)+____1___     "
write(*,*)"                    a(3)+ ___1____   "
write(*,*)"                             ... "
write(*,*)""
write(*,*)""

!****************
!Entrada manual de dados
write(*,*)"Digite '1' para determinar os coeficientes da expansão em frações continuada de pi."
write(*,*)"Digite '2' para determinar os coeficientes da expansão em frações continuada do Número de Euler."
write(*,*)"Digite '3' para determinar os coeficientes da expansão em frações continuada de uma raíz quadrada não exata."
write(*,*)"Digite '4' para determinar os coeficientes da expansão em frações continuada de um número racional a/b."

read(*,*) escolha

if(escolha==1) then
valor=pi
else if (escolha==2) then
valor=euler
else if (escolha==3) then
write(*,*)"Digite o valor do radicando:"
read(*,*)radicando
valor=sqrt(radicando)
else if (escolha==4) then
write(*,*)"Digite o denominador da fração correspondendo ao número racional(a/b):"
read(*,*)denominador
write(*,*)"Digite o numerador da fração correspondendo ao número racional(a/b, um valor diferente de 0):"
read(*,*)numerador
end if

if(escolha<4) then
write(*,*)"Quantos coeficientes você deseja calcular na sua expressão em frações continuadas"
read(*,*)contador
end if

!****************
!Determinando os coeficientes da expansão em fração continuada e exibindo o resultado na tela
!Casos 1, 2, 3 possuem uma expansão em fração continuada com um número infinito de termos
!Caso 4 possui uma expansão em fração continuada com um número finito de termos

write(*,*)"Eis os coeficientes da expansão em frações continuadas:"

if(escolha<4) then

i=1
parte_inteira=floor(valor)
write(*,*)parte_inteira 
parte_decimal=valor-parte_inteira


do while(i<contador)
i=i+1
parte_inteira=floor(1.0d0/parte_decimal)
write(*,*)parte_inteira
parte_decimal=(1.0d0/parte_decimal)-parte_inteira
end do

end if

if(escolha==4) then


parte_inteira=2
do while(parte_inteira>0)


parte_inteira2 = mod(denominador, numerador)
denominador_temp = denominador-parte_inteira2
parte_inteira=denominador_temp/numerador

write(*,*)parte_inteira

denominador=numerador
numerador=parte_inteira2
if(numerador==0) then
exit
end if

end do

end if





end program continuedfractions2

