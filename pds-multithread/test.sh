#!/bin/bash

make realclean;
make;

echo "--- Préparation des fichiers pour compteur-gc ---"
for size in `awk 'BEGIN { for( i=1000; i<=1000000; i*=10 ) print i }'`; do
	echo "$size octets :"
	./aleazard $size > $size.adn
	echo " ok"
done
echo -n "" > resultat.dat
echo "-------------------------------------------------"



echo "-------------- Test de compteur-gc --------------"
for size in `awk 'BEGIN { for( i=1000; i<=1000000; i*=10 ) print i }'`; do
	echo -n "Pour $size octets ..."
    for nthread in `awk 'BEGIN { for( i=1; i<=64; i*=2 ) print i }'`; do
		echo -n "$size $nthread " >> resultat.dat
		echo -n " $nthread"
		ntest=2
		sum=0
		for i in `awk 'BEGIN { for( i=1; i<=2; i++ ) print i }'`; do
			result_time=`./compteur-gc $size.adn $nthread `
			sum=`echo $sum + $result_time | bc -l`
		done

		echo "$sum / $ntest" | bc -l >> resultat.dat
    done
    echo " ok"
done


echo -n "Affichage du graphe ... "
echo -n "Si vous possedez un logiciel permettant de traiter des graphes de maniere interactive, veuillez decommenté les deux derniere ligne du fichier run.gnu"
gnuplot -persist run.gnu
echo ""
echo "ok"

echo "-------------------------------------------------"



echo -n "Nettoyage des fichiers de tests pour compteur-gc ..."
rm *.adn
echo " ok"
