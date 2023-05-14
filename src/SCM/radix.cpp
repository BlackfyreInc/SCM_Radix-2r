#include <iostream>
#include <bitset>
#include <math.h>
#include "radix.h"
#include "rpag.h"

#define DUBUG_SCM

#define RADIX_R 4

std::chrono::duration<long double> total_radix_time(0);
std::chrono::duration<long double> total_radix_time_b(0);

void zero_time(){
   total_radix_time = total_radix_time_b;
}

std::map<std::string, int> radix_op_count = {
    {"shifts", 0},
    {"~", 0},
    {"^", 0},
    {"&", 0},
    {"-", 0},
    {"+", 0},
    {"*", 0},
    {"=", 0},
    {"==", 0}};

void zero_ops_count()
{
   radix_op_count = {
       {"shifts", 0},
       {"~", 0},
       {"^", 0},
       {"&", 0},
       {"-", 0},
       {"+", 0},
       {"*", 0},
       {"=", 0},
       {"==", 0}};
}

double lambert_Wanalyt(double x)
{ // Lambert W function W{x}, where x>=3e-3
   // Analytical approximation formula

   const double E = 0.4586887;

   if (x > 3e-3)
   {
      return (1 + E) * log(1.2 * x / log(2.4 * x / log(1 + 2.4 * x))) - E * log(2 * x / log(1 + 2 * x));
   }
   else
      return NAN;
}

double getR_coeff(int N)
{
   double r = 2 * lambert_Wanalyt(sqrt(N + 1) * log(2)) / log(2);
   return ceil(r);
}

int upper_bound(double r, int N)
{
   int upb = ceil((N + 1) / (r) + pow(2, r - 2) - 2);
   return upb;
}

int adder_depth(double r, int N)
{
   int ath = ceil((N + 1) / (r) + r - 3);
   return ath;
}

double avg_pp(double r, int N)
{
   double avg_pp = (1 - pow(2, -r) * ceil((N + 1) / r));
   return avg_pp;
}

unsigned getQ(unsigned c, int oldest)
{
   unsigned C = c;
   radix_op_count["&"]++;
   radix_op_count["shifts"] += 1;
   if (c & (1 << oldest))
   {
      radix_op_count["~"]++;
      radix_op_count["="]++;
      C = ~C;
   }
   radix_op_count["+"]++;
   radix_op_count["shifts"]++;
   return (C + 1) >> 1;
}

Triplet get_triplet(uint32_t c, int oldest)
{
   radix_op_count["="] += 2;
   radix_op_count["&"]++;
   radix_op_count["shifts"] += 1;
   Triplet tr = {0, 0, 0};
   unsigned C = c;
   if (c & (1 << oldest))
   {
      radix_op_count["~"]++;
      radix_op_count["&"]++;
      radix_op_count["shifts"] += 1;
      radix_op_count["="] += 3;
      C = ~C;
      C &= ((1 << (oldest)) - 1);
      tr.sign = 1;
   }

   radix_op_count["shifts"]++;
   radix_op_count["+"]++;
   radix_op_count["="]++;
   unsigned Q = (C + 1) >> 1;

   if (Q)
   {
      radix_op_count["="]++;
      radix_op_count["^"]++;
      radix_op_count["-"]++;
      radix_op_count["shifts"]++;
      unsigned K = (Q ^ (Q - 1)) >> 1;
      while (K)
      {
         radix_op_count["+"]++;
         radix_op_count["shifts"]++;
         tr.k++;
         K >>= 1;
      }
   }

   radix_op_count["shifts"]++;
   radix_op_count["="]++;
   tr.m = Q >> tr.k;
   return tr;
}

int get_triplets(uint32_t n, int r, Triplet Q[8])
{
   radix_op_count["="]++;
   radix_op_count["shifts"]++;
   unsigned N = (n << 1);
#ifdef DEBUG_SCM
   std::cout << std::bitset<32>(N) << std::endl;
#endif // DEBUG_SCM

   radix_op_count["="]++;
   radix_op_count["shifts"]++;
   radix_op_count["+"]++;
   radix_op_count["-"]++;
   int mask = (1 << (r + 1)) - 1;

   radix_op_count["="]++;
   int i = 0;
   while (N)
   {
      radix_op_count["="] += 3;
      radix_op_count["&"]++;
      radix_op_count["shifts"]++;
      radix_op_count["+"]++;
      int c = N & mask;
      N = N >> r;
      Q[i++] = get_triplet(c, r);
#ifdef DEBUG_SCM
      std::cout << std::bitset<32>(N) << std::endl;
#endif // DEBUG_SCM
   }

   return i;
}

uint32_t mult_base(unsigned m, uint32_t x)
{
   switch (m)
   {
   case 1:
      return x;
   case 3:
      radix_op_count["shifts"]++;
      radix_op_count["+"]++;
      return (x << 1) + x;
   case 5:
      radix_op_count["shifts"] += 2;
      radix_op_count["+"]++;
      return (x << 2) + x;
   case 7:
      radix_op_count["shifts"] += 3;
      radix_op_count["-"]++;
      return (x << 3) - x;
   case 9:
      radix_op_count["shifts"] += 3;
      radix_op_count["+"]++;
      return (x << 3) + x;
   case 11:
      radix_op_count["shifts"] += 4;
      radix_op_count["+"] += 2;
      return (x << 3) + (x << 1) + x;
   case 13:
      radix_op_count["shifts"] += 5;
      radix_op_count["+"] += 2;
      return (x << 3) + (x << 2) + x;
   case 15:
      radix_op_count["shifts"] += 4;
      radix_op_count["-"]++;
      return (x << 4) - x;
   case 17:
      radix_op_count["shifts"] += 4;
      radix_op_count["+"]++;
      return (x << 4) + x;
   case 19:
      radix_op_count["shifts"] += 6;
      radix_op_count["+"]++;
      radix_op_count["-"]--;
      return (x << 4) + (x << 2) - x;
   case 21:
      radix_op_count["shifts"] += 6;
      radix_op_count["+"] += 2;
      return (x << 4) + (x << 2) + x;
   case 23:
      radix_op_count["shifts"] += 7;
      radix_op_count["+"]++;
      radix_op_count["-"]--;
      return (x << 4) + (x << 3) - x;
   case 25:
      radix_op_count["shifts"] += 7;
      radix_op_count["+"] += 2;
      return (x << 4) + (x << 3) + x;
   case 27:
      radix_op_count["shifts"] += 7;
      radix_op_count["-"] += 2;
      return (x << 5) - (x << 2) - x;
   case 29:
      radix_op_count["shifts"] += 7;
      radix_op_count["+"]++;
      radix_op_count["-"]++;
      return (x << 5) - (x << 2) + x;
   case 31:
      radix_op_count["shifts"] += 5;
      radix_op_count["-"]++;
      return (x << 5) - x;
   default:
      return 0;
   }
}

int32_t mult(Triplet q, uint32_t multiplier)
{
   int32_t r = mult_base(q.m, multiplier);
   radix_op_count["="]++;
   radix_op_count["shifts"]++;
   r <<= q.k;
   if (q.sign)
   {
      radix_op_count["-"]++;
      return -r;
   }
   return r;
}

uint64_t multiply(Triplet *Q, int triplSize, uint32_t multiplier, int r)
{
   radix_op_count["="]++;
   uint64_t S = 0;
   for (int i = triplSize - 1; i >= 0; i--)
   {
      radix_op_count["shifts"]++;
      radix_op_count["="]++;
      S <<= r;
#ifdef DEBUG_SCM
      std::cout << "S(after <<=r) = " << S << std::endl;
      std::cout << "q_m = " << Q[i].m << std::endl;
#endif // DEBUG_SCM
      radix_op_count["="]++;
      radix_op_count["+"]++;
      S += mult(Q[i], multiplier);
   }
   return S;
}

int scm_float_mult(Bitset_Float *a, Bitset_Float *b, Bitset_Float *result)
{
   Bitset_Float *x = a->Clone();
   Bitset_Float *y = b->Clone();
   Triplet Q_3[8];
   std::chrono::steady_clock::time_point start_radix_time = std::chrono::steady_clock::now();

#ifdef DEBUG_SCM
   std::cout << "Mantissa1 bits =  " << x->getFractional() << "; Exponent1 bits: " << x->getExponent() << std::endl;
   std::cout << "Mantissa2 bits =  " << y->getFractional() << "; Exponent2 bits: " << y->getExponent() << std::endl;
#endif
   unsigned csign = x->get_sign_bit() ^ y->get_sign_bit();
   radix_op_count["="]++;
   radix_op_count["^"]++;

   if (x->is_zero() || y->is_zero())
   {
      result->get_result(0, 0, 0, 32, 0);
      return 0;
   }

   unsigned mantSize1 = x->get_fractional_size();
   uint32_t mantis1 = x->get_fractional() + (1 << mantSize1);
   uint32_t exp1 = x->get_exponent();

   unsigned mantSize2 = y->get_fractional_size();
   uint32_t mantis2 = y->get_fractional() + (1 << mantSize2);
   uint32_t exp2 = y->get_exponent();
   radix_op_count["="] += 6;
   radix_op_count["+"] += 2;
   //radix_op_count["shifts"] += mantSize1 + mantSize2;
   radix_op_count["shifts"] += 1;
#ifdef DEBUG_SCM
   std::cout << "X" << std::bitset<3>(exp1) << ", " << exp1 << ";" << mantSize1 << "\n";
   std::cout << "Y" << std::bitset<3>(exp2) << ", " << exp2 << ";" << mantSize2 << "\n";
#endif
   int scm_k = get_triplets(mantis1, RADIX_R, Q_3);
#ifdef DEBUG_SCM

   int32_t exp_1 = (int)(exp1 - 127);
   int32_t exp_2 = (int)(exp2 - 127);
   std::cout << "Mantissa1 =  " << std::bitset<24>(mantis1) << "; Exponent1: " << exp_1 << std::endl;
   std::cout << "Mantissa2 =  " << std::bitset<24>(mantis2) << "; Exponent2: " << exp_2 << std::endl;

   for (int i = 0; i < scm_k; i++)
   {
      std::cout << Q_3[i].sign << "  " << Q_3[i].m << "  " << Q_3[i].k << std::endl;
   }

   std::cout << "multiplier = " << mantis2 << std::endl;
#endif
   uint64_t new_mant = multiply(Q_3, scm_k, mantis2, RADIX_R) >> (mantSize2);
   //radix_op_count["shifts"] += mantSize2;
   radix_op_count["shifts"] += 1;
#ifdef DEBUG_SCM
   std::cout << std::bitset<64>(multiply(Q_3, scm_k, mantis2, 4)) << std::endl;
#endif
   uint32_t eexp = exp1 + exp2;
   radix_op_count["+"]++;
#ifdef DEBUG_SCM
   std::cout << "new mantissa = " << std::bitset<28>(new_mant) << "exp" << eexp << std::endl;
#endif
   // case of carry for leftmost bit
   if (((new_mant >> mantSize1) & 0x3) >= 2)
   {
      new_mant >>= 1;
      //radix_op_count["shifts"] += 1 + mantSize1;
      radix_op_count["shifts"] += 1;
      radix_op_count["&"]++;
      radix_op_count["+"]++;
      radix_op_count["="]++;
      eexp += 1;
   }
   uint32_t mantis3 = new_mant;
   radix_op_count["="]++;
#ifdef DEBUG_SCM
   std::cout << "m=" << std::bitset<32>(new_mant) << "sz" << y->get_exponent_size() << "\n";
#endif
   result->get_result(mantis3, eexp, csign, 32, y->get_exponent_size());
   total_radix_time += std::chrono::steady_clock::now() - start_radix_time;
   radix_op_count["+"]++;
   radix_op_count["="]++;
   radix_op_count["-"]++;

   // result->set_number(num);

#ifdef DEBUG_SCM

   std::cout << "combined sign = " << csign << std::endl;
   std::cout << "combined mantissa = " << new_mant << std::endl;
   std::cout << "combined exp = " << exp << "or" << exp_t << std::endl;
   std::cout << "string bit exp = " << std::bitset<8>(exp).to_string() << std::endl;
   std::cout << "string 23bit mantissa = " << std::bitset<23>(new_mant).to_string() << std::endl;
   std::cout << "string 64bit mantissa = " << std::bitset<64>(new_mant).to_string() << std::endl;
   std::cout << "string result bits = " << std::bitset<32>(num).to_string() << std::endl;
   std::cout << "______________________________________________________________________________________________________________________________________________________" << std::endl;
   std::cout << "Radix multiplication result = " << result << std::endl;
   std::cout << "Usual multiplication result = " << (*x) * (*y) << std::endl;
   std::cout << "______________________________________________________________________________________________________________________________________________________" << std::endl;
#endif
   delete x;
   delete y;
   return 0;
}

int scm_float_rpag_mult(Bitset_Float *a, Bitset_Float *b, Bitset_Float *result)
{
   Bitset_Float *x = a->Clone();
   Bitset_Float *y = b->Clone();

   char ops[16];
   int fst[16];
   int sec[16];
   std::chrono::steady_clock::time_point start_radix_time = std::chrono::steady_clock::now();

#ifdef DEBUG_SCM
   std::cout << "Mantissa1 bits =  " << x->getFractional() << "; Exponent1 bits: " << x->getExponent() << std::endl;
   std::cout << "Mantissa2 bits =  " << y->getFractional() << "; Exponent2 bits: " << y->getExponent() << std::endl;
#endif
   unsigned csign = x->get_sign_bit() ^ y->get_sign_bit();
   radix_op_count["="]++;
   radix_op_count["^"]++;

   if (x->is_zero() || y->is_zero())
   {
      result->get_result(0, 0, 0, 32, 0);
      return 0;
   }

   unsigned mantSize1 = x->get_fractional_size();
   uint32_t mantis1 = x->get_fractional() + (1 << mantSize1);
   uint32_t exp1 = x->get_exponent();

   unsigned mantSize2 = y->get_fractional_size();
   uint32_t mantis2 = y->get_fractional() + (1 << mantSize2);
   uint32_t exp2 = y->get_exponent();
   radix_op_count["="] += 6;
   radix_op_count["+"] += 2;
   //radix_op_count["shifts"] += mantSize1 + mantSize2;
   radix_op_count["shifts"] += 1;
#ifdef DEBUG_SCM
   std::cout << "X" << std::bitset<3>(exp1) << ", " << exp1 << ";" << mantSize1 << "\n";
   std::cout << "Y" << std::bitset<3>(exp2) << ", " << exp2 << ";" << mantSize2 << "\n";
#endif
   int scm_k = getExpr(mantis1, ops, fst, sec,8);
#ifdef DEBUG_SCM

   int32_t exp_1 = (int)(exp1 - 127);
   int32_t exp_2 = (int)(exp2 - 127);
   std::cout << "Mantissa1 =  " << std::bitset<24>(mantis1) << "; Exponent1: " << exp_1 << std::endl;
   std::cout << "Mantissa2 =  " << std::bitset<24>(mantis2) << "; Exponent2: " << exp_2 << std::endl;

   for (int i = 0; i < scm_k; i++)
   {
      std::cout << Q_3[i].sign << "  " << Q_3[i].m << "  " << Q_3[i].k << std::endl;
   }

   std::cout << "multiplier = " << mantis2 << std::endl;
#endif
   uint64_t new_mant = getNumber2(mantis2, ops,fst,sec, scm_k) >> (mantSize2);
   //radix_op_count["shifts"] += mantSize2;
   radix_op_count["shifts"] += 1;
#ifdef DEBUG_SCM
   std::cout << std::bitset<64>(multiply(Q_3, scm_k, mantis2, 4)) << std::endl;
#endif
   uint32_t eexp = exp1 + exp2;
   radix_op_count["+"]++;
#ifdef DEBUG_SCM
   std::cout << "new mantissa = " << std::bitset<28>(new_mant) << "exp" << eexp << std::endl;
#endif
   // case of carry for leftmost bit
   if (((new_mant >> mantSize1) & 0x3) >= 2)
   {
      new_mant >>= 1;
      //radix_op_count["shifts"] += 1 + mantSize1;
      radix_op_count["shifts"] += 1;
      radix_op_count["&"]++;
      radix_op_count["+"]++;
      radix_op_count["="]++;
      // exp +=1;
      eexp += 1;
   }
   uint32_t mantis3 = new_mant;
   radix_op_count["="]++;
#ifdef DEBUG_SCM
   std::cout << "m=" << std::bitset<32>(new_mant) << "sz" << y->get_exponent_size() << "\n";
#endif
   result->get_result(mantis3, eexp, csign, 32, y->get_exponent_size());
   total_radix_time += std::chrono::steady_clock::now() - start_radix_time;
   radix_op_count["+"]++;
   radix_op_count["="]++;
   radix_op_count["-"]++;

#ifdef DEBUG_SCM

   std::cout << "combined sign = " << csign << std::endl;
   std::cout << "combined mantissa = " << new_mant << std::endl;
   std::cout << "combined exp = " << exp << "or" << exp_t << std::endl;
   std::cout << "string bit exp = " << std::bitset<8>(exp).to_string() << std::endl;
   std::cout << "string 23bit mantissa = " << std::bitset<23>(new_mant).to_string() << std::endl;
   std::cout << "string 64bit mantissa = " << std::bitset<64>(new_mant).to_string() << std::endl;
   std::cout << "string result bits = " << std::bitset<32>(num).to_string() << std::endl;
   std::cout << "______________________________________________________________________________________________________________________________________________________" << std::endl;
   std::cout << "Radix multiplication result = " << result << std::endl;
   std::cout << "Usual multiplication result = " << (*x) * (*y) << std::endl;
   std::cout << "______________________________________________________________________________________________________________________________________________________" << std::endl;
#endif
   delete x;
   delete y;
   return 0;
}

long double get_total_radix_time()
{
   return total_radix_time.count();
}
