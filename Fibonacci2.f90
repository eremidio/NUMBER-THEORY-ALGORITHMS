!UM PROPGRAMA SIMPLES PÁRA SE CALCULAR O ENÉSIMO TERMO DA SEQUÊNCIA DE FIBONACCI EM FORTRAN
program Fibonacci2
implicit none

integer::n1, fib
write(*,*) "Qual o valor de n?"
read(*,*)n1

write(*,*) "O número que ocupa a posição número", n1, "na sequência de Fibonacci é", fib(n1-1),"."
end program Fibonacci2

recursive function fib(n) result(f)
implicit none
!Resultado da função
integer::f
!variáveis
integer, intent(in)::n


select case(n)
case(0:1)
f=1
case(2:)
f=fib(n-2)+fib(n-1)
end select

endfunction fib
