python kmeans_try.py 3 600 < tests/input_1.txt > my_output1py.txt
python kmeans_try.py 7 < tests/input_2.txt > my_output2py.txt
python kmeans_try.py 15 300 < tests/input_3.txt > my_output3py.txt

gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -lm -o kmeans
@REM gcc ex1.c -o kmeans

.\kmeans.exe 3 600 < tests\input_1.txt > my_output1c.txt
.\kmeans.exe 7 < tests\input_2.txt > my_output2c.txt
.\kmeans.exe 15 300 < tests\input_3.txt > my_output3c.txt

FC my_output1py.txt tests/output_1.txt
FC my_output2py.txt tests/output_2.txt
FC my_output3py.txt tests/output_3.txt

FC my_output1c.txt tests/output_1.txt
FC my_output2c.txt tests/output_2.txt
FC my_output3c.txt tests/output_3.txt
pause