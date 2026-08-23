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
        if(!isYes())
            return incorrect_number_of_equations;
    }
    if(n > 0){
        double a = 0, b = 0, c = 0;
        int seed = 0;
        printf("Do you want to use random seed? Y/N:");
        if(isYes()){
            time_t mytime = time(NULL);//Берет текущее время
            struct tm *now = localtime(&mytime);//Получаем данные в виде структуры
            seed = now->tm_sec;
            srand(seed);//Берем время в секундах с начала секунды // TODO Why not __TIME__
            printf("\nSeed of this generation: %d\n\n", seed);
        }else{
            printf("Enter seed:");
            if(scanf("%d", &seed) != 1)
                return incorrect_seed;
            printf("\n");
        }
        for(int i = 0; i < n; i++){
            getRandCoefficients(&a, &b, &c);
            printf("Roots for %lf %lf %lf:\n", a, b, c);
            solveAndPrint(a, b, c);
        }
        return correct;

    }else
        return incorrect_number_of_equations;
}

CODE_ERRORS     runManualMode(){

    double a = 0, b = 0, c = 0;
    printf("The program for solving square equation, please print a, b, c: \n\n");
    CODE_ERRORS error_code = correct;
    while((error_code = getCoefficients(&a, &b, &c, stdin)) != end_of_file){
        if(error_code == correct){
            solveAndPrint(a, b, c);
        }else if(error_code == incorrect_data_format){
            a = b = c = 0;
            clearBuf();
            printf("Incorrect input, try again\n\n");
        }else{
            return error_code;
        }
    }
    return error_code;
}

CODE_ERRORS     runFileMode(){

    double a = 0, b = 0, c = 0;
    FILE *input_file = NULL;
    CODE_ERRORS error_code = correct;

    if((error_code = enterFileName(&input_file)) != correct){
        return error_code;
    }

    while((error_code = getCoefficients(&a, &b, &c, input_file)) == correct){
        printf("Roots for %lg %lg %lg:\n", a, b, c);
        solveAndPrint(a, b, c);
    }
    return error_code;
}

CODE_ERRORS     runUnitTests(){

    FILE *input = NULL;
    CODE_ERRORS error_code = correct;
    if((error_code = getInputForUnitTests(&input)) != correct)
        return error_code;

    double a = 0, b = 0, c = 0, ans1_ref = 0, ans2_ref = 0;
    NUMBER_OF_ROOTS n_o_r_ref = no_roots;
    int num_of_test = 1;

    while((error_code = getCoeffAndAns(&a, &b, &c, &n_o_r_ref, &ans1_ref, &ans2_ref, input)) == correct){
        if(unitTest(a, b, c, n_o_r_ref, ans1_ref, ans2_ref, num_of_test) == success)
            printf("Test %d CORRECT\n\n", num_of_test);
        num_of_test++;
    }
    return error_code;
}

CODE_ERRORS runHelpMode(){
    printf("This is the program to solve quadratic equations in various forms, the main operating mods:\n"
            "1)Manual mode - you can enter the coefficients of a quadratic equation directly from the command line and get the solution\n"
            "2)File mode - you can write the coefficients of several equations at once into a file, and the program will provide an answer for each of them\n"
            "3)Random mode - the program will generate coefficients and solve the equations\n"
            "4)Test mode - mode for testing the program and checking edge cases: \n"
            "provide the program with coefficients and solutions in the form of a file, or enter them via the command line; the program will verify its solutions");
    return correct;
}
