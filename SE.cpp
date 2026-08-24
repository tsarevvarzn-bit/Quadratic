#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

const int            WORD_LEN = 100;
const int            MAXIMUM_NUMBER_OF_RANDOM_EQUATIONS = 100;
const double         EPSILON = 0.0001;

enum NUMBER_OF_ROOTS {no_roots, one_root, two_roots, infinity_roots}; //Что выводить при отсутствии корней, одном, двух и бесконечном количестве корней
enum CODE_ERRORS     {correct, CMD_arg_incorrect, long_file_name, incorrect_file_name, incorrect_data_format, incorrect_number_of_equations, end_of_file,
                      not_a_finite_number_in_the_input, incorrect_number_of_roots}; //Что возвращать функциям в случае ошибки и в случае, когда она отработала хорошо
enum SUCCESS_RATE    {success = 0, error = 1};

struct coefficients{
    double a;
    double b;
    double c;
};
struct roots{
    NUMBER_OF_ROOTS n_o_r;
    double ans1;
    double ans2;
};

#include "SE_math.cpp"
#include "SE_other.cpp"
#include "SE_modes.cpp"

CODE_ERRORS     processCMDArgs(int argc, char *argv[]);                                          //Функции, вызывающиеся всегда и из main
void            printErrors(CODE_ERRORS error_code);



int main(const int argc, char ** const argv){

    CODE_ERRORS error_code = processCMDArgs(argc, argv);

    printErrors(error_code);

    return !(error_code == correct);
}

CODE_ERRORS     processCMDArgs(int argc, char *argv[]){

    if(argc > 1){
        if(*argv[1] == 'f')
            return runFileMode();

        else if(*argv[1] == 'r')
            return runRandMode();

        else if(*argv[1] == 'm')
            return runManualMode();

        else if(*argv[1] == 't')
            return runUnitTests();

        else if(*argv[1] == 'h')
            return runHelpMode();

    }

    return CMD_arg_incorrect;
}

void            printErrors(CODE_ERRORS error_code){

    switch(error_code){
        case correct:
            break;

        case CMD_arg_incorrect:
            printf("ERROR: CMD argument is incorrect\n\n");
            break;

        case long_file_name:
            printf("ERROR: The file name is too long\n\n");
            break;

        case incorrect_file_name:
            printf("ERROR: There is no file with this name\n\n");
            break;

        case incorrect_data_format:
            printf("ERROR: The data format is incorrect\n\n");
            break;

        case not_a_finite_number_in_the_input:
            printf("ERROR: not a finit number in input\n\n");
            break;

        case incorrect_number_of_equations:
            printf("ERROR: Incorrect number of equations\n\n");
            break;

        case incorrect_number_of_roots:
            printf("ERROR: Incorrect number of roots\n\n");
            break;

        case end_of_file:
            printf("The file has been fully read and processed correctly\n\n");
            break;

        default:
            assert(0 && "Error code is incorrect");
    }
}
