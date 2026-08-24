CODE_ERRORS     runManualMode();                                                                     //Основные режимы работы
CODE_ERRORS     runFileMode();
CODE_ERRORS     runRandMode();
CODE_ERRORS     runUnitTests();
CODE_ERRORS     runHelpMode();



CODE_ERRORS     runRandMode(){

    int n = 0;
    printf("Enter the number of equations: ");
    scanf("%d", &n);
    printf("\n");

    if(n > MAXIMUM_NUMBER_OF_RANDOM_EQUATIONS){
        printf("Are you sure you want to generate so many equations? Y/N:");
        if(!checkingTerminalForYes())
            return incorrect_number_of_equations;
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
    printf("The program for solving square equation, please print a, b, c: \n\n");
    CODE_ERRORS error_code = correct;

    while((error_code = getCoefficients(&coefficients, stdin)) != end_of_file){

        if(error_code == correct){
            solveAndPrint(coefficients);
        }else if(error_code == incorrect_data_format){
            printf("Incorrect input, try again\n\n");
        }else if(error_code == not_a_finite_number_in_the_input){
            printf("Incorrect input, print a finit coefficients\n\n");
        }else if(error_code == incorrect_number_of_roots){
            printf("Incorrect input, print number of roots: 0 <= x <= 3\n\n");
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
    if((error_code = getInputForRunUnitTests(&input)) != correct)
        return error_code;

    coefficients coefficients = {};
    roots roots = {};
    int num_of_test = 1;

    while((error_code = getCoeffAndAns(&coefficients, &roots, input)) != end_of_file){
        if(error_code == correct){
            if(runOneUnitTest(coefficients, roots, num_of_test) == success)
                printf("Test %d CORRECT\n\n", num_of_test);
            num_of_test++;
        }else if(error_code == incorrect_data_format){
            printf("Incorrect input, try again\n\n");
        }else if(error_code == incorrect_number_of_roots){
            printf("Incorrect input, print number of roots: 0 <= x <= 3\n\n");
        }else{
            return error_code;
        }
    }
    return error_code;
}

CODE_ERRORS     runHelpMode(){//Сделать более подробно

    printf("\nThis is the program to solve quadratic equations in various forms, the main operating mods that you can launch using command-line arguments:\n\n"
            "  m  manual mode  - enter coefficients interactively\n"
            "  f  file mode    - read several equations from file\n"
            "  r  random mode  - generate coefficients and solve\n"
            "  t  test mode    - verify solutions against expected data\n"
            "  h  help mode    - show this help\n\n");
    return correct;
}
