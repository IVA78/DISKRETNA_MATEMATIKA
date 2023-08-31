#include <iostream>
#include <queue>

using namespace std;

bool jePovezan(bool *matrica, int n, int v, bool *posjeceniVrhovi,
               bool *staza)
{

   int cnt = 0; // gledam koliko vrhova imam u stazi
   for (int i = 0; i < n; i++)
   {
      if (*(staza + i) == true)
         cnt++;
   }

   if (cnt == (n - 1))
      return true; // ako mi je broj vrhova u stazi jednak broju cvorova, sve sam
                   // prosla, graf je povezan

   for (int u = 0; u < n; u++)
   {
      if (*(matrica + v * n + u) == true)
      {
         if (*(posjeceniVrhovi + u) == false)
         {
            *(staza + u) = true;
            *(posjeceniVrhovi + u) = true;
            if (jePovezan(matrica, n, u, posjeceniVrhovi, staza))
               return true;
         }
      }
   }

   return false;
}

bool jeHamilton(bool *matrica, int n, int v, bool *posjeceniVrhovi,
                queue<int> staza)
{

   if (staza.size() == n && *(matrica + staza.back()) == true)
      return true; // ako mi je broj vrhova u stazi jednak broju cvorova, sve sam
                   // prosla, graf je povezan + pocetni vrh moram biti povezan sa zadnjim vrhom u stazi

   for (int u = 0; u < n; u++)
   {
      if (*(matrica + v * n + u) == true)
      {
         if (*(posjeceniVrhovi + u) == false)
         {
            staza.push(u);
            *(posjeceniVrhovi + u) = true;

            if (jeHamilton(matrica, n, u, posjeceniVrhovi, staza))
            {
               return true;
            }
            staza.pop();
            *(posjeceniVrhovi + u) = false;
         }
      }
   }

   return false;
}

int main(void)
{

   int n, k1, k2, k3, k4;

   cout << "Unesite prirodan broj n: ";
   cin >> n;
   cout << "Unesite vrijednost prirodnog broja k_1: ";
   cin >> k1;
   cout << "Unesite vrijednost prirodnog broja k_2: ";
   cin >> k2;
   cout << "Unesite vrijednost prirodnog broja k_3: ";
   cin >> k3;
   cout << "Unesite vrijednost prirodnog broja k_4: ";
   cin >> k4;

   bool matricaSusj[n][n];

   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= n; j++)
      {
         if (i != j)
         {
            if (abs(i - j) == k1 || abs(i - j) == k2 || abs(i - j) == k3 ||
                abs(i - j) == k4)
            {
               matricaSusj[i - 1][j - 1] = 1;
            }
            else
            {
               matricaSusj[i - 1][j - 1] = 0;
            }
         }
         else
         {
            matricaSusj[i - 1][j - 1] = 0;
         }
      }
   }

   bool posjeceniVrhovi[n];
   posjeceniVrhovi[0] = true;
   for (int i = 1; i < n; i++)
      posjeceniVrhovi[i] = false;
   bool staza[n];
   for (int i = 0; i < n; i++)
      staza[i] = false;

   bool povezan =
       jePovezan(&matricaSusj[0][0], n, 0, &posjeceniVrhovi[0], &staza[0]);

   cout << endl;

   if (povezan)
   {
      cout << "Graf G je povezan graf\n"
           << endl;
   }
   else
   {
      cout << "Graf G nije povezan graf\n"
           << endl;
   }

   bool hamilton;
   if (!povezan || n == 1 || n == 2)
   {
      hamilton = false;
   }
   else
   {

      bool posjeceniVrhovi[n];
      posjeceniVrhovi[0] = true;
      for (int i = 1; i < n; i++)
         posjeceniVrhovi[i] = false;
      queue<int> staza;
      staza.push(0);

      hamilton = jeHamilton(&matricaSusj[0][0], n, 0, &posjeceniVrhovi[0], staza);
   }

   if (hamilton)
   {
      cout << "Graf G je hamiltonovski graf\n"
           << endl;
   }
   else
   {
      cout << "Graf G nije hamiltonovski graf\n"
           << endl;
   }

   return 0;
}