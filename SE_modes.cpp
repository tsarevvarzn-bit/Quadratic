CODE_ERRORS     RunManualMode();                                                                     //Основные режимы работы
CODE_ERRORS     RunFileMode();
CODE_ERRORS     RunRandMode();
CODE_ERRORS     RunUnitTests();



CODE_ERRORS     RunRandMode(){

    printf("Enter the number of equations: ");
    int n = 0;
    scanf("%d", &n);
    printf("\n");

    if(n > 0){
        double a = 0, b = 0, c = 0;
        time_t mytime = time(NULL);//Берет текущее время
        struct tm *now = localtime(&mytime);//Получаем данные в виде структуры
        srand(now->tm_sec);//Берем время в секундах с начала секунды
        for(int i = 0; i < n; i++){
            getRandCoefficients(&a, &b, &c);
            printf("Roots for %lf %lf %lf:\n", a, b, c);
            solveAndPrint(a, b, c);
        }
        return correct;

    }else{
        return incorrect_number_of_equations;
    }
}

CODE_ERRORS     RunManualMode(){

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

CODE_ERRORS     RunFileMode(){

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
    if(error_code == end_of_file){
        solveAndPrint(a, b, c);
    }

    return error_code;
}

CODE_ERRORS     RunUnitTests(){

    FILE *input;
    CODE_ERRORS error_code = correct;
    if((error_code = getInputForUnitTests(&input)) != correct)
        return error_code;

    double a = 0, b = 0, c = 0, ans1_ref = 0, ans2_ref = 0;
    NUMBER_OF_ROOTS n_o_r_ref = no_roots;
    int num_of_test = 1;

    while((error_code = getCoeffAndAns(&a, &b, &c, &n_o_r_ref, &ans1_ref, &ans2_ref, input)) == correct){
        //Считаем один пример, сравниваем с реф значениями, если не совпадает - выводим данные этого примера
        if(unitTest(a, b, c, n_o_r_ref, ans1_ref, ans2_ref, num_of_test))
            printf("Test %d CORRECT\n", num_of_test);
        num_of_test++;
    }
    if(error_code == end_of_file){
        if(unitTest(a, b, c, n_o_r_ref, ans1_ref, ans2_ref, num_of_test))
            printf("Test %d CORRECT\n", num_of_test);
    }

    return error_code;
}
