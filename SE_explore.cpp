void exploreFunction(coefficients coefficients, FILE *out);

void exploreParabola(coefficients coefficients, FILE *out);
void exploreLine(coefficients coefficients, FILE *out);
void exploreHorizontal(coefficients coefficients, FILE *out);

void printFunction(coefficients coefficients, FILE *out);
void printNumWithSign(double x);


void exploreFunction(coefficients coefficients, FILE *out){

    assert(out);

    if(isZero(coefficients.a)){
        if(isZero(coefficients.b)){
            exploreHorizontal(coefficients, out);
        }else{
            exploreLine(coefficients, out);
        }
    }else{
        exploreParabola(coefficients, out);
    }
}

void exploreParabola(coefficients func_coefficients, FILE *out){

    assert(!isZero(func_coefficients.a));

    assert(out != NULL);

    fprintf(out, CYAN  "\n0)" DEFAULT " Graph is parabola: ");
    printFunction(func_coefficients, stdout);

    fprintf(out, CYAN  "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);

    double top_x = ((-1 * func_coefficients.b) / (2 * func_coefficients.a));
    double top_y = func_coefficients.a * pow(top_x, 2) + func_coefficients.b * top_x + func_coefficients.c;

    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW);
    if(func_coefficients.a > 0){
        fprintf(out, "(%.5lg, +INF)\n" DEFAULT, top_y);
    }else{
        fprintf(out, "{-INF, %.5lg}\n" DEFAULT, top_y);
    }


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(func_coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(roots.n_o_r == no_roots){
        if(func_coefficients.a > 0){
            fprintf(out,         "                    +                     \n");
        }else{
            fprintf(out,         "                    -                     \n");
        }
            fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
            fprintf(out, YELLOW  "                                          \n");

    }else if(roots.n_o_r == one_root){
        if(func_coefficients.a > 0){
            fprintf(out,         "            +              +              \n");
        }else{
            fprintf(out,         "            -              -              \n");
        }

            fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
            fprintf(out, YELLOW  "                    %.5lg                 \n", roots.ans1);

    }else{
        if(func_coefficients.a > 0){
            fprintf(out,         "         +          -          +          \n");
        }else{
            fprintf(out,         "         -          +          -          \n");
        }
            fprintf(out, DEFAULT "-INF <--------0-----------0---------> +INF\n");
            fprintf(out, YELLOW  "              %.5lg       %lg             \n", roots.ans1, roots.ans2);

    }


    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);


    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);
    // if(isZero(func_coefficients.b)){
    //     fprintf(out, "y' = (%.5lg) * x\n", (func_coefficients.a * 2));
    // }else{
    //     fprintf(out, "y' = (%.5lg) * x + (%.5lg)\n", (func_coefficients.a * 2), func_coefficients.b);
    // }


    fprintf(out, CYAN "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(func_coefficients.a > 0){
        fprintf(out,         "            -               +             \n");
    }else{
        fprintf(out,         "            +               -             \n");
    }

        fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
        fprintf(out, YELLOW  "                    %.5lg                 \n", top_x);


    fprintf(out, CYAN "8)" DEFAULT " Minimum and maximum points of the function:\n" YELLOW);
    if(func_coefficients.a > 0){
        fprintf(out, DEFAULT "\tMinimum point (top of the parabola) " YELLOW "(%.5lg, %.5lg)\n" DEFAULT, top_x, top_y);
        fprintf(out, DEFAULT "\tThere is no maximum point\n\n" DEFAULT);
    }else{
        fprintf(out, DEFAULT "\tMaximum point (top of the parabola) " YELLOW "(%.5lg, %.5lg)\n" DEFAULT, top_x, top_y);
        fprintf(out, DEFAULT "\tThere is no minimum point\n\n" DEFAULT);
    }

}


void exploreLine(coefficients func_coefficients, FILE *out){

    assert(isZero(func_coefficients.a));
    assert(!isZero(func_coefficients.b));

    assert(out != NULL);

    fprintf(out, CYAN "\n0) " DEFAULT "Graph is line: ");

    printFunction(func_coefficients, stdout);


    fprintf(out, CYAN "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW "{-INF, +INF}\n" DEFAULT);


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(func_coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(func_coefficients.b > 0){
        fprintf(out,         "            -                +            \n");
    }else{
        fprintf(out,         "            +                -            \n");
    }
        fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
        fprintf(out, YELLOW  "                    %.5lg                  \n", roots.ans1);


    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %.5lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);
    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);



    fprintf(out, CYAN "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(func_coefficients.b > 0){
        fprintf(out,         "                   +                      \n");
    }else{
        fprintf(out,         "                   -                      \n");
    }

        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");


    fprintf(out, CYAN "8)" DEFAULT " There is no minimum and maximum of function\n\n" YELLOW);

}

void exploreHorizontal(coefficients func_coefficients, FILE *out){

    assert(isZero(func_coefficients.a));
    assert(isZero(func_coefficients.b));

    assert(out != NULL);

    fprintf(out, CYAN "\n0) " DEFAULT "Graph is horizontal line: ");

    printFunction(func_coefficients, stdout);


    fprintf(out, CYAN "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW "{%.5lg}\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(func_coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(func_coefficients.c > 0){
        fprintf(out,         "                    +                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }else if(func_coefficients.c < 0){
        fprintf(out,         "                    -                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }else{
        fprintf(out,         "                    0                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }



    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);
    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);



    fprintf(out, CYAN "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);
    fprintf(out,         "                   0                      \n");
    fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
    fprintf(out, YELLOW  "                                          \n");


    fprintf(out, CYAN "8)" DEFAULT " There is no minimum and maximum of function\n\n" YELLOW);
}

void printFunction(coefficients coefficients, FILE *out){

    if(isZero(coefficients.a)){
        if(isZero(coefficients.b)){
            fprintf(out, YELLOW "y = " CYAN "%.8lg", coefficients.c);

        }else{
            fprintf(out, YELLOW "y = " CYAN "%.8lg" YELLOW "x ", coefficients.b);
            printNumWithSign(coefficients.c);
        }
    }else{
        fprintf(out, YELLOW "y = " CYAN "%.8lg" YELLOW "x^2 ", coefficients.a);
        printNumWithSign(coefficients.b);
        fprintf(out, YELLOW "x ");
        printNumWithSign(coefficients.c);
    }
}

void printNumWithSign(double x){
    if(x >= 0){
        printf(YELLOW "+ " CYAN "%.8lg" YELLOW, x);
    }else{
        double minx = -1 * x;
        printf(CYAN "- " CYAN "%.8lg" YELLOW, minx);
    }
}








