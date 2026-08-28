/// @file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

#include "SE_common.h"

#include "SE_math.cpp"
#include "SE_explore.cpp"
#include "SE_input_output.cpp"
#include "SE_modes.cpp"





int main(const int argc, char ** const argv){

    CODE_ERRORS error_code = processCMDArgs(argc, argv);

    printErrors(error_code);

    return !(error_code == correct);
}


//! @brief Processes command line arguments, calls the function of the corresponding mode
//!
//! @return The program error code

CODE_ERRORS     processCMDArgs(int argc, char *argv[]){

    printf("\n");

    if(argc > 1){
        if(strcmp(argv[1], "f") == 0)
            return runFileMode();

        else if(strcmp(argv[1], "r") == 0)
            return runRandMode();

        else if(strcmp(argv[1], "m") == 0)
            return runManualMode();

        else if(strcmp(argv[1], "t") == 0)
            return runUnitTests();

        else if(strcmp(argv[1], "h") == 0)
            return runHelpMode();

    }

    return CMD_arg_incorrect;
}

//! @brief If error_code reports an error during program execution, this function outputs an error message to the terminal

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
