#include<TXLib.h>
#include<stdio.h>
#include<math.h>
int main(void)
{
    float a, b, c, D;
    double sol1, sol2;
    int pruf=1;
    printf("Ёта программа решает уравнени€ вида ax^2+bx+c=0\n");
    do
    {
        printf("¬ведите параметры уравнени€:\na= ");
        scanf("%f", &a);
        printf("b= ");
        scanf("%f", &b);
        printf("c= ");
        scanf("%f", &c);
        if (a == 0)
        {
            sol1 = -c/b;
            printf("Ёто уравнение имеет 1 корень х=%.2f\n", sol1);
        }
        else
        {
            D = b*b-4*a*c;
            if (D<0)
            {
                printf("Ёто уравнение не имеет действительных решений\n");
            }
            else if (D==0)
            {
                sol1 = -b/(2*a);
                printf("Ёто уравнение имеет 1 корень х=%.2f\n", sol1);
            }
            else
            {
                sol1 = (-b+sqrt(D))/(2*a);
                sol2 = (-b-sqrt(D))/(2*a);
                printf("Ёто уравнение имеет 2 корн€ х=%.2f и x=%.2f\n", sol1, sol2);
            }
        }
        printf("≈сли хотите решить еще одно уравнение введите 1, дл€ завершени€ программы введите 0\n");
        scanf("%d", &pruf);
    }while(pruf);
    return 0;
}
