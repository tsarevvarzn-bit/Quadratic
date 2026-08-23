#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>

const int            WORD_LEN = 100;
const double         EPSILON = 0.0001;

enum NUMBER_OF_ROOTS {no_roots, one_root, two_roots, infinity_roots}; //Что выводить при отсутствии корней, одном, двух и бесконечном количестве корней
enum CODE_ERRORS     {correct, CMD_arg_incorrect, long_file_name, incorrect_file_name, incorrect_data_format, incorrect_number_of_equations, end_of_file}; //Что возвращать функциям в случае ошибки и в случае, когда она отработала хорошо
enum SUCCESS_RATE    {error, success};

#include "SE_math.cpp"
#include "SE_other.cpp"
#include "SE_modes.cpp"

CODE_ERRORS     processCMDArgs(int argc, char *argv[]);                                          //Функции, вызывающиеся всегда и из main
int             isError(int error_code);
void            printErrors(int error_code);

int main(const int argc, char ** const argv){
    int error_code = processCMDArgs(argc, argv);
    printErrors(error_code);
    return isError(error_code);
}

CODE_ERRORS     processCMDArgs(int argc, char *argv[]){

    if(argc > 1){
        if(*argv[1] == 'f'){
            return RunFileMode();

        }else if(*argv[1] == 'r'){
            return RunRandMode();

        }else if(*argv[1] == 'm'){
            return RunManualMode();

        }else if(*argv[1] == 't'){
            return RunUnitTests();
        }
    }

    return CMD_arg_incorrect;
}

int             isError(int error_code){

    return !(error_code == correct);
}

void            printErrors(int error_code){

    switch(error_code){
        case correct:
            break;

        case CMD_arg_incorrect:
            printf("CMD argument is incorrect\n\n");
            break;

        case long_file_name:
            printf("The file name is too long\n\n");
            break;

        case incorrect_file_name:
            printf("There is no file with this name\n\n");
            break;

        case incorrect_data_format:
            printf("The data format is incorrect\n\n");
            break;

        case incorrect_number_of_equations:
            printf("Incorrect for number od equations\n\n");

        default:
            ;
    }
}
