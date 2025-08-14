#include<TXLib.h>
#include<stdio.h>
#include<math.h>
int input_1(double *kef_a,double *kef_b,double *kef_c);
void output_1(double sol1, double sol2, int cas);
int solver(double kef_a,double kef_b,double kef_c, double *sol1, double *sol2);
int main(void)
{
    double kef_a, kef_b, kef_c;
    double sol1 = 0;
    double sol2 = 0;
    int pruf = 1;
    int prov, cas;
    printf("Эта программа решает уравнения вида ax^2+bx+c=0\n");
    do
    {
        prov = 1;
        printf("Введите параметры уравнения:\n");
        prov = input_1(&kef_a, &kef_b, &kef_c);
        if (prov == 1)
            cas = solver(kef_a, kef_b, kef_c, &sol1, &sol2);
        else
            cas = -1;
        output_1(sol1, sol2, cas);
        printf("Если хотите решить еще одно уравнение введите 1, для завершения программы введите 0\n");
        scanf("%d", &pruf);
    }while(pruf);
    return 0;
}
int input_1(double *kef_a, double *kef_b, double *kef_c)
{
    int prov = 1;
    printf("a= ");
    if (scanf("%lf", kef_a) != 1)
        prov = 0;
    else
    {
        printf("b= ");
        if (scanf("%lf", kef_b) != 1)
            prov = 0;
        else
        {
            printf("c= ");
            if (scanf("%lf", kef_c)!= 1)
                prov = 0;
        }
    }
    if (prov == 0)
    {
        while(getchar() != '\n')
            continue;
    }
    return prov;
}
int solver(double kef_a,double kef_b,double kef_c, double *sol1, double *sol2)
{
    double D;
    int cas;
    if (kef_a == 0)
    {
        if (kef_b ==0)
        {
            if (kef_c == 0)
                cas = 0;
            else
               cas = 1;
        }
        else
        {
            cas = 2;
            *sol1 = -kef_c/kef_b;
        }
    }
    else
    {
        D = kef_b*kef_b-4*kef_a*kef_c;
        if (D<0)
            cas = 3;
        else if (D==0)
        {
            cas = 4;
            *sol1 = -kef_b/(2*kef_a);
        }
        else
        {
            cas = 5;
            *sol1 = (-kef_b+sqrt(D))/(2*kef_a);
            *sol2 = (-kef_b-sqrt(D))/(2*kef_a);
        }
    }
    return cas;
}
void output_1(double sol1, double sol2, int cas)
{
    switch(cas)
    {
        case -1:
            printf("Введены некорректные коэффициены\n");
            break;
        case 0:
            printf("Это уравнение имеет бесконечное количество решений\n");
            break;
        case 1:
            printf("это уравнение не имеет решений\n");
            break;
        case 2:
            printf("Это уравнение имеет одно решение %.2f\n", sol1);
            break;
        case 3:
            printf("это уравнение не имеет решений\n");
            break;
        case 4:
            printf("Это уравнение имеет одно решение %.2f\n", sol1);
            break;
        case 5:
            printf("Это уравнение имеет 2 решения x=%.2f и x=%.2f\n", sol1, sol2);
            break;
        default:
            printf("Что-то поломалось.....\n");
            break;
    }
}
