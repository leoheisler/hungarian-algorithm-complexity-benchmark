curr_empar=1000
jump=100
final_empar=4000
prefix="graphs/benchmark_graphs/"

while [ $curr_empar -le $final_empar ]; do
  graph_name="${prefix}${curr_empar}.dat"
  ./build/graph_gen $curr_empar > "$graph_name"
  curr_empar=$((curr_empar + jump))
done
