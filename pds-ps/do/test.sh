make

echo "Test de base"
./do --or true  true  || echo "Erreur: or true true a renvoyé false"
./do --or false false && echo "Erreur: or false false a renvoyé true"

echo "Une seule commande"
echo "and"
./do --and true
echo $? 
if [[ $? -eq 0 ]]; then
  echo "OK pour le and"
elif [[ $? -ne 0 ]]; then
  echo "NON pour le and "
fi

echo "or"
./do --or true
echo $? 
if [[ $? -eq 0 ]]; then
  echo "OK pour le or"
elif [[ $? -ne 0 ]]; then
  echo "NON pour le or "
fi

echo "####################### AND ######################"
echo "Mode and et une commande échoue"
./do --and true false true
echo $? 

echo "Mode and et toutes les commandes réussissent"
./do --and true true true
echo $? 

echo "Mode and et toutes les commandes échouent"
./do --and false false false
echo $? 


echo "####################### OR #######################"
echo "Mode or et une commande échoue"
./do --or true false true
echo $? 

echo "Mode or et toutes les commandes réussissent"
./do --or true true true
echo $? 

echo "Mode or et toutes les commandes échouent"
./do --or false false false
echo $? 

echo "####################### CC #######################"
echo "Mode and cc et une commande échoue plus vite que la terminaison des autres"
./do --and true ./wait1sec true --cc
echo $? 

echo "Mode and cc et les commandes n'échouent pas"
./do --and true ./wait1sec true --cc
echo $? 


echo "Mode or cc et une commande échoue plus vite que la terminaison des autres"
./do --or true ./wait1sec true --cc
## On considère que true et true réussissent
## mais sont plus longues à executer que true
echo $? 

echo "Mode or cc et les commandes n'échouent pas"
./do --or true true true --cc
echo $? 
