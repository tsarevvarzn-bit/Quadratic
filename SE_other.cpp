void            getRandCoefficients(coefficients *coefficients);
void            clearBuf(FILE *input);

SUCCESS_RATE    transformIntToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int);

SUCCESS_RATE    runOneUnitTest(coefficients coefficients, roots roots_ref, int num_of_test);
CODE_ERRORS     getCoeffAndAns(coefficients *coefficients, roots *roots, FILE *input);
CODE_ERRORS     getInputForRunUnitTests(FILE **input);

CODE_ERRORS     getCoefficients(coefficients *coefficients, FILE *input);
CODE_ERRORS     enterFileName(FILE **input_file);

int             checkingTerminalForYes();
int             getSeed();
CODE_ERRORS     checkInputOnEnter(FILE *input);



void            getRandCoefficients(coefficients *coefficients){

    assert(coefficients != NULL);

    coefficients->a = rand()%2001 - 1000;
    coefficients->b = rand()%2001 - 1000;
    coefficients->c = rand()%2001 - 1000;
}

void            clearBuf(FILE *input){

    int c = 0;
    while(((c = getc(input)) != EOF) && (c != '\n'));
}

SUCCESS_RATE    transformIntToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int){

    switch(n_o_r_int){
        case 0:
            *n_o_r = no_roots;
            break;
        case 1:
            *n_o_r = one_root;
            break;
        case 2:
            *n_o_r = two_roots;
            break;
        case 3:
            *n_o_r = infinity_roots;
            break;
        default:
            return error;
    }
    return success;
}

CODE_ERRORS     getCoefficients(coefficients *coefficients, FILE *input){

    assert(input != NULL);
    assert(coefficients != NULL);


    coefficients->a = coefficients->b = coefficients->c = 0;

    if(fscanf(input, "%lf %lf %lf", &(coefficients->a), &(coefficients->b), &(coefficients->c)) == 3){
        if(isfinite(coefficients->a) && isfinite(coefficients->b) && isfinite(coefficients->c)){
            return checkInputOnEnter(input);
        }else{
            return not_a_finite_number_in_the_input;
        }
    }else{
        return checkInputOnEnter(input);
    }
}

CODE_ERRORS     getCoeffAndAns(coefficients *coefficients, roots *roots, FILE *input){

    assert(input != NULL);
    assert(coefficients != NULL);

    assert(roots != NULL);

    coefficients->a = coefficients->b = coefficients->c = roots->ans1 = roots->ans2 = 0;
    int n_o_r_int = -1;

    if(fscanf(input, "%lf %lf %lf %d %lf %lf", &(coefficients->a), &(coefficients->b), &(coefficients->c), &n_o_r_int, &(roots->ans1), &(roots->ans2))== 6){
        if(isfinite(coefficients->a) && isfinite(coefficients->a) && isfinite(coefficients->a) && isfinite(roots->ans1) && isfinite(roots->ans2)){
            if(transformIntToSwitch(&(roots->n_o_r), n_o_r_int) == error)
                return incorrect_number_of_roots;
            return checkInputOnEnter(input);
        }else{
            return not_a_finite_number_in_the_input;
        }
    }else{
        return checkInputOnEnter(input);
    }
}

CODE_ERRORS     getInputForRunUnitTests(FILE **input){

    assert(input);

    printf("Do you want read tests from file or enter tests from CMD? f/c:");
    int s = getchar();
    clearBuf(stdin);
    while(s != 'f' && s != 'c'){
        printf("\nOutput is wrong, please enter f/c:");
        s = getchar();
        clearBuf(stdin);
    }
    printf("\n");
    *input = stdin;
    CODE_ERRORS error_code = correct;
    if(s == 'f'){
        if((error_code = enterFileName(input)) != correct)
            return error_code;
    }
    return correct;
}

SUCCESS_RATE    runOneUnitTest(coefficients coefficients, roots roots_ref, int num_of_test){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(isfinite(roots_ref.ans1));
    assert(isfinite(roots_ref.ans2));
    assert(num_of_test > 0);

    roots roots = {};
    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));
    if(roots.n_o_r == roots_ref.n_o_r){
        switch(roots.n_o_r){
            case no_roots:
                return success;

            case infinity_roots:
                return success;

            case one_root:
                if(isZero(roots.ans1 - roots_ref.ans1) || isZero(roots.ans2 - roots_ref.ans1))
                    return success;
                break;

            case two_roots:
                if((isZero(roots.ans1 - roots_ref.ans1) && isZero(roots.ans2 - roots_ref.ans1))||(isZero(roots.ans1 - roots_ref.ans2) && isZero(roots.ans2 - roots_ref.ans1)))
                    return success;
                break;

            default:
                ERROR_MASSAGE("Incorrect number of roots");
        }
    }
    printf("Test %d FAILED: a = %lg b = %lg c = %lg\n"
          "expected:    %d roots, x1 = %lg, x2 = %lg\n"
          "got:         %d roots, x1 = %lg, x2 = %lg\n\n", num_of_test, coefficients.a, coefficients.b, coefficients.c, roots_ref.n_o_r, roots_ref.ans1, roots_ref.ans2, roots.n_o_r, roots.ans1, roots.ans2);
    return error;
}

CODE_ERRORS     enterFileName(FILE **input_file){

    assert(input_file);

    char file_name[WORD_LEN] = {};
    printf("Enter file name: ");
    fgets(file_name, WORD_LEN, stdin);//Безопасный ввод с ограничением длины
    if(!strchr(file_name, '\n')){
        return long_file_name;
    }
    file_name[strcspn(file_name, "\n")] = '\0';
    *input_file = fopen(file_name, "r");
    if(*input_file == NULL){
        return incorrect_file_name;
    }
    printf("\n");
    return correct;
}

int             checkingTerminalForYes(){

    int c = getchar();
    while((c = getchar()) != 'Y' && c != 'N' && c != 'y' && c != 'n'){
        clearBuf(stdin);
        printf("\nIncorrect input, enter Y/N:");
    }
    if(c == 'N' || c == 'n')
        return 0;
    return 1;
}

CODE_ERRORS     checkInputOnEnter(FILE *input){

    int c = 0;
    while(((c = getc(input)) != '\n') && isspace(c));

    if(c == '\n'){
        //printf("checkInputOnEnter return correct");
        return correct;
    }else if(c == EOF){
        //printf("checkInputOnEnter return end_of_file");
        return end_of_file;
    }else{
        clearBuf(input);
        //printf("checkInputOnEnter return incorrect_data_format");
        return incorrect_data_format;
    }
}

int             getSeed(){

    int seed = 0;
    printf("Do you want to use random seed? Y/N:");
    if(checkingTerminalForYes()){
        time_t mytime = time(NULL);//Берет текущее время
        struct tm *now = localtime(&mytime);//Получаем данные в виде структуры
        seed = now->tm_sec;
        printf("\nSeed of this generation: %d\n\n", seed);
    }else{
        printf("Enter seed:");
        while((scanf("%d", &seed) != 1)){
            clearBuf(stdin);
            printf("\nIncorrect input, enter correct number:");
        }
        printf("\n");
    }
    return seed;
}
