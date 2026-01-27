#csvfile='power-step-merged.csv'

set datafile separator ','

set ytics nomirror

set xlabel 'Time s'
set ylabel "PWM %" 
set y2label "Laser Current mA" 

set style line 100 lt 1 lc rgb "grey" lw 0.5 
set grid ls 100

set yrange [0:100]
set y2range [0:25]

set xtics 5
set ytics 20
set y2tics 5

set style line 101 lw 1 lt rgb "#f62aa0" 
set style line 102 lw 1 lt rgb "#26dfd0" 
# set style line 103 lw 4 lt rgb "#b8ee30" 

set xtics rotate # rotate labels on the x axis
set key right center # legend placement

# Format is time, n_on, n_pwm, sum_current, n_current
plot \
  csvfile using ($1 / 100):(100 * $2 /$3) title "PWM" with lines ls 101, \
  csvfile using ($1 / 100):(25.75 / 1023 * $4 / $5) title "Laser Current" with lines axis x1y2 ls 102
