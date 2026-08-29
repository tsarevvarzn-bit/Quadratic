/// @file

CODE_ERRORS exploreFunction(coefficients coefficients, FILE *out){

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

    return printGraphOfFunction(stdout, coefficients);

}

void exploreParabola(coefficients func_coefficients, FILE *out){

    assert(!isZero(func_coefficients.a));

    assert(out != NULL);

    double top_x = ((-1 * func_coefficients.b) / (2 * func_coefficients.a));
    double top_y = func_coefficients.a * pow(top_x, 2) + func_coefficients.b * top_x + func_coefficients.c;

    fprintf(out, CYAN  "\n0)" DEFAULT " Graph is parabola: ");
    printFunction(func_coefficients, stdout);


    fprintf(out, CYAN  "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN  "2) " DEFAULT "Y in interval " YELLOW);
    if(func_coefficients.a > 0){
        fprintf(out, "(%.5lg, +INF)\n" DEFAULT, top_y);
    }else{
        fprintf(out, "{-INF, %.5lg}\n" DEFAULT, top_y);
    }


    fprintf(out, CYAN  "3) " DEFAULT "Roots:\n\t" YELLOW);
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


    fprintf(out, CYAN  "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN  "6) " DEFAULT "The derivative:\n\t" YELLOW);
    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);


    fprintf(out, CYAN  "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);

    if(func_coefficients.a > 0){
        fprintf(out,         "            -               +             \n");
    }else{
        fprintf(out,         "            +               -             \n");
    }

        fprintf(out, DEFAULT "-INF <--------------0---------------> +INF\n");
        fprintf(out, YELLOW  "                    %.5lg                 \n", top_x);


    fprintf(out, CYAN  "8)" DEFAULT " Minimum and maximum points of the function:\n" YELLOW);
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

    fprintf(out, CYAN  "\n0) " DEFAULT "Graph is line: ");
    printFunction(func_coefficients, stdout);


    fprintf(out, CYAN  "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN  "2) " DEFAULT "Y in interval " YELLOW "{-INF, +INF}\n" DEFAULT);


    fprintf(out, CYAN  "3) " DEFAULT "Roots:\n\t" YELLOW);
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


    fprintf(out, CYAN  "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %.5lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN  "6) " DEFAULT "The derivative:\n\t" YELLOW);
    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);



    fprintf(out, CYAN  "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);
    if(func_coefficients.b > 0){
        fprintf(out,         "                   +                      \n");
    }else{
        fprintf(out,         "                   -                      \n");
    }

        fprintf(out, DEFAULT "-INF <------------------------------> +INF\n");
        fprintf(out, YELLOW  "                                          \n");


    fprintf(out, CYAN  "8)" DEFAULT " There is no minimum and maximum of function\n\n" DEFAULT);

}

void exploreHorizontal(coefficients func_coefficients, FILE *out){

    assert(isZero(func_coefficients.a));
    assert(isZero(func_coefficients.b));

    assert(out != NULL);

    fprintf(out, CYAN  "\n0) " DEFAULT "Graph is horizontal line: ");
    printFunction(func_coefficients, stdout);


    fprintf(out, CYAN  "\n1) " DEFAULT "X in interval " YELLOW "(-INF, +INF)\n" DEFAULT);


    fprintf(out, CYAN  "2) " DEFAULT "Y in interval " YELLOW "{%.5lg}\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN  "3) " DEFAULT "Roots:\n\t" YELLOW);
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



    fprintf(out, CYAN  "5) " DEFAULT "Itersection with OY: " YELLOW "(0, %lg)\n" DEFAULT, func_coefficients.c);


    fprintf(out, CYAN  "6) " DEFAULT "The derivative:\n\t" YELLOW);
    coefficients der_coefficients = {.a = 0, .b = 0, .c = 0};
    der_coefficients = getDerivative(func_coefficients);
    printFunction(der_coefficients, stdout);


    fprintf(out, CYAN  "\n7) " DEFAULT "Intervals of ascending (y' > 0) and descending (y' < 0):\n" YELLOW);
    fprintf(out,            "                   0                      \n");
    fprintf(out, DEFAULT    "-INF <------------------------------> +INF\n");
    fprintf(out, YELLOW     "                                          \n");


    fprintf(out, CYAN  "8)" DEFAULT " There is no minimum and maximum of function\n\n" DEFAULT);
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

CODE_ERRORS printGraphOfFunction(FILE* out, coefficients coefficients){

    assert(out);
    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));

    printf(CYAN "9)" DEFAULT "Graph\n");

    canvas* canvas_p = NULL;

    CODE_ERRORS error_code = correct;

    if((error_code = canvasCreate(&canvas_p, WIDTH, HEIGHT)) != correct)
        return error_code;

    canvasGetConfig(canvas_p, coefficients);

    canvasPrintConfig(canvas_p);

    canvasPrintAxis(canvas_p);

    canvasPrintFunctionPoints(canvas_p, coefficients);

    canvasPrintAxisDesignations(canvas_p);

    canvasPrint(canvas_p, out);

    canvasFree(canvas_p);

    return correct;
}

// Создание холста, все ячейки заполняются пробелами
CODE_ERRORS canvasCreate(canvas** canvas_p_p, int width, int height) {

    assert(canvas_p_p);
    assert(width > 0);
    assert(height > 0);

    canvas *new_canvas_p = (canvas*)calloc(1, sizeof(canvas));

    if ( !new_canvas_p)
        return could_not_allocate_memory;

    new_canvas_p->width = width;
    new_canvas_p->height = height;

    new_canvas_p->data = (char**)calloc(height, sizeof(char*));

    if ( !new_canvas_p->data) {
        free(new_canvas_p);
        return could_not_allocate_memory;
    }

    for (int y = 0; y < height; y++) {

        new_canvas_p->data[y] = (char*)calloc(width, sizeof(char));

        if ( !new_canvas_p->data[y]) {

            for (int i = 0; i < y; i++){
                free(new_canvas_p->data[i]);
            }

            free(new_canvas_p->data);
            free(new_canvas_p);

            return could_not_allocate_memory;
        }

        for(int i = 0; i < width; i++){
            new_canvas_p->data[y][i] = ' ';
        }
    }

    new_canvas_p->config.scale_x = 1;
    new_canvas_p->config.scale_y = 1;
    new_canvas_p->config.x_shift = 0;
    new_canvas_p->config.y_shift = 0;

    *canvas_p_p = new_canvas_p;//Должны вернуть указатель на новый холст -> обращаемся по указателю на указатель
}

// Освобождение холста
void canvasFree(canvas *canvas_p) {

    assert(canvas_p);

    for (int y = 0; y < canvas_p->height; y++) {
        free(canvas_p->data[y]);
    }

    free(canvas_p->data);
    free(canvas_p);
}

// Установка символа в точке (x, y)
void canvasSetSymbol(canvas *canvas_p, int x, int y, char c) {//Печатает относительно центра (canvas_p->width/2, canvas_p->height/2) -> (0,0),

    assert(canvas_p);

    if (x < -1 * (canvas_p->width / 2) || x >= (canvas_p->width / 2) || y < -1 * (canvas_p->height / 2) || y >= (canvas_p->height / 2)){
        return;
    }
    canvas_p->data[y + (canvas_p->height / 2)][x + (canvas_p->width / 2)] = c;
}

// Печать холста в консоль (ось Y направлена вверх)
void canvasPrint(canvas *canvas_p, FILE* out) {//Передаем указатель на структуру

    assert(canvas_p);
    assert(out);

    for (int y = canvas_p->height - 1; y >= 0; y--) {//Печатем сверху вниз
        for (int x = 0; x < canvas_p->width; x++) {
            putc(canvas_p->data[y][x], out);
        }
        putc('\n', out);
    }
}

void canvasPrintAxis(canvas *canvas_p){

    assert(canvas_p);

    int oy_shift_in_symbols = (int) (canvas_p->config.x_shift / canvas_p->config.scale_x);//Насколько символов вправо
    int ox_shift_in_symbols = (int) (canvas_p->config.y_shift / canvas_p->config.scale_y);//Насколько символов вверх

    for(int x = -(canvas_p->width / 2); x < (canvas_p->width / 2); x++){
        canvasSetSymbol(canvas_p, x, ox_shift_in_symbols, '-');
    }

    for(int y = -(canvas_p->height / 2); y < (canvas_p->height / 2); y++){
        canvasSetSymbol(canvas_p, oy_shift_in_symbols, y, '|');
    }

    canvasSetSymbol(canvas_p, oy_shift_in_symbols, ox_shift_in_symbols, '+');

    return correct;
}

void canvasPrintFunctionPoints(canvas* canvas_p, coefficients coefficients){

    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(canvas_p);

    //Крайние, допустимые значения:
    int mat_x_min = (int) (-(canvas_p->width  / 2)      * (canvas_p->config.scale_x) - canvas_p->config.x_shift);

    int symbol_x_max = (int) ((canvas_p->width  / 2) - 1);
    int symbol_x_min = (int) -(canvas_p->width  / 2);
    int symbol_y_max = (int) ((canvas_p->height / 2) - 1);
    int symbol_y_min = (int) -(canvas_p->height / 2);

    int function_value_symbol = 0;
    int next_function_value_symbol = functionValueSymbol(canvas_p, coefficients, mat_x_min);

    for(int x_symbol = symbol_x_min; x_symbol <= symbol_x_max; x_symbol++){//Перебираем символы относительно абсолютного центра

        double x_math = (x_symbol * canvas_p->config.scale_x) - canvas_p->config.x_shift;
        function_value_symbol = next_function_value_symbol;
        next_function_value_symbol = functionValueSymbol(canvas_p, coefficients, x_math + canvas_p->config.scale_x);

        if( ! ((next_function_value_symbol < symbol_y_min &&  function_value_symbol < symbol_y_min) ||
               (next_function_value_symbol      > symbol_y_max &&  function_value_symbol > symbol_y_max))){//Если это значение и следующее находятся в одной мертвой зоне - не печатаем

            canvasSetSymbol(canvas_p, x_symbol, function_value_symbol, '#');

            if(next_function_value_symbol - function_value_symbol > 1){
                for(int y = function_value_symbol + 1; y < next_function_value_symbol; y++){
                    canvasSetSymbol(canvas_p, x_symbol + 1, y, '#');
                }
            }else if(function_value_symbol - next_function_value_symbol > 1){
                for(int y = function_value_symbol - 1; y > next_function_value_symbol; y--){
                    canvasSetSymbol(canvas_p, x_symbol, y, '#');
                }
            }
        }
    }
}

void canvasPrintAxisDesignations(canvas* canvas_p){

    assert(canvas_p);

    int oy_shift_in_symbols = (int) (canvas_p->config.x_shift / canvas_p->config.scale_x);//Насколько символов вправо отодвинута ось
    int ox_shift_in_symbols = (int) (canvas_p->config.y_shift / canvas_p->config.scale_y);//Насколько символов вверх отодвинута ось

    canvasSetSymbol(canvas_p, (canvas_p->width / 2) - 1,        ox_shift_in_symbols, '>');
    canvasSetSymbol(canvas_p, (canvas_p->width / 2) - 1,      ox_shift_in_symbols-1, 'X');
    canvasSetSymbol(canvas_p,       oy_shift_in_symbols, (canvas_p->height / 2) - 1, '^');
    canvasSetSymbol(canvas_p,   oy_shift_in_symbols + 1, (canvas_p->height / 2) - 1, 'Y');

    int symbol_x_max = (int) ((canvas_p->width  / 2) - 1);
    int symbol_x_min = (int) -(canvas_p->width  / 2);
    int symbol_y_max = (int) ((canvas_p->height / 2) - 1);
    int symbol_y_min = (int) -(canvas_p->height / 2);

    int ox_symbol = (int) (canvas_p->config.y_shift / canvas_p->config.scale_y);
    int oy_symbol = (int) (canvas_p->config.x_shift / canvas_p->config.scale_x);

    //Оцифровка OX:
    for(int x_symbol = oy_shift_in_symbols + NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OX; x_symbol < symbol_x_max - 5; x_symbol += NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OX){

        canvasSetSymbol(canvas_p, x_symbol, ox_symbol, '+');
        canvasPrintDouble(canvas_p, x_symbol, ox_symbol - 1, (x_symbol - oy_shift_in_symbols) * canvas_p->config.scale_x);
    }
    for(int x_symbol = oy_shift_in_symbols - NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OX; x_symbol > symbol_x_min; x_symbol -= NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OX){

        canvasSetSymbol(canvas_p, x_symbol, (int) (canvas_p->config.y_shift / canvas_p->config.scale_y), '+');
        canvasPrintDouble(canvas_p, x_symbol, ox_symbol - 1, (x_symbol - oy_shift_in_symbols) * canvas_p->config.scale_x);
    }

    //Оцифровка OY:
    for(int y_symbol = ox_shift_in_symbols + NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OY; y_symbol < symbol_y_max; y_symbol += NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OY){

        canvasSetSymbol(canvas_p, oy_symbol, y_symbol, '+');
        canvasPrintDouble(canvas_p, oy_symbol + 1, y_symbol, (y_symbol - ox_shift_in_symbols) * canvas_p->config.scale_y);
    }
    for(int y_symbol = ox_shift_in_symbols - NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OY; y_symbol >= symbol_y_min; y_symbol -= NUMBER_OF_CHARACTER_BETWEEN_NUMBERS_OY){

        canvasSetSymbol(canvas_p, oy_symbol, y_symbol, '+');
        canvasPrintDouble(canvas_p, oy_symbol + 1, y_symbol, (y_symbol - ox_shift_in_symbols) * canvas_p->config.scale_y);
    }
}

void canvasGetConfig(canvas* canvas_p, coefficients func_coefficients){

    assert(canvas_p);
    assert(isfinite(func_coefficients.a));
    assert(isfinite(func_coefficients.b));
    assert(isfinite(func_coefficients.c));

    if(isZero(func_coefficients.a)){

        if(isZero(func_coefficients.b)){

            if( !isZero(func_coefficients.c)){
                canvas_p->config.scale_y = min(max(0.1, fabs(func_coefficients.c) / (canvas_p->height / 4.0)), MAX_SCALE);
            }

        }else{

            double intersection_with_oy = func_coefficients.c;
            double intersection_with_ox = -1 * (func_coefficients.c / func_coefficients.b);

            canvas_p->config.scale_y = min(max(0.1, (max(fabs(intersection_with_oy), fabs(intersection_with_ox)) / (canvas_p->height / 4.0))), MAX_SCALE);
            canvas_p->config.scale_x = canvas_p->config.scale_y;

            //Масштабируем, чтобы четко видеть два пересечения

            if(intersection_with_oy > 0){
                canvas_p->config.y_shift = -((canvas_p->height / 4.0) * canvas_p->config.scale_y);
            }else if(intersection_with_oy < 0){
                canvas_p->config.y_shift = (canvas_p->height / 4.0) * canvas_p->config.scale_y;
            }

            if(intersection_with_ox > 0){
                canvas_p->config.x_shift = -((canvas_p->height / 4.0) * canvas_p->config.scale_x);
            }else if(intersection_with_ox < 0){
                canvas_p->config.x_shift = (canvas_p->height / 4.0) * canvas_p->config.scale_x;
            }
        }

    }else{

        double top_x = ((-1 * func_coefficients.b) / (2 * func_coefficients.a));
        double top_y = func_coefficients.a * pow(top_x, 2) + func_coefficients.b * top_x + func_coefficients.c;

        //Вершина параболы должна умещаться в квадратик canvas_p->width/4 и canvas_p->height/4

        canvas_p->config.scale_y = min(max(MIN_SCALE, (max(fabs(top_x), fabs(top_y)) / (canvas_p->height / 4.0))), MAX_SCALE);

        //Расширяем ее, чтобы она была похожа на параболу (ветви расходились хотя бы на width/4)

        double branch_1 = 0;
        double branch_2 = 0;

        coefficients coefficients_for_branches = func_coefficients;

        if(func_coefficients.a > 0){

            coefficients_for_branches.c = coefficients_for_branches.c - ((canvas_p->height / 2) - 1) * canvas_p->config.scale_y;

        }else{
            coefficients_for_branches.c = coefficients_for_branches.c + ((canvas_p->height / 2) - 1) * canvas_p->config.scale_y;
        }

        solveSquareEquation(coefficients_for_branches, &branch_1, &branch_2);


        canvas_p->config.scale_x = (branch_2 - branch_1) / (canvas_p->width  / 4.0);



        if(func_coefficients.a > 0 and top_y >= 0){

            canvas_p->config.y_shift = -((canvas_p->height / 4.0) * canvas_p->config.scale_y);

        }else if(func_coefficients.a < 0 and top_y <= 0){

            canvas_p->config.y_shift = (canvas_p->height / 4.0) * canvas_p->config.scale_y;
        }

        canvas_p->config.x_shift = max(min((canvas_p->width / 2.0) * canvas_p->config.scale_x, -top_x), -(canvas_p->width / 2.0) * canvas_p->config.scale_x);

        //Сдвигаем экран по Oy на 1/4 если парабола находиться в одной половине графика, по Ox вершина в середине, но видна хотя бы 1/4 от каждой четверти

    }
}

int functionValueSymbol(canvas* canvas_p, coefficients coefficients, double x){

    assert(canvas_p);
    assert(isfinite(coefficients.a));
    assert(isfinite(coefficients.b));
    assert(isfinite(coefficients.c));
    assert(isfinite(x));

    double function_value = coefficients.a * pow(x, 2) + coefficients.b * x + coefficients.c;
    return (int) ((function_value + canvas_p->config.y_shift) / canvas_p->config.scale_y);
}

void canvasPrintDouble(canvas* canvas_p, int x_symbol, int y_symbol, double number){

    assert(canvas_p);
    assert(isfinite(number));

    int integer_part = (int) fabs(number);

    int number_of_digits_befor_point = 0;
    while(integer_part > 0){
        integer_part = integer_part / 10;
        number_of_digits_befor_point++;
    }

    int number_multiplied = (int) (fabs(number) * pow(10, NUMBER_OF_DIGIT_TO_PRINT));


    char number_mas[NUMBER_OF_DIGIT_IN_DOUBLE] = {};

    char number_of_reads_digits = 0;
    while(number_multiplied > 0){
        number_mas[NUMBER_OF_DIGIT_IN_DOUBLE - 1 - number_of_reads_digits] = (char) (number_multiplied % 10);
        number_multiplied = number_multiplied / 10;
        number_of_reads_digits++;
    }

    char number_of_characters_written = 0;
    char number_of_digits_written = 0;
    char there_is_dot = 0;

    if(number < 0){
        canvasSetSymbol(canvas_p, x_symbol, y_symbol, '-');
        number_of_characters_written++;
    }

    if(number_of_digits_befor_point == 0){
        canvasSetSymbol(canvas_p, x_symbol, y_symbol, '0');
        number_of_characters_written++;
    }

    while(number_of_characters_written < NUMBER_OF_DIGIT_TO_PRINT){

        if(number_of_digits_written == number_of_digits_befor_point && !there_is_dot){

            if(number_of_characters_written == NUMBER_OF_DIGIT_TO_PRINT - 1){
                return;
            }

            canvasSetSymbol(canvas_p, x_symbol + number_of_characters_written, y_symbol, '.');
            there_is_dot = 1;

        }else{

            canvasSetSymbol(canvas_p, x_symbol + number_of_characters_written, y_symbol, '0' + number_mas[(NUMBER_OF_DIGIT_IN_DOUBLE - number_of_reads_digits) + number_of_digits_written]);
            number_of_digits_written++;

        }
        number_of_characters_written++;
    }

}

void canvasPrintConfig(canvas* canvas_p){

    assert(canvas_p);

    printf(YELLOW "\tScale: x: " CYAN "%.5lg" YELLOW " y: " CYAN "%.5lg\n" DEFAULT, canvas_p->config.scale_x, canvas_p->config.scale_y);
    printf(YELLOW "\tShift: x: " CYAN "%.5lg" YELLOW " y: " CYAN "%.5lg\n" DEFAULT, canvas_p->config.x_shift, canvas_p->config.y_shift);
}

