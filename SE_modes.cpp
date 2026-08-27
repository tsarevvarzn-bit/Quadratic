CODE_ERRORS     runManualMode();                                                                     //Основные режимы работы
CODE_ERRORS     runFileMode();
CODE_ERRORS     runRandMode();
CODE_ERRORS     runUnitTests();
CODE_ERRORS     runHelpMode();



CODE_ERRORS     runRandMode(){

    int n = 0;
    printf(YELLOW "Enter the number of equations: " DEFAULT);
    scanf("%d", &n);
    printf("\n");

    if(n > MAXIMUM_NUMBER_OF_RANDOM_EQUATIONS){

        printf(YELLOW "Are you sure you want to generate so many equations? Y/N: " DEFAULT);
        if(!checkTerminalForYes()){
            printf("\n");
            return correct;
        }
        printf("\n");
    }

    if(n > 0){
        coefficients coefficients = {};
        srand(getSeed());
        for(int i = 0; i < n; i++){
            getRandCoefficients(&coefficients);
            printf("Roots for %lf %lf %lf:\n", coefficients.a, coefficients.b, coefficients.c);
            solveAndPrint(coefficients);
        }
        return correct;
    }else
        return incorrect_number_of_equations;
}

CODE_ERRORS     runManualMode(){

    coefficients coefficients = {};
    printf(YELLOW "Please print a, b, c: \n\n" DEFAULT);
    CODE_ERRORS error_code = correct;

    while((error_code = getCoefficients(&coefficients, stdin)) != end_of_file){

        if(error_code == correct){

            //exploreTheFunction(); Математическое исследование функции с построением графика
            solveAndPrint(coefficients);

            printf(YELLOW "Do you want to continue? Y/N:" DEFAULT);

            if(checkTerminalForYes()){
                printf(YELLOW "\nPlease print a, b, c: \n\n" DEFAULT);
            }else{
                printf("\n");
                return correct;
            }

        }else if(error_code == incorrect_data_format){
            printf(BOLD RED "Incorrect input" YELLOW ", try again\n\n" DEFAULT);

        }else if(error_code == not_a_finite_number_in_the_input){
            printf(BOLD RED "Incorrect input" YELLOW ", print a finit coefficients\n\n" DEFAULT);

        }else if(error_code == incorrect_number_of_roots){
            printf(BOLD RED "Incorrect input" YELLOW ", print number of roots: 0 <= x <= 3\n\n" DEFAULT);

        }else{
            return error_code;

        }
        coefficients.a = coefficients.b = coefficients.c = 0;
    }
    return error_code;
}

CODE_ERRORS     runFileMode(){

    coefficients coefficients = {};
    FILE *input_file = NULL;
    CODE_ERRORS error_code = correct;

    if((error_code = enterFileName(&input_file)) != correct){
        return error_code;
    }

    while((error_code = getCoefficients(&coefficients, input_file)) == correct){

        printf("Roots for %lg %lg %lg:\n", coefficients.a, coefficients.b, coefficients.c);
        solveAndPrint(coefficients);
    }
    return error_code;
}

CODE_ERRORS     runUnitTests(){

    FILE *input = NULL;
    CODE_ERRORS error_code = correct;
    int isIntegratedTests = 0;

    if((error_code = getInputForRunUnitTests(&input, &isIntegratedTests)) != correct)
        return error_code;

    if(isIntegratedTests){
        return runIntegratedTests();

    }else{
        return runUsersTests(input);

    }

}

CODE_ERRORS     runHelpMode(){

    printf("\n");
    printf(BOLD CYAN "+------------------------------------------------+\n" DEFAULT);
    printf(BOLD CYAN "|" DEFAULT BOLD "           Quadratic Equation Solver            " DEFAULT BOLD CYAN "|\n" DEFAULT);
    printf(BOLD CYAN "|" DEFAULT BOLD "          Tsarev Vladislav, FRKT, 2026          " DEFAULT BOLD CYAN "|\n" DEFAULT);
    printf(BOLD CYAN "+------------------------------------------------+\n" DEFAULT);
    printf("\n");

    printf(BOLD  VIOLET "This program solves quadratic equations of the form:\n\n" DEFAULT);
    printf("    ax^2 + bx + c = 0\n\n");

    printf(BOLD VIOLET "Operating modes (set via command-line argument):\n\n" DEFAULT);

    printf(BOLD GREEN "  m" DEFAULT " -> " BOLD "manual mode\n" DEFAULT);
    printf("      Enter coefficients directly in the console and get the solution\n\n");

    printf(BOLD GREEN "  f" DEFAULT " -> " BOLD "file mode\n" DEFAULT);
    printf("      Write several equations into a file - the program will solve each one\n\n");

    printf(BOLD GREEN "  r" DEFAULT " -> " BOLD "random mode\n" DEFAULT);
    printf("      Generates random coefficients and solves the equations\n");
    printf("      " YELLOW "Options:\n" DEFAULT);
    printf("        " CYAN "    " DEFAULT "Use your seed for the generator\n");
    printf("        " CYAN "    " DEFAULT "Seed will be taken from current time (different results every run)\n\n");

    printf(BOLD GREEN "  t" DEFAULT " -> " BOLD "test mode\n" DEFAULT);
    printf("      Verifies solutions for correctness\n");
    printf("      " YELLOW "Ways to run:\n" DEFAULT);
    printf("        " CYAN "    " DEFAULT "Input test data from console (coefficients + expected roots)\n");
    printf("        " CYAN "    " DEFAULT "Input test data from file (coefficients + expected roots)\n");
    printf("        " CYAN "    " DEFAULT "Use predefined data in code\n\n");

    printf(BOLD GREEN "  h" DEFAULT " -> " BOLD "help\n" DEFAULT);
    printf("      Show this help message\n\n");

    printf(BOLD VIOLET "Useful additions:\n" DEFAULT);
    printf("  Any solution is automatically checked by podstanovka\n");
    printf("  In " BOLD GREEN "m" DEFAULT " mode and " BOLD GREEN "f" DEFAULT " mode record the coefficients in the format: a b c\\n\n");
    printf("  In " BOLD GREEN "t" DEFAULT " mode print coefficients and answer in one line: a b c number_of_roots root1 root2\\n\n");
    printf(YELLOW "    Remark:" DEFAULT " number_of_roots is an integer number: 0 - ther is no roots, 1 - one root (write the root in the first cell - ans1, ans2 - any number),\n"\
           "    2 - two roots, 3 - infinity number of roots, " YELLOW BOLD "any other number is an incorrect input format\n" DEFAULT);
    printf("\n");

    printf(BOLD CYAN "Good luck solving quadratic equations! Remember: the equation is solved by a neural network, it can sometimes make mistakes\n\n" DEFAULT);

    return correct;
}

