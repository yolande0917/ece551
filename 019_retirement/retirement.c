#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

int calculateYears(int totalAge) {
  return totalAge / 12;
}

int calculateMonths(int totalAge) {
  return totalAge % 12;
}

double printMonthlySaving(int age, double saving, double rate, double contribution) {
  int months = calculateMonths(age);
  int years = calculateYears(age);
  saving = saving * (1 + rate) + contribution;
  printf("Age %3d month %2d you have $%.2lf\n", years, months, saving);
  return saving;
}

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired
  printf("Age %3d month %2d you have $%.2lf\n",
         calculateYears(startAge),
         calculateMonths(startAge),
         initial);
  while (working.months > 0) {
    startAge++;
    working.months--;
    initial = printMonthlySaving(
        startAge, initial, working.rate_of_return, working.contribution);
  }

  while (retired.months > 1) {
    startAge++;
    retired.months--;
    initial = printMonthlySaving(
        startAge, initial, retired.rate_of_return, retired.contribution);
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return 0;
}
