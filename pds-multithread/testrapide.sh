#! /bin/bash

make realclean;
make ;




# création d'un petit fichier de  Mio environ
echo "création d'un gros fichier de 256 Mo environ "
dd if=/dev/urandom of=test.txt  bs=1048576 count=128
echo "--------------------- OK --------------------"

echo "Test du tri rapide "
for i in `seq 1 20`; do
  ./tri-rapide -cvn $i test.txt
  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi
done


echo "Test du tri rapide pour le format texte "
for i in `seq 1 20`; do

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre0.txt

  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre1.txt

  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre2.txt
  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre3.txt

  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre4.txt

  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

  ./tri-rapide -cavt -l 6 -n $i nombre/nombre5.txt

  if [[ $? -eq 0 ]]; then
    echo ""
    echo "OK pour "$i" threads"
  elif [[ $? -ne 0 ]]; then
    echo "pas bon pour"$i" threads"
  fi

done

echo -n "Nettoyage des fichiers de tests pour le tri rapide ..."
rm -rf test.txt
echo " ok"
