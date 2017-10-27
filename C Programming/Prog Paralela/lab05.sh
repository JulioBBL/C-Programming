echo "let's start."

echo "omp_num_Threads set to 1"
export OMP_NUM_THREADS=1
./a.out

echo ""
echo "omp_num_Threads set to 2"
export OMP_NUM_THREADS=2
./a.out

echo ""
echo "omp_num_Threads set to 3"
export OMP_NUM_THREADS=3
./a.out

echo ""
echo "omp_num_Threads set to 4"
export OMP_NUM_THREADS=4
./a.out

echo ""
echo "omp_num_Threads set to 5"
export OMP_NUM_THREADS=5
./a.out

echo ""
echo "omp_num_Threads set to 6"
export OMP_NUM_THREADS=6
./a.out
