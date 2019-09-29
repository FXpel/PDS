make multif;
make race;
make exo8;




echo "------------------ Testmultif ------------------"
echo "avec un argument: le résultat est 0"
./multif true
echo "avec un argument: le résultat est 1"
./multif false
echo "avec deux arguments: le résultat est 0"
./multif true true
echo "avec deux arguments: le résultat est 1"
./multif true false
echo "------------------------------------------------"

echo ""

echo "------------------ Testrace --------------------"
for i in `seq 1 4`;
do
  echo "Course n° $i: "
  echo "Resultat:"
  ./race
  echo ""
done
echo "------------------------------------------------"


echo ""

echo "Observation de processus"
echo "Q2: "
echo " Utilisez la commande kill pour terminer les processus fils. > les fils ne sont plus excecuter."
echo "Que se passe-t-il si vous tuez le processus père ? > Les processus fils sont récuperer par le père du père et sont toujour en exécution."
