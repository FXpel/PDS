#! /bin/bash

echo "--------- Creation des fichiers test --------"
mkdir test
touch test/text.txt
touch test/vide

echo "fhoshsdjvwjhvoiqhefbqbvjsiuhqzbejkfbohvbdjbsvoibfiozebufhn" >> test/text.txt
echo "qhoihfsh<fpcoshcjhsdvobiwhdoisvhfshicjshvidvjbwuoufsfe<oshicdsw" >> test/text.txt
echo "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" >> test/text.txt

# création d'un gros fichier de 40 Mio environ
echo "création d'un gros fichier de 40 Mio environ "
touch test/big
dd if=/dev/urandom of=test/big bs=40072 count=1000
echo "--------------------- OK --------------------"

echo -n "Définition de la variable globale pour les tests simples ... "
MCAT_BUFSIZ=16
export MCAT_BUFSIZ
echo "ok"

echo ""


#Test sur un fichier vide
echo "---- Test: pour un fichier vide ----"
echo "cat systeme"
cat test/vide
echo "notre cat"
./mcat-scd test/vide
echo "------------------------------------"

echo ""

#Test sur un fichier avec texte
echo "---- Test: pour un fichier avec texte ----"
echo "cat systeme"
cat test/text.txt
echo "notre cat"
./mcat-scd test/text.txt
echo "------------------------------------"

echo ""

echo "------ Exécution des tests de performance, avec plusieurs tailles de buffer -------"
#On supprime s'il existe deja le fichier .dat
rm -f mcat-tm.dat && echo "#buffsize real user sys" > mcat-tm.dat

for size in `awk 'BEGIN { for( i=1; i<=40072; i*=2 ) print i }'`;
do
    export MCAT_BUFSIZ=$size
    echo -n "Test pour un buffer de $MCAT_BUFSIZ octets ... "
    /usr/bin/time -f "$MCAT_BUFSIZ %e %U %S" ./mcat-scd test/big > /dev/null 2>> mcat-tm.dat
    echo "ok"
done






echo -n "Génération du graph ... "
gnuplot mcat.gp
echo ""
echo "--------------------------------------- OK -----------------------------------------"

echo ""

#echo "---------------------------"
#echo "Suppression du dossier test et du mcat-tm.dat"
#rm -r test
#rm mcat-tm.dat
#echo "----------- OK ------------"
