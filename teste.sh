ras=3
sapos=3
execucoes=1050
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
echo $solucoes
#calculando porcentagem de finais ideais
porcent=$(echo "scale=2; 100.0 / $execucoes" | bc)
echo $porcent
echo 'solucoes: '$solucoes
porcent_ideal=$(echo "scale=2; $porcent * solucoes" | bc)
echo $porcent_ideal

