#!/bin/bash

make mdu;
mkdir test
cd test 
dd if=/dev/zero of=text.txt bs=1k count=1k >/dev/null 2>&1
ln -s text.txt lien
cd ..

echo '#commande originale' &>>mdu_log.txt

du -B 512 -L mdu.c &>> mdu_log.txt

echo '#commande mdu' &>> mdu_log.txt

./mdu -L mdu.c &>> mdu_log.txt

echo '#commande originale avec option -b' &>>mdu_log.txt

du -b mdu.c &>> mdu_log.txt

echo '#commande mdu avec option -b ' &>>mdu_log.txt

./mdu -b mdu.c &>> mdu_log.txt


echo "test egalité"
./mdu test/ >> resmdu.txt
du -B512 test/ >> resdu.txt
diff resdu.txt resmdu.txt


#les commandes sont bien identiques
