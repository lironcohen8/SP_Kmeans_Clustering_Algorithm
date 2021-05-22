echo python test1 started
time python3 kmeans.py 3 600 < tests/input_1.txt > my_output1py.txt
diff -s my_output1py.txt tests/output_1.txt
echo python test1 ended
echo python test2 started
time python3 kmeans.py 7 < tests/input_2.txt > my_output2py.txt
diff -s my_output2py.txt tests/output_2.txt
echo python test2 ended
echo python test3 started
time python3 kmeans.py 15 300 < tests/input_3.txt > my_output3py.txt
diff -s my_output3py.txt tests/output_3.txt
echo python test3 ended

gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -lm -o kmeans

echo c test1 started
time ./kmeans 3 600 < tests/input_1.txt > my_output1c.txt
diff -s my_output1c.txt tests/output_1.txt
echo c test1 ended
echo c test2 started
time ./kmeans 7 < tests/input_2.txt > my_output2c.txt
diff -s my_output2c.txt tests/output_2.txt
echo c test2 ended
echo c test3 started
time ./kmeans 15 300 < tests/input_3.txt > my_output3c.txt
diff -s my_output3c.txt tests/output_3.txt
echo c test3 ended

# echo ===================MY TESTS=================
# echo generating input file
# python3 generate_input.py 10 > my_intput_rand.txt
# echo finished generating input file
# echo python my test started
# time python3 kmeans.py 10 < my_intput_rand.txt > my_output_randpy.txt
# echo python my test ended
# echo C my test started
# time ./hw1 10 < my_intput_rand.txt > my_output_randc.txt
# echo C my test ended
# diff -s my_output_randpy.txt my_output_randc.txt




