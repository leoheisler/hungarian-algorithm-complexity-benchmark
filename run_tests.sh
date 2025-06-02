mkdir -p results
csv_file="results.csv"

echo "NUM_VERTEX,NUM_EDGES,TOTAL_ITR,INSERTS,UPDATES,DELETES,TIME" > $csv_file
for arquivo in ./graphs/benchmark_graphs/*; do
  ./build/hungarian $csv_file < $arquivo
done
