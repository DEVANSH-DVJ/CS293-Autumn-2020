g++ testcases.cpp -o testcases
g++ -O2 190100044_2.cpp -o 190100044_2
g++ check.cpp -o check

for i in {0..10}; do
    ./testcases >input
    time ./190100044_2 <input >output
    ./check input output
done
