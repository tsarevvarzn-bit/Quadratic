void            getRandCoefficients(double *a, double *b, double *c);
void            clearBuf();

SUCCESS_RATE    intToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int);

SUCCESS_RATE    unitTest(double a, double b, double c, NUMBER_OF_ROOTS n_o_r_ref, double ans1_ref, double ans2_ref, int num_of_test);
CODE_ERRORS     getCoeffAndAns(double *a, double *b, double *c, NUMBER_OF_ROOTS *n_o_r, double *ans1, double *ans2, FILE *input);
CODE_ERRORS     getInputForUnitTests(FILE **input);

CODE_ERRORS     getCoefficients(double *a, double *b, double *c, FILE *input);
CODE_ERRORS     enterFileName(FILE **input_file);

int isYes();


void            getRandCoefficients(double *a, double *b, double *c){
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    *a = rand()%2001 - 1000;
    *b = rand()%2001 - 1000;
    *c = rand()%2001 - 1000;
}

void            clearBuf(){
    int c = 0;
    while(((c = getc(stdin)) != EOF) && (c != '\n'));
}

SUCCESS_RATE    intToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int){
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

CODE_ERRORS     getCoefficients(double *a, double *b, double *c, FILE *input){

    assert(input != NULL);
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    int x = 0;
    if(((x = fscanf(input, "%lf %lf %lf", a, b, c)) == 3) && ((getc(input) == '\n') || (getc(input) == EOF))){
        return correct;
    }else{
        if(getc(input) == EOF){
            return end_of_file;
        }else{
            return incorrect_data_format;
        }
    }
}

CODE_ERRORS     getCoeffAndAns(double *a, double *b, double *c, NUMBER_OF_ROOTS *n_o_r, double *ans1, double *ans2, FILE *input){

    assert(input != NULL);
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(ans1 != NULL);
    assert(ans2 != NULL);

    int number_of_accepted_arguments = 0;
    int n_o_r_int = -1;
    if((number_of_accepted_arguments = fscanf(input, "%lf %lf %lf %d %lf %lf", a, b, c, &n_o_r_int, ans1, ans2)) == 6 && (getc(input) == '\n' || getc(input) == EOF)){
        if(intToSwitch(n_o_r, n_o_r_int) == error)
            return incorrect_data_format;
        return correct;
    }else{
        if(getc(input) == EOF){
            return end_of_file;
        }else{
            return incorrect_data_format;
        }
    }
}

CODE_ERRORS     getInputForUnitTests(FILE **input){

    assert(input);
    assert(*input);

    printf("Do you want read tests from file or enter tests from CMD? f/c:");
    int s = getchar();
    while(s != 'f' && s != 'c'){
        clearBuf();
        printf("\nOutput is wrong, please enter f/c:");
        s = getchar();
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

SUCCESS_RATE    unitTest(double a, double b, double c, NUMBER_OF_ROOTS n_o_r_ref, double ans1_ref, double ans2_ref, int num_of_test){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(ans1_ref));
    assert(isfinite(ans2_ref));
    assert(isfinite(c));
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));
    assert(!isnan(ans1_ref));
    assert(!isnan(ans2_ref));
    assert(!isnan(c));
    assert(num_of_test > 0);

    double ans1 = 0, ans2 = 0;
    NUMBER_OF_ROOTS n_o_r = solveSquareEq(a, b, c, &ans1, &ans2);
    if(n_o_r == n_o_r_ref){
        switch(n_o_r){
            case no_roots:
                return success;
            case infinity_roots:
                return success;
            case one_root:
                if(isZero(ans1-ans1_ref) || isZero(ans2-ans1_ref))
                    return success;
                break;
            case two_roots:
                if((isZero(ans1-ans1_ref) && isZero(ans2-ans2_ref))||(isZero(ans1-ans2_ref) && isZero(ans2-ans1_ref)))
                    return success;
                break;
            default:
                assert(0 && "Incorrect number of roots");
        }
    }
    printf("Test %d FAILED: a = %lg b = %lg c = %lg\n"
          "expected:    %d roots, x1 = %lg, x2 = %lg\n"
          "got:         %d roots, x1 = %lg, x2 = %lg\n\n", num_of_test, a, b, c, n_o_r_ref, ans1_ref, ans2_ref, n_o_r, ans1, ans2);
    return error;
}

CODE_ERRORS     enterFileName(FILE **input_file){

    assert(input_file);
    assert(*input_file);

    if(input_file == NULL || *input_file == NULL)
        assert(0 && "Incorrect input file");
    char file_name[WORD_LEN] = {};
    printf("Enter file name: ");
    int n = 0;
    scanf("%s%n", file_name, &n); // TODO too long file name but no security  // use another func from std
    if(n >= WORD_LEN){
        return long_file_name;
    }
    *input_file = fopen(file_name, "r");
    if(*input_file == NULL){
        return incorrect_file_name;
    }
    printf("\n");
    return correct;
}

int isYes(){
    int c = getchar();
    while((c = getchar()) != 'Y' && c != 'N' && c != 'y' && c != 'n'){
        clearBuf();
        printf("\nIncorrect input, enter Y/N:");
    }
    if(c == 'N' || c == 'n')
        return 0;
    return 1;
}

