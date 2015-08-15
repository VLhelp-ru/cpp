/*
***** COPYRIGHT: VLhelp.ru / program@vlhelp.ru *****

Библиотека комплексных чисел на Си с использованием структур.
Операции: +, -, /, *, сопряженное, модуль, аргумент, поворот, возведение в степень, получение действительной и мнимой части

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// структура для комплексных чисел
typedef struct{
    double real, img; // действительная и мнимая части числа
} complex;

// вывод действительной части
void print_real(complex c){
    printf("real=%lf\n", c.real);
}

// вывод мнимой части
void print_img(complex c){
    printf("img=%lf\n", c.img);
}

// сложение
complex sum(complex a, complex b){
    complex c;
    c.real = a.real + b.real;
    c.img = a.img + b.img;
    return c;
}

// вычитание
complex subtract(complex a, complex b){
    complex c;
    c.real = a.real - b.real;
    c.img = a.img - b.img;
    return c;
}

// умножение
complex mult(complex a, complex b){
    complex c;
    c.real = a.real*b.real - a.img*b.img;
    c.img = a.img*b.real + a.real*b.img;
    return c;
}

// деление
complex divide(complex a, complex b){
    complex c;
    if (b.real == 0 && b.img == 0){ // исключаем деление на ноль
        return c;
    }
    c.real = (a.real*b.real + a.img*b.img) / (b.real*b.real + b.img*b.img);
    c.img = (b.real*a.img - b.img*a.real) / (b.real*b.real + b.img*b.img);
    return c;
}

// сопряженное
complex conjugate(complex c){
    complex cc;
    cc.real = c.real;
    cc.img = -c.img;
    return cc;
}

// модуль
double module(complex c){
    return sqrt(c.real*c.real + c.img*c.img);
}

// аргумент
double argument(complex c){
    return c.img / c.real;
}

// поворот
// алгоритм: поворот комплексного числа z=x+yi на угол a равносилен умножению его на комплексное число cos(a) + i*sin(a)
complex turn(complex c, int angle){
    complex result, _mult;
    _mult.real = cos(angle);
    _mult.img = sin(angle);
    result = mult(c, _mult);
    return result;
}

// степень
complex power(complex c, int _power){
    complex result;
    result.real = 0;
    result.img = 0;
    if (c.real || c.img){
        double r = pow(module(c), _power); // возведим модуль в квадрат
        double cos_phi = c.real / r; // вычисляем косинус "фи"
        double phi = acos(cos_phi); // вычисляем "фи"
        result.real = r * cos(_power * phi); // вычисляем действительную часть
        result.img = r * sin(_power * phi); // вычисляем мнимую часть
    }
    return result;
}

int main()
{
    int choice, _angle, _power;
    complex a, b, c;
    double tmp;

    while (1){
        printf("Press 1 to add two complex numbers.\n");
        printf("Press 2 to subtract two complex numbers.\n");
        printf("Press 3 to multiply two complex numbers.\n");
        printf("Press 4 to divide two complex numbers.\n");
        printf("Press 5 to get conjugate of complex number.\n");
        printf("Press 6 to get module of complex number.\n");
        printf("Press 7 to get argument of complex number.\n");
        printf("Press 8 to turn complex number.\n");
        printf("Press 9 to power complex number.\n");
        printf("Press 0 to exit.\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        if(choice == 0){
            exit(0);
        }

        if(choice >= 1 && choice <= 4) {
            printf("Enter a and b where a + ib is the first complex number.");
            printf("\na = ");
            scanf("%lf", &a.real);
            printf("b = ");
            scanf("%lf", &a.img);
            printf("Enter c and d where c + id is the second complex number.");
            printf("\nc = ");
            scanf("%lf", &b.real);
            printf("d = ");
            scanf("%lf", &b.img);
        } else if (choice >= 5 && choice <= 9) {
            printf("Enter a and b where a + ib is a complex number.");
            printf("\na = ");
            scanf("%lf", &a.real);
            printf("b = ");
            scanf("%lf", &a.img);
        }

        if (choice == 8) {
            printf("Enter an angle for turning a complex number.");
            printf("\na = ");
            scanf("%d", &_angle);
        } else if (choice == 9) {
            printf("Enter a power for a complex number.");
            printf("\na = ");
            scanf("%d", &_power);
        }

        if (choice == 1) {
            c = sum(a, b);
            if (c.img >= 0){
                printf("Sum of two complex numbers = %lf + %lfi\n",c.real,c.img);
            } else {
                printf("Sum of two complex numbers = %lf %lfi\n",c.real,c.img);
            }
        } else if (choice == 2) {
            c = subtract(a, b);
            if (c.img >= 0) {
                printf("Difference of two complex numbers = %lf + %lfi\n",c.real,c.img);
            } else {
                printf("Difference of two complex numbers = %lf %lfi\n",c.real,c.img);
            }
        } else if (choice == 3) {
            c = mult(a, b);
            if (c.img >= 0) {
                printf("Multiplication of two complex numbers = %lf + %lfi\n",c.real,c.img);
            } else {
                printf("Multiplication of two complex numbers = %lf %lfi\n",c.real,c.img);
            }
        } else if (choice == 4) {
            if (b.real == 0 && b.img == 0){
                printf("Division by 0 + 0i is not allowed.\n");
            } else {
                c = divide(a, b);
                printf("Division of two complex numbers = %lf + %lfi\n",c.real,c.img);
            }
        } else if (choice == 5) {
            c = conjugate(a);
            printf("Conjugate of complex number = %lf + %lfi\n",c.real,c.img);
        } else if (choice == 6) {
            tmp = module(a);
            printf("Module of complex number = %lf\n",tmp);
        } else if (choice == 7) {
            tmp = argument(a);
            printf("Argument of complex number = %lf\n",tmp);
        } else if (choice == 8) {
            c = turn(a, _angle);
            printf("Turn of complex number = %lf + %lfi\n",c.real,c.img);
        } else if (choice == 9) {
            c = power(a, _power);
            printf("Power of complex number = %lf + %lfi\n",c.real,c.img);
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
