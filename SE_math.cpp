void            solveAndPrint(double a, double b, double c);                                                       //Решает уравнение и выводит корни
NUMBER_OF_ROOTS solveSquareEq(double a, double b, double c, double *ans1, double *ans2);                           //Решает частный случай гарантированно квадратного уравнения
NUMBER_OF_ROOTS linearEq(double b, double c, double *ans1);                                                        //Решает частный случай вырожденного уравнения
NUMBER_OF_ROOTS squareEq(double a, double b, double c, double *ans1, double *ans2);                                //Решает квадратное уравнение в общем случае
void            printRoots(NUMBER_OF_ROOTS num_of_roots, double ans1, double ans2);                                //Напечатать корни в терминал
int             isRootCorrect(double a, double b, double c, double root);                                          //Проверяет корни подстановкой
int             isZero(double x);                                                                                  //Сравнение с нулем
SUCCESS_RATE    testingTheSolution(double a, double b, double c, NUMBER_OF_ROOTS n_o_r, double ans1, double ans2); //Тестирование подстановкой
void            printCalcError(double a, double b, double c, NUMBER_OF_ROOTS n_o_r, double ans1, double ans2);     //Вывод ошибки после подстановки



void            solveAndPrint(double a, double b, double c){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));


    double ans1 = 0, ans2 = 0;

    NUMBER_OF_ROOTS num_of_roots = solveSquareEq(a, b, c, &ans1, &ans2);

    switch(testingTheSolution(a, b, c, num_of_roots, ans1, ans2)){
        case success:
            printRoots(num_of_roots, ans1, ans2);
            break;
        case error:
            break;
        default:
            assert(0 && "Incorrect calc error");
    }
}

NUMBER_OF_ROOTS solveSquareEq(double a, double b, double c, double *ans1, double *ans2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(ans1 != NULL);
    assert(ans2 != NULL);

    *ans1 = NAN;
    *ans2 = NAN;

    if(isZero(a)){//Линейное уравнение
        return linearEq(b, c, ans1);
    }else{//Квадратное уравнение
        return squareEq(a, b, c, ans1, ans2);
    }
}

NUMBER_OF_ROOTS linearEq(double b, double c, double *ans1){

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

NUMBER_OF_ROOTS squareEq(double a, double b, double c, double *ans1, double *ans2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(ans1 != NULL);
    assert(ans2 != NULL);

    *ans1 = NAN;
    *ans2 = NAN;

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

void            printRoots(NUMBER_OF_ROOTS num_of_roots, double ans1, double ans2){



    switch(num_of_roots){
        case no_roots:
            assert(isnan(ans1));
            assert(isnan(ans2));
            printf("There is no roots\n");
            break;

        case one_root:
            assert(isfinite(ans1));
            assert(isnan(ans2));
            printf("%-15.10lg\n", ans1);
            break;

        case two_roots:
            assert(isfinite(ans1));
            assert(isfinite(ans2));
            printf("%-15.10lg %-15.10lg\n", ans1, ans2);
            break;

        case infinity_roots:
            assert(isnan(ans1));
            assert(isnan(ans2));
            printf("Infinity number of roots\n");
            break;

        default:
            assert(0 && "Incorrect number of roots");

    }
    printf("\n");
}

int             isRootCorrect(double a, double b, double c, double root){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(root));

    return isZero(a * pow(root, 2) + b * root + c);
}

int             isZero(double x){

    assert(isfinite(x));
    assert(!isnan(x));

    return fabs(x) < EPSILON;
}

SUCCESS_RATE     testingTheSolution(double a, double b, double c, NUMBER_OF_ROOTS n_o_r, double ans1, double ans2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d = 0;
    switch (n_o_r){
        case two_roots:
            assert(isfinite(ans1));
            assert(isfinite(ans2));
            if(isRootCorrect(a, b, c, ans1) && isRootCorrect(a, b, c, ans2))
                return success;
            break;
        case one_root:
            assert(isfinite(ans1));
            assert(isnan(ans2));
            if(isRootCorrect(a, b, c, ans1))
                return success;
            break;
        case no_roots:
            assert(isnan(ans1));
            assert(isnan(ans2));
            d = b * b - 4 * a * c;
            if((isZero(a) && isZero(b) && (!isZero(c))) || ((!isZero(d)) && d < 0))
                return success;
            break;
        case infinity_roots:
            assert(isnan(ans1));
            assert(isnan(ans2));
            if(isZero(a) && isZero(b) && isZero(c))
                return success;
            break;
        default:
            assert(0 && "Incorrect number of roots");
    }
    printCalcError(a, b, c, n_o_r, ans1, ans2);
    return error;
}

void            printCalcError(double a, double b, double c, NUMBER_OF_ROOTS n_o_r, double ans1, double ans2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(ans1));
    assert(isfinite(ans2));

    printf("Error during equation solving:\nCoefficients: %lg %lg %lg\nOutput:\n", a, b, c);
    printRoots(n_o_r, ans1, ans2);
}
