set title "Time"
set xlabel "n^{th} number"
set ylabel "measure(ns)"
set terminal png font " Times_New_Roman,12 "
set output "time.png"
set xtics 0 ,20 ,500

plot \
"final" using :1 with linespoints linewidth 2 title "kernel space", \
"final" using :2 with linespoints linewidth 2 title "user space", \
"final" using :3 with linespoints linewidth 2 title "kerenl to user", \