################################################################################
#                                IME-USP (2018)                                #
#            MAC0219 - Programacao Concorrente e Paralela - MiniEP2            #
#                                                                              #
#                                    Testes                                    #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

ras=2
sapos=2
execucoes=105
solucoes=0
resposta=4
comando='./miniep2 '$ras' '$sapos
#echo $comando
contador=0
while [ $contador -lt $execucoes ]; do
	#resposta=(eval $comando)
	eval $comando
	resposta=$?
	let solucoes=solucoes+resposta
	let contador=contador+1
done
echo 'rodando o mini-ep2 com '$ras' ras e '$sapos' sapos'
echo 'numero de execucoes: '$execucoes
#calculando porcentagem de finais ideais (solucionou)
echo 'vezes que chegou no final ideal: '$solucoes
porcent=$(echo "scale=5; 100.0 / $execucoes" | bc)
echo 'peso percentual de cada execucao: '$porcent'%'
porcent_ideal=$(echo "scale=5; $porcent * $solucoes" | bc)
echo 'porcentagem de vezes no final ideal: '$porcent_ideal'%'

################################################################################
