void exploreFunction(coefficients coefficients, FILE *out);

void exploreParabola(coefficients coefficients, FILE *out);
void exploreLine(coefficients coefficients, FILE *out);
void exploreHorizontal(coefficients coefficients, FILE *out);


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

void exploreParabola(coefficients coefficients, FILE *out){

    assert(!isZero(coefficients.a));

    assert(out != NULL);

    fprintf(out, CYAN  "\n0)" DEFAULT " Graph is parabola: " YELLOW "y = (%.5lg) * x^2 + (%.5lg) * x + (%.5lg)\n" DEFAULT, coefficients.a, coefficients.b, coefficients.c);

    fprintf(out, CYAN  "1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);

    double top_x = ((-1 * coefficients.b) / (2 * coefficients.a));
    double top_y = coefficients.a * pow(top_x, 2) + coefficients.b * top_x + coefficients.c;

    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW);
    if(coefficients.a > 0){
        fprintf(out, "(%.5lg, +INF)\n" DEFAULT, top_y);
    }else{
        fprintf(out, "{-INF, %.5lg}\n" DEFAULT, top_y);
    }


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(roots.n_o_r == no_roots){
        if(coefficients.a > 0){
            fprintf(out,         "                    +                     \n");
        }else{
            fprintf(out,         "                    -                     \n");
        }
            fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
            fprintf(out, YELLOW  "                                          \n");

    }else if(roots.n_o_r == one_root){
        if(coefficients.a > 0){
            fprintf(out,         "            +              +              \n");
        }else{
            fprintf(out,         "            -              -              \n");
        }

            fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
            fprintf(out, YELLOW  "                    %.5lg                 \n", roots.ans1);

    }else{
        if(coefficients.a > 0){
            fprintf(out,         "         +          -          +          \n");
        }else{
            fprintf(out,         "         -          +          -          \n");
        }
            fprintf(out, DEFAULT "-INF <--------0-----------0---------> +INF\n");
            fprintf(out, YELLOW  "              %.5lg       %lg             \n", roots.ans1, roots.ans2);

    }


    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);
    if(isZero(coefficients.b)){
        fprintf(out, "y' = (%.5lg) * x\n", coefficients.a);
    }else{
        fprintf(out, "y' = (%.5lg) * x + (%.5lg)\n", coefficients.a, coefficients.b);
    }


    fprintf(out, CYAN "7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(coefficients.a > 0){
        fprintf(out,         "            -               +             \n");
    }else{
        fprintf(out,         "            +               -             \n");
    }

        fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
        fprintf(out, YELLOW  "                    %.5lg                 \n", top_x);


    fprintf(out, CYAN "8)" DEFAULT " Minimum and maximum points of the function:\n" YELLOW);
    if(coefficients.a > 0){
        fprintf(out, DEFAULT "\tMinimum point (top of the parabola) " YELLOW "(%.5lg, %.5lg)\n" DEFAULT, top_x, top_y);
        fprintf(out, DEFAULT "\tThere is no maximum point\n\n" DEFAULT);
    }else{
        fprintf(out, DEFAULT "\tMaximum point (top of the parabola) " YELLOW "(%.5lg, %.5lg)\n\n" DEFAULT, top_x, top_y);
        fprintf(out, DEFAULT "\tThere is no minimum point\n" DEFAULT);
    }

}


void exploreLine(coefficients coefficients, FILE *out){

    assert(isZero(coefficients.a));
    assert(!isZero(coefficients.b));

    assert(out != NULL);

    fprintf(out, CYAN "\n0) " DEFAULT "Graph is line: " YELLOW "y = (%.5lg) * x + (%.5lg)\n" DEFAULT, coefficients.b, coefficients.c);


    fprintf(out, CYAN "1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW "{-INF, +INF}\n" DEFAULT);


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(coefficients.b > 0){
        fprintf(out,         "            -                +            \n");
    }else{
        fprintf(out,         "            +                -            \n");
    }
        fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
        fprintf(out, YELLOW  "                    %.5lg                  \n", roots.ans1);


    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %.5lg)\n" DEFAULT, coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);
    fprintf(out, "y' = (%.5lg)\n", coefficients.b);



    fprintf(out, CYAN "7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(coefficients.b > 0){
        fprintf(out,         "                   +                      \n");
    }else{
        fprintf(out,         "                   -                      \n");
    }

        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");


    fprintf(out, CYAN "8)" DEFAULT " There is no minimum and maximum of function\n\n" YELLOW);

}

void exploreHorizontal(coefficients coefficients, FILE *out){

    assert(isZero(coefficients.a));
    assert(isZero(coefficients.b));

    assert(out != NULL);

    fprintf(out, CYAN "\n0) " DEFAULT "Graph is horizontal line: " YELLOW "y = %.5lgy\n" DEFAULT, coefficients.c);


    fprintf(out, CYAN "1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN "2) " DEFAULT "Y in interval " YELLOW "{%.5lg}\n" DEFAULT, coefficients.c);


    fprintf(out, CYAN "3) " DEFAULT "Roots:\n\t" YELLOW);
    roots roots = {};
    roots.n_o_r = solveSquareEquation(coefficients, &(roots.ans1), &(roots.ans2));
    printRoots(roots);


    fprintf(out, CYAN  "4) " DEFAULT "Y sign:\n" YELLOW);
    if(coefficients.c > 0){
        fprintf(out,         "                    +                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }else if(coefficients.c < 0){
        fprintf(out,         "                    -                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }else{
        fprintf(out,         "                    0                     \n");
        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");
    }



    fprintf(out, CYAN "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, coefficients.c);


    fprintf(out, CYAN "6) " DEFAULT "The derivative:\n\t" YELLOW);
    fprintf(out, "y' = 0\n");



    fprintf(out, CYAN "7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(coefficients.b > 0){
        fprintf(out,         "                   0                      \n");
    }else{
        fprintf(out,         "                   0                      \n");
    }

        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");


    fprintf(out, CYAN "8)" DEFAULT " There is no minimum and maximum of function\n\n" YELLOW);
}









