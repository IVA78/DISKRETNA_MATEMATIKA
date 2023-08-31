#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

bool jePovezan(int *matrica, int n, int v, bool *posjeceniVrhovi,
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
      if (*(matrica + v * n + u) > 0)
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

class Brid
{
public:
   int tezina, pocetni_vrh, krajnji_vrh;

   Brid(int tezina, int pocetni_vrh, int krajnji_vrh)
   {
      this->tezina = tezina;
      this->pocetni_vrh = pocetni_vrh;
      this->krajnji_vrh = krajnji_vrh;
   }
};

class Graf
{
public:
   vector<Brid> bridovi;

   void dodaj_brid(int tezina, int pocetni_vrh, int krajnji_vrh)
   {
      Brid brid(tezina, pocetni_vrh, krajnji_vrh);
      bridovi.push_back(brid);
   }
};

bool usporediBridove(Brid b1, Brid b2)
{
   return (b1.tezina < b2.tezina);
}

void ispis_mst(const vector<Brid> &);

class MST
{

public:
   int broj_vrhova;
   vector<pair<int, int>> podskupovi;
   vector<Brid> mst_bridovi;
   vector<vector<int>> mst_matrica;
   vector<vector<int>> mst_mat_vektor;
   vector<int> susjed;

   MST(int broj_vrhova)
   {

      this->broj_vrhova = broj_vrhova;
      mst_matrica.resize(broj_vrhova);
      podskupovi.resize(broj_vrhova);

      for (auto &stupac : mst_matrica)
      {
         stupac.resize(broj_vrhova);
      }

      for (int i = 0; i < broj_vrhova; ++i)
      {
         for (int j = 0; j < broj_vrhova; ++j)
         {
            mst_matrica[i][j] = 0;
         }
      }

      for (int i = 0; i <= broj_vrhova; i++)
      {
         podskupovi[i].first = i;
         podskupovi[i].second = 0;
      }
   }

   void odredi_MST(Graf &graf)
   {

      // sortiranje bridova za MST
      sort(graf.bridovi.begin(), graf.bridovi.end(), usporediBridove);

      int brojac_ukupni_vrhovi = 0; // na kraju broj bridova u MST treba biti brojac_ukupni_vrhovi - 1
      int brojac_bridovi_u_MST = 0;

      while (brojac_bridovi_u_MST < (broj_vrhova - 1) && brojac_ukupni_vrhovi < graf.bridovi.size())
      {
         Brid trenutni_brid = graf.bridovi[brojac_ukupni_vrhovi++];

         int x = odredi(trenutni_brid.pocetni_vrh);
         int y = odredi(trenutni_brid.krajnji_vrh);

         if (x != y)
         {
            napraviUniju(trenutni_brid.pocetni_vrh, trenutni_brid.krajnji_vrh);
            mst_bridovi.push_back(trenutni_brid);
            mst_matrica[trenutni_brid.pocetni_vrh - 1][trenutni_brid.krajnji_vrh - 1] = trenutni_brid.tezina;
            mst_matrica[trenutni_brid.krajnji_vrh - 1][trenutni_brid.pocetni_vrh - 1] = trenutni_brid.tezina;
            brojac_bridovi_u_MST++;
         }
      }

      //ispis_mst(mst_bridovi);
   }

   int odredi(int vrh)
   {

      if (podskupovi[vrh].first != vrh)
      {
         podskupovi[vrh].first = odredi(podskupovi[vrh].first);
      }

      return podskupovi[vrh].first;
   }

   void napraviUniju(int x, int y)
   {

      int x_korijen = odredi(x);
      int y_korijen = odredi(y);

      if (podskupovi[x_korijen].second > podskupovi[y_korijen].second)
      {
         podskupovi[y_korijen].first = x_korijen;
      }
      else
      {
         podskupovi[x_korijen].first = y_korijen;
      }
      if (podskupovi[x_korijen].second == podskupovi[y_korijen].second)
      {
         podskupovi[y_korijen].second++;
      }
   }

   void dfs_mst(int v)
   {
      for (int i = 0; i < mst_mat_vektor.size(); i++)
      {
         if (mst_mat_vektor[v][i] > 0 && i != susjed[v])
         {
            susjed[i] = v;
            dfs_mst(i);
         }
      }
   }

   vector<int> p_kod()
   {

      int n = mst_mat_vektor.size();
      susjed.resize(n);
      susjed[n - 1] = -1;
      dfs_mst(n - 1);

      int ptr = -1;
      vector<int> stupnjevi(n);
      for (int i = 0; i < n; i++)
      {
         stupnjevi[i] = 0;
         for (int j = 0; j < n; j++)
         {
            if (mst_mat_vektor[i][j] > 0)
            {
               stupnjevi[i]++;
            }
         }
         if (stupnjevi[i] == 1 && ptr == -1)
         {
            ptr = i;
         }
      }

      vector<int> pruf_kod(n - 2);
      int list = ptr;
      for (int i = 0; i < n - 2; i++)
      {
         int sljedeci = susjed[list];
         pruf_kod[i] = sljedeci;
         if (--stupnjevi[sljedeci] == 1 && sljedeci < ptr)
         {
            list = sljedeci;
         }
         else
         {
            ptr++;
            while (stupnjevi[ptr] != 1)
               ptr++;
            list = ptr;
         }
      }

      return pruf_kod;
   }
};

void ispis_mst(const vector<Brid> &bridovi)
{
   int minimalna_tezina = 0;
   cout << "MST bridovi [pocetni vrh - krajnji vrh = tezina]\n";

   for (auto brid : bridovi)
   {
      cout << brid.pocetni_vrh << " - " << brid.krajnji_vrh << " = " << brid.tezina << '\n';

      minimalna_tezina += brid.tezina;
   }
   cout << "Ukupna minimalna tezina = " << minimalna_tezina << endl;
}

int main(void)
{

   int n, a, b, c;

   cout << "Unesite prirodan broj n: ";
   cin >> n;
   cout << "Unesite prirodan broj a: ";
   cin >> a;
   cout << "Unesite prirodan broj b: ";
   cin >> b;
   cout << "Unesite prirodan broj c: ";
   cin >> c;

   int matricaSusj[n][n];

   for (int i = 1; i <= n; i++)
   {
      for (int j = i; j <= n; j++)
      {
         if (i < j)
         {
            double izraz = abs(a * i - b * j) * 1. / c;
            izraz = floor(izraz);
            if (izraz != 0)
            {
               matricaSusj[i - 1][j - 1] = izraz;
               matricaSusj[j - 1][i - 1] = izraz;
            }
            else
            {
               matricaSusj[i - 1][j - 1] = 0;
               matricaSusj[j - 1][i - 1] = 0;
            }
         }
         else
         {
            matricaSusj[i - 1][j - 1] = 0;
            matricaSusj[j - 1][i - 1] = 0;
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

      Graf g;
      for (int i = 1; i <= (n - 1); i++)
      {
         for (int j = i; j <= n; j++)
         {
            if (i < j)
            {
               if (matricaSusj[i - 1][j - 1] != 0)
               {
                  g.dodaj_brid(matricaSusj[i - 1][j - 1], i, j);
               }
            }
         }
      }

      MST mst_graf(n);
      mst_graf.odredi_MST(g);

      mst_graf.mst_mat_vektor.resize(mst_graf.broj_vrhova, vector<int>(mst_graf.broj_vrhova));
      for (int i = 0; i < mst_graf.broj_vrhova; i++)
      {
         for (int j = 0; j < mst_graf.broj_vrhova; j++)
         {
            mst_graf.mst_mat_vektor[i][j] = mst_graf.mst_matrica[i][j];
         }
      }
      cout << endl;
      cout << "Pruferov kod minimalnog razapinjuceg stabla: ";
      vector<int> p_kod = mst_graf.p_kod();
      int prvi_ispis = 1;
      for (int i : p_kod)
      {
         if (prvi_ispis == 1)
         {
            prvi_ispis = 0;
            cout << "(" << (i + 1);
         }
         else
         {
            cout << ", " << (i + 1);
         }
      }
      cout << ")";

      cout << endl;
   }
   else
   {
      cout << "Graf G nije povezan graf\n"
           << endl;
   }

   return 0;
}