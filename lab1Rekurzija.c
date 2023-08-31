#include <stdio.h>

double izracunajBn(unsigned int n, double b_0, double b_1, double b_2, double lam_1, double lam_2)
{

   if (n == 0)
   {
      return b_0;
   }
   else if (n == 1)
   {
      return b_1;
   }
   else if (n == 2)
   {
      return b_2;
   }
   else
   {
      double b_n = lam_1 * b_1 + lam_2 * b_0;
      for (int i = 3; i <= n; i++)
      {
         b_0 = b_1;
         b_1 = b_n;
         b_n = lam_1 * b_1 + lam_2 * b_0;
      }
      return b_n;
   }

   return -1;
}

int main(void)
{

   unsigned int n;
   double b_0, b_1, b_2, c_0, c_1, c_2, b_n;

   // ucitavanje broja clanova niza
   printf("Unesite nenegativan cijeli broj: ");
   scanf("%u", &n);
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

   /*
   𝑎𝑛 = 𝜆1𝑎𝑛−1 + 𝜆2𝑎𝑛−2
   -> da bih dobila 𝜆1 i 𝜆2 treba, rijesiti sustav s dvije nepoznanice
   1. b_2 = 𝜆1*b_1 + 𝜆2 * b_0
   2. c_2 = 𝜆1*c_1 + 𝜆2 * c_0

   IDEJA: rijesiti metodom suprotnih koeficijenata

   𝜆1*b_1 + 𝜆2 * b_0 = b_2 / *c_1
   𝜆1*c_1 + 𝜆2 * c_0 = c_2 / *b_1

   𝜆1*b_1 * c_1 + 𝜆2 * b_0 * c_1 = b_2 * c_1
   𝜆1*c_1 * b_1  + 𝜆2 * c_0 * b_1= c_2 * b_1

   𝜆2 * (b_0 * c_1 - c_0 * b_1) = b_2 * c_1 - c_2 * b_1

   ----> 𝜆2 = (b_2 * c_1 - c_2 * b_1) / (b_0 * c_1 - c_0 * b_1)

   𝜆1*b_1 + 𝜆2 * b_0 = b_2
   𝜆1 * b_1 = b_2 - 𝜆2 * b_0 / /b_1

   ----> 𝜆1 = (b_2 / b_1) - (𝜆2 * b_0 / b_1)

   */

   double lam_1, lam_2;
   lam_2 = (b_2 * c_1 - c_2 * b_1) / (b_0 * c_1 - c_0 * b_1);
   lam_1 = (b_2 / b_1) - (lam_2 * b_0 / b_1);

   b_n = izracunajBn(n, b_0, b_1, b_2, lam_1, lam_2);

   printf("Vrijednost broja b_n: %.0lf", b_n);

   return 0;
}