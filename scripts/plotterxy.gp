#csvfile='power-step-merged.csv'

set datafile separator ','

set ytics nomirror
unset y2tics
unset y2label

set xlabel "PWM %" 
set ylabel "Laser Current mA" 

set style line 100 lt 1 lc rgb "grey" lw 0.5 
set grid ls 100

set xrange [0:100]
set yrange [0:25]

set xtics 20
set ytics 5

set xtics rotate # rotate labels on the x axis

# Format is time, n_on, n_pwm, sum_current, n_current
plot \
  csvfile using (100 * $2 /$3):(48.1 / 1023 * $4 / $5) with points pointtype 1 notitle
