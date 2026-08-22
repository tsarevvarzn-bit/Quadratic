#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

const int WORD_LEN = 100;
const double eps = 0.0001;
const char ESC[] = "esc";

enum {no_roots = 0, one_root = 1, two_roots = 2, infinity_roots = 3}; //Что выводить при отсутствии корней, одном, двух и бесконечном количестве корней
enum {correct, CMD_arg_incorrect, long_file_name, incorrect_file_name, incorrect_data_format, incorrect_number_of_equations, end_of_file}; //Что возвращать функциям в случае ошибки и в случае, когда она отработала хорошо

// snake_case
// pascalCase
// CamelCase
// CAPS_CASE

int processCMDArgs(int argc, char *argv[]);
void printErrors(int error_code);
void printRoots(int num_of_roots, double ans1, double ans2);                         //Напечатать корни в терминал
void solveAndPrint(double a, double b, double c);                                    //Решает уравнение и выводит корни
int solveSquareEq(double a, double b, double c, double *ans1, double *ans2);         //Решает частный случай гарантированно квадратного уравнения
int linearEq(double b, double c, double *ans1);                                      //Решает частный случай вырожденного уравнения
int squareEq(double a, double b, double c, double *ans1, double *ans2);              //Решает квадратное уравнение в общем случае
int getCoeffs(double *a, double *b, double *c, FILE *input);                         //Взять 3 числа из FILE*, если NULL => генерируем рандомные
int enterFileName(FILE **input_file);
int manualMode();
int fileMode();
int randMode();
int isZero(double x);
int checkErrors(int error_code);
void getRandCoeffs(double *a, double *b, double *c);
void ClearBuf(FILE *input);

int main(int argc, char *argv[]){
    int error_code = processCMDArgs(argc, argv);
    printErrors(error_code);
    return checkErrors(error_code);
}

int processCMDArgs(int argc, char *argv[]){
    if(argc > 1){
        if(*argv[1] == 'f'){
            return fileMode();
        }else if(*argv[1] == 'r'){
            return randMode();
        }else if(*argv[1] == 'm'){
            return manualMode();
        }
    }
    return CMD_arg_incorrect;
}

int getCoeffs(double *a, double *b, double *c, FILE *input){
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

int randMode(){
    printf("Enter the number of equations: ");
    int n = 0;
    scanf("%d", &n);
    if(n > 0){
        double a = 0, b = 0, c = 0;
        for(int i = 0; i < n; i++){
            getRandCoeffs(&a, &b, &c);
            printf("Roots for %lf %lf %lf:\n", a, b, c);
            solveAndPrint(a, b, c);
        }
        return correct;
    }else{
        return incorrect_number_of_equations;
    }
}
//В ручном режиме добавить попытку ввода нормальных значений после ввода мусора
int manualMode(){
    double a = 0, b = 0, c = 0;

    printf("The program for solving square equation, please print a, b, c: \n");

    int error_code = correct;

    while((error_code = getCoeffs(&a, &b, &c, stdin)) != end_of_file){
        if(error_code == correct){
            solveAndPrint(a, b, c);
        }else if(error_code == incorrect_data_format){
            a = b = c = 0;
            ClearBuf(stdin);
            printf("Incorrect input, try again\n");
        }else{
            return error_code;
        }
    }
    return error_code;
}

int fileMode(){
    double a = 0, b = 0, c = 0;
    FILE *input_file = NULL;
    int error_code = correct;
    if((error_code = enterFileName(&input_file)) != correct){
        return error_code;
    }
    while((error_code = getCoeffs(&a, &b, &c, input_file)) == correct){
        printf("Roots for %lg %lg %lg:\n", a, b, c);
        solveAndPrint(a, b, c);
    }
    if(error_code == end_of_file){
        solveAndPrint(a, b, c);
    }

    return error_code;
}

int enterFileName(FILE **input_file){
    char file_name[WORD_LEN] = {};
    printf("Enter file name: ");
    int n = 0;
    scanf("%99s%n", file_name, &n);
    if(n >= WORD_LEN){
        return long_file_name;
    }
    *input_file = fopen(file_name, "r");
    if(*input_file == NULL){
        return incorrect_file_name;
    }
    return correct;
}

void solveAndPrint(double a, double b, double c){
    double ans1 = 0, ans2 = 0;
    int num_of_roots = solveSquareEq(a, b, c, &ans1, &ans2);
    printRoots(num_of_roots, ans1, ans2);
}

int solveSquareEq(double a, double b, double c, double *ans1, double *ans2){
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

int linearEq(double b, double c, double *ans1){
    if(isZero(b)){
        return isZero(c) ? infinity_roots : no_roots;
    }else{
        *ans1 = -1*((c)/(b));
        return one_root;
    }
}

int squareEq(double a, double b, double c, double *ans1, double *ans2){
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

void printRoots(int num_of_roots, double ans1, double ans2){
    switch(num_of_roots){
        case no_roots:
            printf("There is no roots\n");
            break;
        case one_root:
            printf("%-15.10lf\n", ans1);
            break;
        case two_roots:
            printf("%-15.10lf %-15.10lf\n", ans1, ans2);
            break;
        case infinity_roots:
            printf("Infinity number of roots\n");
            break;
        default:
            assert(0 && "Non-standart output of solveSquareEq");
    }
    printf("\n");
}

int checkErrors(int error_code){
    if(error_code == correct){
        return 0;
    }
    return 1;
}

void printErrors(int error_code){
    switch(error_code){
        case correct:
            break;
        case CMD_arg_incorrect:
            printf("CMD argument is incorrect\n");
            break;
        case long_file_name:
            printf("The file name is too long\n");
            break;
        case incorrect_file_name:
            printf("There is no file with this name\n");
            break;
        case incorrect_data_format:
            printf("The data format is incorrect\n");
            break;
        case incorrect_number_of_equations:
            printf("Incorrect for number od equations\n");
        default:
            ;
    }
}

int isZero(double x){
    return fabs(x) < eps;
}

void getRandCoeffs(double *a, double *b, double *c){
    *a = rand()%2001 - 1000;
    *b = rand()%2001 - 1000;
    *c = rand()%2001 - 1000;
}

void ClearBuf(FILE *file){
    int c = 0;
    while(((c = getc(file)) != EOF) && (c != '\n'));
}
