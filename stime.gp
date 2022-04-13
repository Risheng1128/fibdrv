# 畫出有經過統計的圖
set title "Time"
set xlabel "n^{th} number"
set ylabel "measure(ns)"
set terminal png font " Times_New_Roman,12 "
set output "single.png"
set xtics 0 ,100 ,1000

plot \
"out" using :1 with linespoints linewidth 2 title "user space", \
"out" using :2 with linespoints linewidth 2 title "kernel space", \
"out" using :3 with linespoints linewidth 2 title "kerenl to user", \