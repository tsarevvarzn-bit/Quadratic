/// @file




//! @brief Solves a quadratic equation ax2 + bx + c = 0 and print the roots in CMD
//!
//! @param [in] coefficients the structure that contains the coefficients of the equation
//!
//! @note Calls
void            solveAndPrint(coefficients coefficients){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));

    roots roots = {};
    roots.ans1 = roots.ans2 = NAN;

    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));

    testCase test_case = {.coefficients = coefficients, .roots = roots};

    switch(testTheSolution(test_case)){
        case success:
            printRoots(roots);
            break;
        case error:
            printCalcError(test_case);
            break;
        default:
            ERROR_MASSAGE("Incorrect calc error");
    }
}

//! @brief Solves a quadratic equation ax2 + bx + c = 0
//!
//! @param [in] coefficients the structure that contains the coefficients of the equation
//!
//! @param [in] ans1 a pointer to a variable to put the first root in
//! @param [in] ans2 a pointer to a variable to put the second root in
//!
//! @note If there are no roots, nan is placed in ans1 and ans2, if there is one root, it is placed in ans1, nan in ans2,
//!       if there are two roots, the smaller one is placed in ans1, the larger one in ans2.
//!
//! @return an enum that indicates the number of roots
NUMBER_OF_ROOTS solveSquareEquation(coefficients coefficients, double *ans1, double *ans2){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(ans1 != NULL);
    assert(ans2 != NULL);

    *ans1 = NAN;
    *ans2 = NAN;

    if(isZero(coefficients.a)){//Линейное уравнение
        return solveLinearEq(coefficients.b, coefficients.c, ans1);
    }else{                     //Квадратное уравнение
        return solveSquareEq(coefficients, ans1, ans2);
    }
}

//! @brief Solves a special case of a quadratic equation in which it is guaranteed that a = 0
//!
//! @param [in] b the variable that contains the  second coefficients of the equation
//! @param [in] c the variable that contains the third coefficients of the equation
//!
//! @param [in] ans1 a pointer to a variable to put the root in
//!
//! @note If there are no roots, nan is placed in ans1, if there is one root, it is placed in ans1
//!
//! @return an enum that indicates the number of roots
NUMBER_OF_ROOTS solveLinearEq(double b, double c, double *ans1){

    assert(isfinite(b));
    assert(isfinite(c));

    assert(ans1 != NULL);
    *ans1 = NAN;

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

//! @brief Solves a special case of a quadratic equation in which it is guaranteed that a is not equal to 0
//!
//! @param [in] coefficients the structure that contains the coefficients of the equation
//!
//! @param [in] ans1 a pointer to a variable to put the first root in
//! @param [in] ans2 a pointer to a variable to put the second root in
//!
//! @note If there are no roots, nan is placed in ans1 and ans2, if there is one root, it is placed in ans1, nan in ans2,
//!       if there are two roots, the smaller one is placed in ans1, the larger one in ans2.
//!
//! @return an enum that indicates the number of roots
NUMBER_OF_ROOTS solveSquareEq(coefficients coefficients, double *ans1, double *ans2){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));

    assert(ans1 != NULL);
    assert(ans2 != NULL);

    *ans1 = NAN;
    *ans2 = NAN;

    double d = (coefficients.b * coefficients.b) - 4 * (coefficients.a * coefficients.c);

    if(isZero(d)){
        *ans1 = (-1 * coefficients.b)/(2 * coefficients.a);
        if(isZero(*ans1))
            *ans1 = 0;
        return one_root;

    }else if(d < 0){
        return no_roots;

    }else{
        double s_d = sqrt(d);
        if(coefficients.a > 0){
            *ans1 = (-1 * coefficients.b - s_d)/(2 * coefficients.a);
            *ans2 = (-1 * coefficients.b + s_d)/(2 * coefficients.a);
        }else{
            *ans2 = (-1 * coefficients.b - s_d)/(2 * coefficients.a);
            *ans1 = (-1 * coefficients.b + s_d)/(2 * coefficients.a);
        }

        return two_roots;
    }
}



//! @brief checks the root by substituting into the equation
//!
//! @param [in] coefficients the structure that contains the coefficients of the equation
//!
//! @param [in] root the root that needs to be checked
//!
//! @return 1 if the root is correct, otherwise 0
int             isRootCorrect(coefficients coefficients, double root){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(isfinite(root));

    return isZero(coefficients.a * pow(root, 2) + coefficients.b * root + coefficients.c);
}
//Default comment


//! @brief checks whether a number lies in the vicinity of EPSILON (const) from zero
//!
//!
//! @param [in] x the number we are checking
//!
//! @note it is necessary to correct the error when calculating the double
//!
//! @return 1 if x lies in the vicinity of EPSILON (const) from zero, otherwise 0
int             isZero(double x){

    assert(isfinite(x));
    assert(!isnan(x));
    assert(true);

    return fabs(x) < EPSILON;
}

//! @brief Checks the solution of a quadratic equation by substitution
//!
//! @param [in] testCase the struct which contains the coefficients of the equation and the roots
//!
//! @return success if solution correct, otherwise 0
SUCCESS_RATE     testTheSolution(testCase testCase){

    assert(isfinite(testCase.coefficients.a));
    assert(isfinite(testCase.coefficients.b));
    assert(isfinite(testCase.coefficients.c));
    assert(isRootsFormatCorrect(testCase.roots));

    double d = 0;

    switch (testCase.roots.n_o_r){
        case two_roots:
            assert(isfinite(testCase.roots.ans1));
            assert(isfinite(testCase.roots.ans2));

            if(isRootCorrect(testCase.coefficients, testCase.roots.ans1) && isRootCorrect(testCase.coefficients, testCase.roots.ans2))
                return success;
            break;
        case one_root:
            assert(isfinite(testCase.roots.ans1));
            assert(isnan(testCase.roots.ans2));

            if(isRootCorrect(testCase.coefficients, testCase.roots.ans1))
                return success;
            break;
        case no_roots:
            assert(isnan(testCase.roots.ans1));
            assert(isnan(testCase.roots.ans2));

            d = testCase.coefficients.b * testCase.coefficients.b - 4 * testCase.coefficients.a * testCase.coefficients.c;

            if((isZero(testCase.coefficients.a) && isZero(testCase.coefficients.b) && (!isZero(testCase.coefficients.c))) || ((!isZero(d)) && d < 0))
                return success;
            break;
        case infinity_roots:
            assert(isnan(testCase.roots.ans1));
            assert(isnan(testCase.roots.ans2));

            if(isZero(testCase.coefficients.a) && isZero(testCase.coefficients.b) && isZero(testCase.coefficients.c))
                return success;
            break;
        default:
            ERROR_MASSAGE("Incorrect number of roots");
    }

    return error;
}



//! @brief get derivative
//!
//! @param [in] func_coefficients the struct which contains the coefficients of function
//!
//! @return the struct der_coefficients which contains the coefficients of the derivative function
coefficients getDerivative(coefficients func_coefficients){

    coefficients der_coefficients = {};
    der_coefficients.b = func_coefficients.a * 2;
    der_coefficients.c = func_coefficients.b;

    return der_coefficients;
}

//! @brief Check the roots for the correct format
//!
//! @param [in] roots the struct which contains roots
//!
//! @return 1 if roots format is correct, otherwise 0
int isRootsFormatCorrect(roots roots){

    switch(roots.n_o_r){
        case no_roots:
            return 1;
        case one_root:
            return isfinite(roots.ans1) ? 1 : 0;
        case two_roots:
            return (isfinite(roots.ans1) && isfinite(roots.ans2)) ? 1 : 0;
        case infinity_roots:
            return 1;
        default:
            ERROR_MASSAGE("Incorrect number of roots");
    }
}

//! @brief It takes integer number and converts it to the corresponding enum
//!
//! @param [out] n_o_r a pointer to the enum to which the function will write the result.
//!
//! @param [in]  n_o_r_int the number we want to convert to enum
//!
//! @return Success if there is an enum corresponding to the given number, otherwise error
SUCCESS_RATE    transformIntToSwitch(NUMBER_OF_ROOTS *n_o_r, int n_o_r_int){

    const int no_roots_code       = (int) no_roots;
    const int one_root_code       = (int) one_root;
    const int two_roots_code      = (int) two_roots;
    const int infinity_roots_code = (int) infinity_roots;

    switch(n_o_r_int){
        case no_roots_code:
            *n_o_r = no_roots;
            break;
        case one_root_code:
            *n_o_r = one_root;
            break;
        case two_roots_code:
            *n_o_r = two_roots;
            break;
        case infinity_roots_code:
            *n_o_r = infinity_roots;
            break;
        default:
            return error;
    }
    return success;
}

//! @brief Return random number
//!
//! @param [in] roots struct that contains data about the roots
//!
//! @return random double number from range [RAND_MIN, RAND_MAX]
double getRandNumber(){
    return ((((double)rand())/RAND_MAX) * (MAX_RAND - MIN_RAND)) + MIN_RAND;
}

//! @brief Generated random coefficients
//!
//! @param [out] coefficients a pointer to the structure where the random coefficients will be placed
void            getRandCoefficients(coefficients *coefficients){

    assert(coefficients != NULL);

    coefficients->a = getRandNumber();
    coefficients->b = getRandNumber();
    coefficients->c = getRandNumber();
}
