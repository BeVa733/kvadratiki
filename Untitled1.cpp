#include<TXLib.h>
#include<stdio.h>
#include<math.h>
int main(void)
{
    float a, b, c, D;
    double sol1, sol2;
    int pruf=1;
    printf("��� ��������� ������ ��������� ���� ax^2+bx+c=0\n");
    do
    {
        printf("������� ��������� ���������:\na= ");
        scanf("%f", &a);
        printf("b= ");
        scanf("%f", &b);
        printf("c= ");
        scanf("%f", &c);
        if (a == 0)
        {
            sol1 = -c/b;
            printf("��� ��������� ����� 1 ������ �=%.2f\n", sol1);
        }
        else
        {
            D = b*b-4*a*c;
            if (D<0)
            {
                printf("��� ��������� �� ����� �������������� �������\n");
            }
            else if (D==0)
            {
                sol1 = -b/(2*a);
                printf("��� ��������� ����� 1 ������ �=%.2f\n", sol1);
            }
            else
            {
                sol1 = (-b+sqrt(D))/(2*a);
                sol2 = (-b-sqrt(D))/(2*a);
                printf("��� ��������� ����� 2 ����� �=%.2f � x=%.2f\n", sol1, sol2);
            }
        }
        printf("���� ������ ������ ��� ���� ��������� ������� 1, ��� ���������� ��������� ������� 0\n");
        scanf("%d", &pruf);
    }while(pruf);
    return 0;
}
