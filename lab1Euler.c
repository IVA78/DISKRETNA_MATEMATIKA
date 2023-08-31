#include <complex.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
   
   int n;
   double b_0, b_1, b_2, c_0, c_1, c_2, b_n;
   double complex b_n_compl;
   _Bool comp = 0;

   // ucitavanje broja clanova niza
   printf("Unesite nenegativan cijeli broj: ");
   scanf("%d", &n);

   if (n < 0)
   {
      printf("Niste unijeli nenegativan cijeli broj");
   }
   else
   {

      // ucitavanje prva tri clana niza bn
      printf("Unesite vrijednost broja b_0: ");

      scanf("%lf", &b_0);
      printf("Unesite vrijednost broja b_1: ");
      scanf("%lf", &b_1);
      printf("Unesite vrijednost broja b_2: ");
      scanf("%lf", &b_2);
      // ucitavanje prva tri clana niza cn
      printf("Unesite vrijednost broja c_0: ");
      scanf("%lf", &c_0);
      printf("Unesite vrijednost broja c_1: ");
      scanf("%lf", &c_1);
      printf("Unesite vrijednost broja c_2: ");
      scanf("%lf", &c_2);

      // racunam lambde za rekurziju
      double lam_1, lam_2;
      /*
      Prvi nacin za rjesavanje -> Metoda suprotnih koeficijenata
      lam_2 = (b_2 * c_1 - c_2 * b_1) / (b_0 * c_1 - c_0 * b_1);
      lam_1 = (b_2 / b_1) - (lam_2 * b_0 / b_1);

      -> za slucaj 24 1 0 5 2 10 10 imam nulu u nazivniku!

      Drugi nacin za rjesavanje -> Cramerovo pravilo
      int d = b_1 * c_0 - c_1 * b_0;
      int d1 = b_2 * c_0 - b_0 * c_2;
      int d2 = b_1 * c_2 - c_1 * b_2;
      lam_1 = d1 / d;
      lam_2 = d2 / d;
      */
      int d = b_1 * c_0 - c_1 * b_0;
      int d1 = b_2 * c_0 - b_0 * c_2;
      int d2 = b_1 * c_2 - c_1 * b_2;
      lam_1 = d1 / d;
      lam_2 = d2 / d;

      // Eulerovom supstitucijom dolazim do diskriminante karakteristicne jednadzbe
      double D = pow(lam_1, 2) + 4 * lam_2;

      if (D > 0)
      {
         double x_1 = (lam_1 + sqrt(D)) / 2.;
         double x_2 = (lam_1 - sqrt(D)) / 2.;

         // racunam lambde iz pocetnih uvjeta
         double lam_2_nova = (b_0 * x_1 - b_1) / (x_1 - x_2);
         double lam_1_nova = b_0 - lam_2_nova;

         b_n = lam_1_nova * pow(x_1, n) + lam_2_nova * pow(x_2, n);
      }
      else if (D == 0)
      {
         // racunam lambde iz pocetnih uvjeta
         double x = lam_1 / 2.;
         double lam_1_nova = b_0;
         double lam_2_nova = (b_1 - lam_1_nova * x) / x;

         b_n = lam_1_nova * pow(x, n) + lam_2_nova * n * pow(x, n);
      }
      else
      {
         comp = 1;

         double complex x_1_compl = lam_1 / 2. + sqrt(fabs(D)) / 2. * I;
         double complex x_2_compl = lam_1 / 2. - sqrt(fabs(D)) / 2. * I;

         /*
         double complex lam_2_nova = (b_0 * x_1_compl - b_1) / (x_1_compl - x_2_compl);
         double complex lam_1_nova = b_0 - lam_2_nova;

         Rucno dijeljenje kompleksnih brojeva
         (a + bi) / (c + di) = ((ac + bd) / (c * c + d * d)) + ((bc - ad) / (c*c + d*d)) * I

         (c + di) = (x1 - x2) = (creal(x1) - creal(x2) + (cimag(x1) - cimag(x2)) * I);
         c = creal(x1) - creal(x2);
         d = cimag(x1) - cimag(x2);
         a = b_0 * creal(x1) - b_1;
         b = b_0 * cimag(x1);
         */
         double a, b, c, d;
         a = b_0 * creal(x_1_compl) - b_1;
         b = b_0 * cimag(x_1_compl);
         c = creal(x_1_compl) - creal(x_2_compl);
         d = cimag(x_1_compl) - cimag(x_2_compl);
         double complex lam_2_nova = ((a * c + b * d) / (c * c + d * d)) + ((b * c - a * d) / (c * c + d * d)) * I;
         double complex lam_1_nova = b_0 - creal(lam_2_nova) - cimag(lam_2_nova) * I;

         /*
         Potencija x1
         double complex x_1_poten = 1;
         for(int i = 0; i < n; i++) {
            x_1_poten *= x_1_compl;
         }
         */
         double complex x_1_poten = 1;
         for (int i = 0; i < n; i++)
         {
            x_1_poten *= x_1_compl;
         }

         double complex x_2_poten = 1;
         for (int i = 0; i < n; i++)
         {
            x_2_poten *= x_2_compl;
         }

         b_n_compl = (lam_1_nova * x_1_poten + lam_2_nova * x_2_poten);
      }
      if (!comp)
      {
         printf("Vrijednost broja b_n: %f", b_n);
      }
      else
      {
         printf("Vrijednost broja b_n: %f", b_n_compl);
      }
   }

   return 0;
}