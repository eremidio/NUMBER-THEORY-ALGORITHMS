!Vamos escrever um programa para calcular frações contínuadas em Fortran 95
program continuedfractions
implicit none
!Definição de variáveis
integer, dimension(:), allocatable::a
real(kind=kind(1.0d0)), dimension(:), allocatable::parcial
real(kind=kind(1.0d0)):: resultado
integer::n, i, j

!****************
!Explicação do programa
write(*,*)"Este programa retorna um número real a partir de sua expansão em fração continuada."
write(*,*)"Dado um número real qualquer r e uma seqûencia de inteiros a(0), a(1),a(2), ... ."
write(*,*)"Sua expansão em frações continuada denotada também por r=[a(0); a(1), a(2), ...] é"
write(*,*)"r=a(0)+____1____"
write(*,*)"        a(1)+____1____  "
write(*,*)"              a(2)+____1___     "
write(*,*)"                    a(3)+ ___1____   "
write(*,*)"                             ... "
write(*,*)""
write(*,*)""

!Definindo um array de coeficientes
write(*,*)"Quantos termos você vai utilizar no cálculo de sua fração continuada?"
read(*,*)n

allocate(a(n), parcial(n-1)) !Alocação de memória dinâmica
 do i=1,n,1
 write(*,*)"Digite o valor de a(",i,"):"
 read(*,*)a(i)
 end do

!Calculando a soma da fração parcial
parcial(1)=real(a(n-1)+(1.0d0/(a(n)+ 1.0d0)))

 do j =2, n-1, 1
  parcial(j)=real(a(n-j))+(1.0d0/(parcial(j-1)))

 end do

resultado=parcial(n-1)

!Exibindo o resultado final

write(*,*)"O resultado da soma parcial de sua fração continuada para", n, "termos é", resultado
deallocate(a, parcial)
              
end program continuedfractions


