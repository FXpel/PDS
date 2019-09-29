set title "Temps et vitesse d'execution"
set logscale x
set xlabel "taille en lignes"
set logscale y
set ylabel "temps en s ou vitesse en octets/s"
set style data linespoints
plot "mcat-tm.dat" using 1:2 title "temps", \
     "mcat-tm.dat" using 1:3 title "vitesse"
pause -1  "Hit return to continue"