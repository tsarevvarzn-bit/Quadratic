void            solveAndPrint(coefficients coefficients);                                                       //Решает уравнение и выводит корни
NUMBER_OF_ROOTS solveSquareEquation(coefficients coefficients, double *ans1, double *ans2);                     //Решает частный случай гарантированно квадратного уравнения
NUMBER_OF_ROOTS solveLinearEq(double b, double c, double *ans1);                                                   //Решает частный случай вырожденного уравнения
NUMBER_OF_ROOTS solveSquareEq(coefficients coefficients, double *ans1, double *ans2);                           //Решает квадратное уравнение в общем случае
void            printRoots(roots roots);                                //Напечатать корни в терминал
int             isRootCorrect(coefficients coefficients, double root);                                          //Проверяет корни подстановкой
int             isZero(double x);                                                                                  //Сравнение с нулем
SUCCESS_RATE    testTheSolution(coefficients coefficients, roots roots);    //Тестирование подстановкой
void            printCalcError(coefficients coefficients, roots roots);     //Вывод ошибки после подстановки



void            solveAndPrint(coefficients coefficients){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));

    roots roots = {};
    roots.ans1 = roots.ans2 = NAN;

    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));

    switch(testTheSolution(coefficients, roots)){
        case success:
            printRoots(roots);
            break;
        case error:
            break;
        default:
            assert(0 && "Incorrect calc error");
    }
}

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
    }else{//Квадратное уравнение
        return solveSquareEq(coefficients, ans1, ans2);
    }
}

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
        return one_root;

    }else if(d < 0){
        return no_roots;

    }else{
        double s_d = sqrt(d);
        *ans1 = (-1 * coefficients.b - s_d)/(2 * coefficients.a);
        *ans2 = (-1 * coefficients.b + s_d)/(2 * coefficients.a);
        return two_roots;
    }
}

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
            printf("%-15.10lg\n", roots.ans1);
            break;

        case two_roots:
            assert(isfinite(roots.ans1));
            assert(isfinite(roots.ans2));
            printf("%-15.10lg %-15.10lg\n", roots.ans1, roots.ans2);
            break;

        case infinity_roots:
            assert(isnan(roots.ans1));
            assert(isnan(roots.ans2));
            printf("Infinity number of roots\n");
            break;

        default:
            assert(0 && "Incorrect number of roots");

    }
    printf("\n");
}

int             isRootCorrect(coefficients coefficients, double root){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(isfinite(root));

    return isZero(coefficients.a * pow(root, 2) + coefficients.b * root + coefficients.c);
}

int             isZero(double x){

    assert(isfinite(x));
    assert(!isnan(x));

    return fabs(x) < EPSILON;
}

SUCCESS_RATE     testTheSolution(coefficients coefficients, roots roots){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));

    double d = 0;

    switch (roots.n_o_r){
        case two_roots:
            assert(isfinite(roots.ans1));
            assert(isfinite(roots.ans2));
            if(isRootCorrect(coefficients, roots.ans1) && isRootCorrect(coefficients, roots.ans2))
                return success;
            break;
        case one_root:
            assert(isfinite(roots.ans1));
            assert(isnan(roots.ans2));
            if(isRootCorrect(coefficients, roots.ans1))
                return success;
            break;
        case no_roots:
            assert(isnan(roots.ans1));
            assert(isnan(roots.ans2));
            d = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;
            if((isZero(coefficients.a) && isZero(coefficients.b) && (!isZero(coefficients.c))) || ((!isZero(d)) && d < 0))
                return success;
            break;
        case infinity_roots:
            assert(isnan(roots.ans1));
            assert(isnan(roots.ans2));
            if(isZero(coefficients.a) && isZero(coefficients.b) && isZero(coefficients.c))
                return success;
            break;
        default:
            assert(0 && "Incorrect number of roots");
    }
    printCalcError(coefficients, roots);
    return error;
}

void            printCalcError(coefficients coefficients, roots roots){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(isfinite(roots.ans1));
    assert(isfinite(roots.ans2));

    printf("Error during equation solving:\nCoefficients: %lg %lg %lg\nOutput:\n", coefficients.a, coefficients.b, coefficients.c);
    printRoots(roots);
}
