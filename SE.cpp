#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

#define ERROR_MASSAGE(str)      printf("\nERROR MASSAGE: %s, file %s, function: %s, line %d", str, __FILE__, __func__, __LINE__); \
                                abort()

const int            WORD_LEN = 100;
const int            MAXIMUM_NUMBER_OF_RANDOM_EQUATIONS = 100;
const double         EPSILON = 0.0001;

enum NUMBER_OF_ROOTS {
    no_roots,
    one_root,
    two_roots,
    infinity_roots
};

enum CODE_ERRORS     {
    correct,
    CMD_arg_incorrect,
    long_file_name,
    incorrect_file_name,
    incorrect_data_format,
    incorrect_number_of_equations,
    end_of_file,
    not_a_finite_number_in_the_input,
    incorrect_number_of_roots
};

enum SUCCESS_RATE    {
    success = 0,
    error = 1
};

struct coefficients  {
    double a;
    double b;
    double c;
};


struct roots         {
    NUMBER_OF_ROOTS n_o_r;
    double ans1;
    double ans2;
};

struct testCase       {
    coefficients coefficients;
    roots roots;
};

#include "SE_colors.cpp"
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

    printf("\n");

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
            printf(BOLD RED"ERROR: CMD argument is incorrect\n\n" DEFAULT);
            break;

        case long_file_name:
            printf(BOLD RED "ERROR: The file name is too long\n\n" DEFAULT);
            break;

        case incorrect_file_name:
            printf(BOLD RED "ERROR: There is no file with this name\n\n" DEFAULT);
            break;

        case incorrect_data_format:
            printf(BOLD RED "ERROR: The data format is incorrect\n\n" DEFAULT);
            break;

        case not_a_finite_number_in_the_input:
            printf(BOLD RED "ERROR: Not a finit number in input\n\n" DEFAULT);
            break;

        case incorrect_number_of_equations:
            printf(BOLD RED "ERROR: Incorrect number of equations\n\n" DEFAULT);
            break;

        case incorrect_number_of_roots:
            printf(BOLD RED "ERROR: Incorrect number of roots\n\n" DEFAULT);
            break;

        case end_of_file:
            printf(BOLD GREEN"The file has been fully read and processed correctly\n\n" DEFAULT);
            break;

        default:
            ERROR_MASSAGE("Error code is incorrect");
    }
}
