// Calendar console app
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function that returns week-day number ny given date(DD.MM.YYYY). Tomohiko Sakamoto’s Algorithm
int dayNumber(int day, int month, int year)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};                       // month codes
    year -= month < 3;                                                           //-1 if month < 3 and -0 if month >= 3
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7; // this reminder is going to be week-day num
}

// simple function that returns month name by it's number(0-11)
char *getMonthName(int monthNumber)
{
    static char months[12][10] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"};
    char *monthName = months[monthNumber];
    return monthName;
}

// return number of days in certain month by month number and year number(Given the leap years)
int numberOfDays(int monthNumber, int year)
{
    if (monthNumber == 1)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) // for feb in leap years
        {
            return 29;
        }
        else
            return 28;
    }

    int d31[] = {0, 2, 4, 6, 7, 9, 11};
    for (int i = 0; i < (sizeof(d31)) / (sizeof(int)); i++)
    {
        if (d31[i] == monthNumber)
            return 31;
    }
    return 30;
}

void printCalendar(int year)
{
    int days;                            // storing num of days in cur month
    int current = dayNumber(1, 1, year); // get the week-day of January first in certain year(to calculate how many spaces to print berfore it)
    char *s = "Calendar";
    printf("---%*s%*s---\n", 10 + strlen(s) / 2, s, 10 - strlen(s) / 2, "");

    for (int i = 0; i < 12; i++)
    {

        days = numberOfDays(i, year);

        printf("----%*s%*s----\n\n", 10 + strlen(getMonthName(i)), getMonthName(i), 10, "");
        printf("Sn    Mn    Tu    Wd    Th    Fr    St\n");
        int sp; // counter for spaces
        for (sp = 0; sp < current; sp++)
        {
            printf("      ");
        }
        for (int i = 1; i <= days; i++)
        {
            if ((sp + 1) > 6) // if we are at the end of the week -> line break
            {
                i < 10 ? printf("0%d", i) : printf("%d", i); // 1->01....9->09
                sp = 0;
                printf("\n");
            }
            else
            {
                i < 10 ? printf("0%d%4s", i, "") : printf("%d%4s", i, "");
                sp++;
            }
        }
        current = sp; // to make transition between months
        printf("\n\n\n");
    }
    return;
}

int main(void)
{
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printCalendar(year); // call our print func
    return 0;
}