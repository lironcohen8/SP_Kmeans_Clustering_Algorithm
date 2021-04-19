#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int k = argv[0];
    int max_iter = 200;
    char *input_file_name = argv[2];
    if (argc == 3) {
        max_iter = argv[1];
    }

    FILE *input = fopen(input_file_name,'rb');
    char buffer[1000];
    while (fget(buffer,1000,input)!= NULL) {   
        
    }

}