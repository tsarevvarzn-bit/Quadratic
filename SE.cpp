#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

// test.c
// include in SE.cpp

const int            WORD_LEN = 100;
const double         EPSILON = 0.0001;

enum NUMBER_OF_ROOTS {no_roots = 0, one_root = 1, two_roots = 2, infinity_roots = 3}; //Что выводить при отсутствии корней, одном, двух и бесконечном количестве корней
enum CODE_ERRORS     {correct, CMD_arg_incorrect, long_file_name, incorrect_file_name, incorrect_data_format, incorrect_number_of_equations, end_of_file}; //Что возвращать функциям в случае ошибки и в случае, когда она отработала хорошо
enum CALC_ERRORS     {calc_error, no_calc_error};
enum SUCCESS_RATE    {error, success};

// snake_case
// pascalCase
// CamelCase
// CAPS_CASE

enum CODE_ERRORS     processCMDArgs(int argc, char *argv[]);                                          //Функции, вызывающиеся всегда и из main
int                  checkErrors(int error_code);
void                 printErrors(int error_code);

void                 solveAndPrint(double a, double b, double c);                                     //Решает уравнение и выводит корни
enum NUMBER_OF_ROOTS solveSquareEq(double a, double b, double c, double *ans1, double *ans2);         //Решает частный случай гарантированно квадратного уравнения
enum NUMBER_OF_ROOTS linearEq(double b, double c, double *ans1);                                      //Решает частный случай вырожденного уравнения
enum NUMBER_OF_ROOTS squareEq(double a, double b, double c, double *ans1, double *ans2);              //Решает квадратное уравнение в общем случае
void                 printRoots(enum NUMBER_OF_ROOTS num_of_roots, double ans1, double ans2);         //Напечатать корни в терминал

enum CODE_ERRORS     getCoefficients(double *a, double *b, double *c, FILE *input);                   //Взять 3 числа из FILE*

enum CALC_ERRORS     testingTheSolution(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r, double ans1, double ans2); //Тестирование подстановкой
void                 printCalcError(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r, double ans1, double ans2);     //Вывод ошибки после подстановки

enum CODE_ERRORS     manualMode();                                                                     //Основные режимы работы
enum CODE_ERRORS     fileMode();
enum CODE_ERRORS     randMode();
enum CODE_ERRORS     unitTests();

int                  isZero(double x);                                                                 //Вспомогательные функции
void                 getRandCoefficients(double *a, double *b, double *c);
void                 clearBuf();
enum CODE_ERRORS     enterFileName(FILE **input_file);
enum SUCCESS_RATE    intToSwitch(enum NUMBER_OF_ROOTS *n_o_r, int n_o_r_int);
int                  isRootCorrect(double a, double b, double c, double root);                         //Проверяет корни подстановкой

enum SUCCESS_RATE    unitTest(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r_ref, double ans1_ref, double ans2_ref, int num_of_test);
enum CODE_ERRORS     getCoeffAndAns(double *a, double *b, double *c, enum NUMBER_OF_ROOTS *n_o_r, double *ans1, double *ans2, FILE *input);


int main(int argc, char *argv[]){

    int error_code = processCMDArgs(argc, argv);
    printErrors(error_code);

    return checkErrors(error_code);
}

enum CODE_ERRORS processCMDArgs(int argc, char *argv[]){

    if(argc > 1){
        if(*argv[1] == 'f'){
            return fileMode();

        }else if(*argv[1] == 'r'){
            return randMode();

        }else if(*argv[1] == 'm'){
            return manualMode();

        }else if(*argv[1] == 't'){
            return unitTests();
        }
    }

    return CMD_arg_incorrect;
}

enum CODE_ERRORS getCoefficients(double *a, double *b, double *c, FILE *input){
    assert(input);
    int x = 0;
    if((x = fscanf(input, "%lf %lf %lf", a, b, c)) == 3 && getc(input) == '\n'){
        return correct;
    }else{
        if(x == EOF){
            return end_of_file;
        }else{
            return incorrect_data_format;
        }
    }
}

enum CODE_ERRORS getCoeffAndAns(double *a, double *b, double *c, enum NUMBER_OF_ROOTS *n_o_r, double *ans1, double *ans2, FILE *input){
    assert(input);
    int x = 0;
    int n_o_r_int = -1;
    if((fscanf(input, "%lf %lf %lf %d %lf %lf", a, b, c, &n_o_r_int, ans1, ans2)) == 6 && (x = getc(input)) == '\n'){
        intToSwitch(n_o_r, n_o_r_int);
        return correct;
    }else{
        if(x == EOF){
            intToSwitch(n_o_r, n_o_r_int);
            return end_of_file;
        }else{
            return incorrect_data_format;
        }
    }
}

enum CODE_ERRORS randMode(){

    printf("Enter the number of equations: ");

    int n = 0;
    scanf("%d", &n);
    printf("\n");

    if(n > 0){
        double a = 0, b = 0, c = 0;

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

enum CODE_ERRORS manualMode(){

    double a = 0, b = 0, c = 0;

    printf("The program for solving square equation, please print a, b, c: \n\n");

    enum CODE_ERRORS error_code = correct;

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

enum CODE_ERRORS fileMode(){

    double a = 0, b = 0, c = 0;

    FILE *input_file = NULL;

    enum CODE_ERRORS error_code = correct;

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
//Дает unit тесты функции unitTest
enum CODE_ERRORS unitTests(){
    printf("Do you want read tests from file or enter tests from CMD? f/c:");
    int s = getchar();
    while(s != 'f' && s != 'c'){
        clearBuf();
        printf("\nOutput is wrong, please enter f/c:");
        s = getchar();
    }
    printf("\n");
    FILE *input = stdin;
    enum CODE_ERRORS error_code = correct;
    if(s == 'f'){
        if((error_code = enterFileName(&input)) != correct)
            return error_code;
    }
    //Взяли input
    double a = 0, b = 0, c = 0, ans1_ref = 0, ans2_ref = 0;
    enum NUMBER_OF_ROOTS n_o_r_ref = no_roots;
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
//Проверяет систему на конкретном уравнении
enum SUCCESS_RATE    unitTest(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r_ref, double ans1_ref, double ans2_ref, int num_of_test){
    double ans1 = 0, ans2 = 0;
    enum NUMBER_OF_ROOTS n_o_r = solveSquareEq(a, b, c, &ans1, &ans2);
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
          "got:         %d roots, x1 = %lg, x2 = %lg\n", num_of_test, a, b, c, n_o_r_ref, ans1_ref, ans2_ref, n_o_r, ans1, ans2);
    return error;
}

enum CALC_ERRORS     testingTheSolution(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r, double ans1, double ans2){
    double d = 0;
    switch (n_o_r){
        case two_roots:
            if(isRootCorrect(a, b, c, ans1) && isRootCorrect(a, b, c, ans2))
                return no_calc_error;
            break;
        case one_root:
            if(isRootCorrect(a, b, c, ans1) ^ isRootCorrect(a, b, c, ans2))
                return no_calc_error;
            break;
        case no_roots:
            d = b * b - 4 * a * c;
            if((isZero(a) && isZero(b) && (!isZero(c))) || ((!isZero(d)) && d < 0))
                return no_calc_error;
            break;
        case infinity_roots:
            if(isZero(a) && isZero(b) && isZero(c))
                return no_calc_error;
            break;
        default:
            assert(0 && "Incorrect number of roots");
    }
    printCalcError(a, b, c, n_o_r, ans1, ans2);
    return calc_error;
}

void                 printCalcError(double a, double b, double c, enum NUMBER_OF_ROOTS n_o_r, double ans1, double ans2){
    printf("Error during equation solving:\nCoefficients: %lg %lg %lg\nOutput:\n", a, b, c);
    printRoots(n_o_r, ans1, ans2);
}

enum CODE_ERRORS     enterFileName(FILE **input_file){
    char file_name[WORD_LEN] = {};
    printf("Enter file name: ");
    int n = 0;
    scanf("%s%n", file_name, &n); // another func from std
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

void                 solveAndPrint(double a, double b, double c){

    double ans1 = 0, ans2 = 0;

    NUMBER_OF_ROOTS num_of_roots = solveSquareEq(a, b, c, &ans1, &ans2);

    switch(testingTheSolution(a, b, c, num_of_roots, ans1, ans2)){
        case no_calc_error:
            printRoots(num_of_roots, ans1, ans2);
            break;
        case calc_error:
            break;
        default:
            assert(0 && "Incorrect calc error");
    }
}

enum NUMBER_OF_ROOTS solveSquareEq(double a, double b, double c, double *ans1, double *ans2){

    assert(ans1 != NULL);
    assert(ans2 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    *ans1 = NAN;
    *ans2 = NAN;

    if(isZero(a)){//Линейное уравнение
        return linearEq(b, c, ans1);

    }else{//Квадратное уравнение
        return squareEq(a, b, c, ans1, ans2);

    }
}

enum NUMBER_OF_ROOTS linearEq(double b, double c, double *ans1){

    if(isZero(b)){
        return isZero(c) ? infinity_roots : no_roots;

    }else{
        if(isZero(c)){
            *ans1 = 0;

        }else{
            *ans1 = -1*((c)/(b));

        }
        return one_root;

    }
}

enum NUMBER_OF_ROOTS squareEq(double a, double b, double c, double *ans1, double *ans2){

    double d = (b * b) - 4 * (a * c);

    if(isZero(d)){
        *ans1 = (-b)/(2 * a);
        return one_root;

    }else if(d < 0){
        return no_roots;

    }else{
        double s_d = sqrt(d);
        *ans1 = (-b - s_d)/(2 * a);
        *ans2 = (-b + s_d)/(2 * a);
        return two_roots;

    }
}

void                 printRoots(enum NUMBER_OF_ROOTS num_of_roots, double ans1, double ans2){

    switch(num_of_roots){
        case no_roots:
            printf("There is no roots\n");
            break;

        case one_root:
            printf("%-15.10lg\n", ans1);
            break;

        case two_roots:
            printf("%-15.10lg %-15.10lg\n", ans1, ans2);
            break;

        case infinity_roots:
            printf("Infinity number of roots\n");
            break;

        default:
            assert(0 && "Incorrect number of roots");

    }
    printf("\n");
}

int                  checkErrors(int error_code){

    return !(error_code == correct);
}

void                 printErrors(int error_code){

    switch(error_code){
        case correct:
            break;

        case CMD_arg_incorrect:
            printf("CMD argument is incorrect\n\n");
            break;

        case long_file_name:
            printf("The file name is too long\n\n");
            break;

        case incorrect_file_name:
            printf("There is no file with this name\n\n");
            break;

        case incorrect_data_format:
            printf("The data format is incorrect\n\n");
            break;

        case incorrect_number_of_equations:
            printf("Incorrect for number od equations\n\n");

        default:
            ;
    }
}

int                  isZero(double x){

    return fabs(x) < EPSILON;
}

void                 getRandCoefficients(double *a, double *b, double *c){
 // how to solve
    *a = rand()%2001 - 1000;
    *b = rand()%2001 - 1000;
    *c = rand()%2001 - 1000;
}

void                 clearBuf(){

    int c = 0;
    while(((c = getc(stdin)) != EOF) && (c != '\n'));
}

int                  isRootCorrect(double a, double b, double c, double root){

    return isZero(a * pow(root, 2) + b * root + c);
}

enum SUCCESS_RATE    intToSwitch(enum NUMBER_OF_ROOTS *n_o_r, int n_o_r_int){
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
            assert(0 && "Incorrect number of roots");
    }
    return success;
}
