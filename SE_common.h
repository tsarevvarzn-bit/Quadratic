/// @brief Print error massage and end the program
#define ERROR_MASSAGE(str)      printf("\nERROR MASSAGE: %s, file %s, function: %s, line %d", str, __FILE__, __func__, __LINE__); \
                                abort()

/// @brief Maximum number of symbols, that we can read and save
/// @note This is necessary to ensure security when entering text, to avoid the error of overflowing the array
const int     WORD_LEN = 100;

/// @brief If the user has entered too many equations, we ask him if he is sure
/// @note Generating and solving more than 1000 equations takes a sufficient amount of time, if the user makes a mistake, the program can enter an endless loop
const int     MAXIMUM_NUMBER_OF_RANDOM_EQUATIONS = 1000;

/// @brief The calculation error we assume is used to compare the numbers in the function isZero()
const double  EPSILON = 0.0001;

/// @brief The maximum number that the function getRandNumber() can output
const double  MAX_RAND = 100000;

/// @brief The minimum number that the function getRandNumber() can output
const double  MIN_RAND = -100000;

const int     WIDTH = 91;

const int     HEIGHT = 41;

const double  MAX_SCALE = 1000;

const double  MIN_SCALE = 0.1;

const int     NUMBER_OF_DIGIT_TO_PRINT = 5;

const int     NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OX = 10;

const int     NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OY = 5;

const int     NUMBER_OF_DIGIT_IN_DOUBLE = 20;

/// @brief Enum for transmitting the number of roots
enum NUMBER_OF_ROOTS {
    no_roots,                        //!< There is no real roots
    one_root,                        //!< There is only one real root
    two_roots,                       //!< There is two different real roots
    infinity_roots                   //!<Any real number is a root
};

/// @brief Enum to return the error with which the program ended or information that the program worked without errors
/// @note "correct" and "end_of_file" are also in the enum, but they are signals about the correct operation of the program.
enum CODE_ERRORS     {
    correct,                         //!< The program or function worked without errors
    CMD_arg_incorrect,               //!< The command line argument written when calling the program is incorrect
    long_file_name,                  //!< The file name written by the user is too long
    incorrect_file_name,             //!< The program cannot find and open a file with that name
    incorrect_data_format,           //!< The data received from the user has an incorrect format
    incorrect_number_of_equations,   //!< The user entered an incorrect number indicating the number of equations that need to be generated and solved
    end_of_file,                     //!< The file has been completely read, no more data can be taken from there.
    not_a_finite_number_in_the_input,//!< The data received from the user include nan, inf or -inf insted of finite number
    incorrect_number_of_roots,       //!< The number indicating the number of roots entered by the user is not included in the allowed set {0, 1, 2, 3}
    could_not_allocate_memory
};

/// @brief Enum to return success rate of called function
enum SUCCESS_RATE    {
    success = 0,                     //!< The function worked correctly
    error = 1                        //!< The function worked with an error
};

/// @brief Enum to store the coefficients of a particular quadratic equation
struct coefficients  {
    double a;                        //!< The number that stands before x^2 in the above equation is ax^2+bx+c=0
    double b;                        //!< The number that stands before x in the above equation is ax^2+bx+c=0
    double c;                        //!< Free coefficient in the above equation is ax^2+bx+c=0
};

/// @brief Struct that stores the complete solution of a particular quadratic equation

struct roots         {
    NUMBER_OF_ROOTS n_o_r;           //!< The number of real roots
    double          ans1;            //!< The smallest root in the case of two roots, the value of the single root, if there is one, otherwise - nan
    double          ans2;            //!< The largest root is if there are two different real numbers, otherwise - nan
};

/// @brief Struct that stores coefficients and the solution of a specific equation

struct testCase       {
    coefficients    coefficients;    //!< Enum to store the coefficients of a particular quadratic equation
    roots           roots;           //!< Struct that stores the complete solution of a particular quadratic equation
};

struct canvasConfig   {
    double scale_x;
    double scale_y;
    double x_shift; //Сдвиг центральной точки
    double y_shift;
};
struct canvas         {
    int    width;
    int    height;
    canvasConfig config;
    char** data;   // data[width][height]
};






#define DEFAULT "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define VIOLET  "\033[1;35m"
#define CYAN    "\033[1;36m"



//SE.cpp
CODE_ERRORS     processCMDArgs(int argc, char *argv[]);                                            //Функции, вызывающиеся всегда и из main
void            printErrors(CODE_ERRORS error_code);

//SE_modes.h
CODE_ERRORS     runManualMode();                                                                   //Основные режимы работы
CODE_ERRORS     runFileMode();
CODE_ERRORS     runRandMode();
CODE_ERRORS     runUnitTests();
CODE_ERRORS     runHelpMode();

SUCCESS_RATE    runOneUnitTest(testCase testCase, int num_of_test);
CODE_ERRORS     runIntegratedTests();


//SE_input_output.h
void            clearBuf(FILE *input);
int             checkTerminalForYes();
unsigned int    getSeed();
CODE_ERRORS     checkInputOnEnter(FILE *input);

CODE_ERRORS     runUsersTests(FILE *input);
void            getRandCoefficients(coefficients *coefficients);
CODE_ERRORS     getCoefficients(coefficients *coefficients, FILE *input);
CODE_ERRORS     getCoeffAndAns(testCase *testCase, FILE *input);

CODE_ERRORS     enterFileName(FILE **input_file);
CODE_ERRORS     getInputForRunUnitTests(FILE **input, int *isIntegratedTests);
void            printUnitTestResult(SUCCESS_RATE s_r, testCase testCase, roots roots, int num_of_test);
void            printRoots(roots roots);                                                           //Напечатать корни в терминал

//SE_math.h
void            solveAndPrint(coefficients coefficients);                                          //Решает уравнение и выводит корни
NUMBER_OF_ROOTS solveSquareEquation(coefficients coefficients, double *ans1, double *ans2);        //Решает квадратное уравнение в общем случае
NUMBER_OF_ROOTS solveLinearEq(double b, double c, double *ans1);                                   //Решает частный случай вырожденного уравнения
NUMBER_OF_ROOTS solveSquareEq(coefficients coefficients, double *ans1, double *ans2);              //Решает частный случай гарантированно квадратного уравнения

coefficients    getDerivative(coefficients func_coefficients);

int             isRootCorrect(coefficients coefficients, double root);                             //Проверяет корни подстановкой
int             isZero(double x);                                                                  //Сравнение с нулем
SUCCESS_RATE    testTheSolution(testCase testCase);                                                //Тестирование подстановкой
void            printCalcError(testCase testCase);                                                 //Вывод ошибки после подстановки
double          calculateTheFunctionValue(coefficients coefficients, double x);

int             isRootsFormatCorrect(roots roots);
double          getRandNumber();
SUCCESS_RATE    transformIntToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int);

double          max(double a, double b);
double          min(double a, double b);

//SE_explore.cpp
void            exploreFunction(coefficients coefficients, FILE *out);

void            exploreParabola(coefficients coefficients, FILE *out);
void            exploreLine(coefficients coefficients, FILE *out);
void            exploreHorizontal(coefficients coefficients, FILE *out);

void            printFunction(coefficients coefficients, FILE *out);
void            printNumWithSign(double x);

CODE_ERRORS            printGraphOfFunction(FILE* out, coefficients coefficients);

CODE_ERRORS     canvasCreate(canvas** canvas_p_p, int width, int height);
void            canvasPrint(canvas* canvas_p, FILE* out);
void            canvasFree(canvas* canvas_p);

void            canvasPrintAxis(canvas* canvas_p);
void            canvasPrintGraph(canvas* canvas_p, coefficients coefficients);
void            canvasPrintFunctionPoints(canvas* canvas_p, coefficients coefficients);
void            canvasPrintAxisDesignations(canvas* canvas_p);

void            canvasSetSymbol(canvas* canvas_p, int x, int y, char c);
void            canvasSetMathDot(canvas *canvas_p, double mat_x, double mat_y, char c);

void            canvasGetConfig(canvas* canvas_p, coefficients coefficients);
int             functionValueSymbol(canvas* canvas_p, coefficients coefficients, double x);

void            canvasPrintDouble(canvas* canvas_p, int x_symbol, int y_symbol, double number);
void            canvasPrintConfig(canvas* canvas_p);
