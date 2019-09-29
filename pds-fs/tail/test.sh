#! /bin/bash


echo "Création et remplissage du dossier de test ... "
mkdir test
touch test/number_1_20


for  i in `seq 1 20`;
 do
  echo $i >> test/number_1_20
done


echo "----- Liste des éléments du dossier de test -----"
ls -lR test
echo "-------------------------------------------------"
echo ""


#Test tail sans paramètres
echo "----------------------------------"
echo "tail systeme normale (sans paramètre)";
tail test/number_1_20  >> test1.txt
echo "----------------------------------"
echo "notre tail (sans paramètre)"
./mtail test/number_1_20  >> test2.txt
echo "----------------------------------"
diff test1.txt test2.txt > /dev/null
if [[ $? -eq 0 ]]; then
  echo "OK sans paramètres"
elif [[ $? -ne 0 ]]; then
  echo "NOK"
fi

echo ""

#Test tail avec paramètres
echo "----------------------------------"
echo "tail systeme, argument -n 5";
tail test/number_1_20 -n 5 >> test3.txt
echo "----------------------------------"
echo "notre tail, argument -n 5"
./mtail test/number_1_20 -n 5 >> test4.txt
echo "----------------------------------"
diff test3.txt test4.txt > /dev/null
if [[ $? -eq 0 ]]; then
  echo "OK avec paramètres"
elif [[ $? -ne 0 ]]; then
  echo "NOK"
fi

echo ""

#Test tail 0 ligne
echo "----------------------------------"
echo "tail systeme -n 0";
tail test/number_1_20 -n 0 >> test5.txt
echo "----------------------------------"
echo "notre tail, argument -n 0"
./mtail test/number_1_20 -n 0 >> test6.txt
echo "----------------------------------"
diff test5.txt test6.txt > /dev/null
if [[ $? -eq 0 ]]; then
  echo "OK pour 0"
elif [[ $? -ne 0 ]]; then
  echo "NOK"
fi


echo ""

#Test tail nombre de ligne < 0
echo "----------------------------------"
echo "tail systeme -n -10";
tail test/number_1_20 -n -10 >> test7.txt
echo "----------------------------------"
echo "notre tail, argument -n -10"
./mtail test/number_1_20 -n -10 >> test8.txt
echo "----------------------------------"
diff test7.txt test8.txt > /dev/null
if [[ $? -eq 0 ]]; then
  echo "OK pour < 0"
elif [[ $? -ne 0 ]]; then
  echo "NOK"
fi

echo "Fin du test"
