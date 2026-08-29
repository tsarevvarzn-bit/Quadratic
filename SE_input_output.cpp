/// @file

//! @brief It takes all characters from the specified file until it encounters '\n', clearing the input for other functions
//!
//! @param [in] input a pointer to the file where the characters will be taken from
void            clearBuf(FILE *input){

    int c = 0;
    while(((c = getc(input)) != EOF) && (c != '\n'));
}



//! @brief Get coefficients from transmitted input
//!
//! @param [out] coefficients a pointer to the structure to put the data in
//!
//! @param [in]  input The FILE* from which the data will be read
//!
//! @note In order for the data to be read and processed, it must be presented in a specific format: a b c '\n', where a, b, c - integer finite numbers
//!
//! @return Error code
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

//! @brief Get test case from transmitted input
//!
//! @param [out] testCase a pointer to the structure to put the data in
//!
//! @param [in]  input The FILE* from which the data will be read
//!
//! @note In order for the data to be read and processed, it must be presented in a specific format: a b c number_of_roots ans1 ans2'\n',
//!       where a, b, c, number_of_roots are finite integer numbers,
//!       number_of_roots is an integer number: 0 - ther is no roots (ans1, ans2 - any numbers), 1 - one root (write the root in the first cell - ans1, ans2 - any number),
//!       2 - two roots(ans1, ans2 - finite numbers), 3 - infinity number of roots(ans1, ans2 - any numbers)
//!
//! @return Error code
CODE_ERRORS     getCoeffAndAns(testCase *test_case_p, FILE *input){

    assert(input != NULL);
    assert(test_case_p != NULL);

    test_case_p->coefficients.a = test_case_p->coefficients.b = test_case_p->coefficients.c = test_case_p->roots.ans1 = test_case_p->roots.ans2 = 0;

    int n_o_r_int = -1;

    if(input == stdin)
        printf(YELLOW "Print coefficients and answer in one line:" DEFAULT " a b c number_of_roots root1 root2\n");

    if(fscanf(input, "%lf %lf %lf %d %lf %lf", &(test_case_p->coefficients.a),
                                               &(test_case_p->coefficients.b),
                                               &(test_case_p->coefficients.c),
                                               &n_o_r_int,
                                               &(test_case_p->roots.ans1),
                                               &(test_case_p->roots.ans2)) == 6){

        if(isRootsFormatCorrect(test_case_p->roots)){

            if(transformIntToSwitch(&(test_case_p->roots.n_o_r), n_o_r_int) == error)
                return incorrect_number_of_roots;

            return checkInputOnEnter(input);

        }else{
            return not_a_finite_number_in_the_input;
        }
    }else{
        return checkInputOnEnter(input);
    }

}

//! @brief Auxiliary function for runUnitTests(), asks the user about the necessary configuration for running unit testing
//!
//! @param [out] input a pointer to a pointer to the FILE* from which the user wants to enter data
//!
//! @param [out] is_internal_p a pointer to a variable indicating whether the user wants to run the internal tests.
//!
//! @return Error code
CODE_ERRORS     getInputForRunUnitTests(FILE **input, int *is_internal_p){

    assert(input);
    assert(is_internal_p);

    *is_internal_p = 0;
    printf(YELLOW "Do you want read tests from file, enter tests from CMD or run internal tests? f/c/p:" DEFAULT);
    int c = getchar();
    clearBuf(stdin);

    while(c != 'f' && c != 'c' && c != 'p'){
        printf(BOLD RED"\nOutput is wrong" YELLOW ", please enter f/c/p:" DEFAULT);
        c = getchar();
        clearBuf(stdin);
    }

    printf("\n");
    *input = stdin;
    CODE_ERRORS error_code = correct;

    if(c == 'f'){
        if((error_code = enterFileName(input)) != correct)
            return error_code;
    }else if(c == 'p'){
        *is_internal_p = 1;
    }
    return correct;
}



//! @brief Gives a pointer to the file that the user wants to read data from.
//!
//! @param [out] input_file pointer to the pointer to the file that the user wants to open
//!
//! @return Error code
CODE_ERRORS     enterFileName(FILE **input_file){

    assert(input_file);

    char file_name[WORD_LEN] = {};
    printf(YELLOW "Enter file name: " DEFAULT);
    fgets(file_name, WORD_LEN, stdin);//Безопасный ввод с ограничением длины

    if( !strchr(file_name, '\n')){
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

//! @brief Expects yes or no answer from the user, processing incorrect input and waiting for correct input
//!
//! @return Error code
int             checkTerminalForYes(){

    int c = 0;

    while(isspace(c = getchar()));//Ожидаем любой видимый в консоли символ

    while(c != 'Y' && c != 'N' && c != 'y' && c != 'n'){
        clearBuf(stdin);
        printf(BOLD RED "\nIncorrect input" YELLOW ", enter Y/N:" DEFAULT);
        c = getchar();
    }
    clearBuf(stdin);
    if(c == 'N' || c == 'n')
        return 0;
    return 1;
}

//! @brief Checks if there is a '\n' after the sequence of space characters
//!
//! @param [out] input pointer to the file that we want to check
//!
//! @return Error code
CODE_ERRORS     checkInputOnEnter(FILE *input){

    assert(input);

    int c = 0;
    while(((c = getc(input)) != '\n') && isspace(c));

    if(c == '\n'){
        return correct;
    }else if(c == EOF){
        return end_of_file;
    }else{
        clearBuf(input);
        return incorrect_data_format;
    }
}

//! @brief Communicates with the user and returns seed
//!
//! @note If the user wants to generate a random seed, it will be generated using time
//!
//! @return seed how unsigned int
unsigned int    getSeed(){

    int seed = 0;

    printf(YELLOW "Do you want to use random seed? Y/N: " DEFAULT);

    if(checkTerminalForYes()){

        seed = (((int)time(NULL))%1000);
        printf(YELLOW "\nSeed of this generation: %u\n\n" DEFAULT, seed);

    }else{

        printf("\n");
        printf(YELLOW "Enter seed:" DEFAULT);
        while((scanf("%d", &seed) != 1) ){
            clearBuf(stdin);
            printf(BOLD RED"\nIncorrect input," YELLOW " enter correct number:" DEFAULT);
        }
        printf("\n");
    }
    return seed;
}



//! @brief Run Users tests from file or terminal
//!
//! @param [in] input pointer to the file that we want to read
//!
//! @return always and_of_file
CODE_ERRORS      runUsersTests(FILE *input){

    testCase test_case = {};
    int num_of_test = 1;
    CODE_ERRORS error_code = correct;

    while((error_code = getCoeffAndAns(&test_case, input)) != end_of_file){

        if(error_code == correct){
            runOneUnitTest(test_case, num_of_test);
            num_of_test++;

        }else if(error_code == incorrect_data_format){
            if(input != stdin)
                num_of_test++;

            printf(BOLD RED "Incorrect input" YELLOW ", try again\n\n" DEFAULT);

        }else if(error_code == incorrect_number_of_roots){
            printf(BOLD RED "Incorrect input" YELLOW ", print number of roots: 0 <= x <= 3\n\n" DEFAULT);

        }else{
            return error_code;
        }
    }
    return error_code;
}

//! @brief Print unit test result
//!
//! @param [in] s_r is test correct
//!
//! @param [in] testCase data of test
//!
//! @param [in] roots solution of program
//!
//! @param [in] num_of_test number of this test
void            printUnitTestResult(SUCCESS_RATE s_r, testCase testCase, roots roots, int num_of_test){

    assert(num_of_test > 0);

    if(s_r == success){
        printf(BOLD GREEN "Test %d CORRECT: a = %lg b = %lg c = %lg\n"
                          "Output:      %d roots, x1 = %lg, x2 = %lg\n" DEFAULT,
                          num_of_test, testCase.coefficients.a, testCase.coefficients.b, testCase.coefficients.c,
                                       testCase.roots.n_o_r,    testCase.roots.ans1,     testCase.roots.ans2);
    }else{
        printf(BOLD RED   "Test %d FAILED: a = %lg b = %lg c = %lg\n"
                          "Expected:    %d roots, x1 = %lg, x2 = %lg\n"
                          "Got:         %d roots, x1 = %lg, x2 = %lg\n\n" DEFAULT,
                          num_of_test, testCase.coefficients.a, testCase.coefficients.b, testCase.coefficients.c,
                                        testCase.roots.n_o_r,    testCase.roots.ans1,     testCase.roots.ans2,
                                        roots.n_o_r,             roots.ans1,              roots.ans2);
    }
}

//! @brief print error when the program solved the equation, but the roots do not fit when substituting
//!
//! @param [in] test_case the struct which contains the coefficients of the equation and the roots
void            printCalcError(testCase test_case){

    assert(isfinite(test_case.coefficients.a));
    assert(isfinite(test_case.coefficients.b));
    assert(isfinite(test_case.coefficients.c));
    assert(isRootsFormatCorrect(test_case.roots));

    printf(BOLD RED "Error during equation solving:\nCoefficients: %lg %lg %lg\nOutput:\n" DEFAULT, test_case.coefficients.a, test_case.coefficients.b, test_case.coefficients.c);
    printRoots(test_case.roots);
}

//! @brief print roots in terminal
//!
//! @param [in] roots the structure that contains the roots of the equation
//!
//!
//! @note аor correct output, it is required that in the case of a single root, it is written to ans1.
void            printRoots(roots roots){

    switch(roots.n_o_r){
        case no_roots:
            assert(isnan(roots.ans1));
            assert(isnan(roots.ans2));
            printf("There is no roots\n");
            break;

        case one_root:
            assert(isfinite(roots.ans1));
            assert(isnan(roots.ans2));
            printf("There is one root: x = %-15.10lg\n", roots.ans1);
            break;

        case two_roots:
            assert(isfinite(roots.ans1));
            assert(isfinite(roots.ans2));
            printf("There is two roots: x1 = %-15.10lg x2 = %-15.10lg\n", roots.ans1, roots.ans2);
            break;

        case infinity_roots:
            assert(isnan(roots.ans1));
            assert(isnan(roots.ans2));
            printf("Infinity number of roots\n");
            break;

        default:
            ERROR_MASSAGE("Incorrect number of roots");

    }
    printf("\n");
}
