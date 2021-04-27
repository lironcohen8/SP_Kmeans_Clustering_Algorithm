echo python test1 started
time python3 kmeans.py 3 600 < tests/input_1.txt > my_output1py.txt
echo python test1 ended
echo python test2 started
time python3 kmeans.py 7 < tests/input_2.txt > my_output2py.txt
echo python test2 ended
echo python test3 started
time python3 kmeans.py 15 300 < tests/input_3.txt > my_output3py.txt
echo python test3 ended

gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -lm -o kmeans

echo c test1 started
time ./kmeans 3 600 < tests/input_1.txt > my_output1c.txt
echo c test1 ended
echo c test2 started
time ./kmeans 7 < tests/input_2.txt > my_output2c.txt
echo c test2 ended
echo c test3 started
time ./kmeans 15 300 < tests/input_3.txt > my_output3c.txt
echo c test3 ended

diff -s my_output1py.txt tests/output_1.txt
diff -s my_output2py.txt tests/output_2.txt
diff -s my_output3py.txt tests/output_3.txt

diff -s my_output1c.txt tests/output_1.txt
diff -s my_output2c.txt tests/output_2.txt
diff -s my_output3c.txt tests/output_3.txt
