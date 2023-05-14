#ifndef RADIX_H
#define RADIX_H
#include "..//BFloat//Bitset_Float.h"
#include <map>
#include <chrono>

long double get_total_radix_time();
void zero_time();

extern std::map<std::string, int> radix_op_count;
void zero_ops_count();

double lambert_Wanalyt(double x);

double getR_coeff(int n);

int upper_bound(double r, int n);
int adder_depth(double r, int n);

double avg_pp(double r, int n);

unsigned getQ(unsigned c, int oldest);

struct Triplet
{
   int sign;
   int m;
   int k;
};

Triplet get_triplet(uint32_t c, int oldest);

int get_triplets(uint32_t n, int r, Triplet Q[8]);

uint32_t mult_base(unsigned m, uint32_t x);

int32_t mult(Triplet q, uint32_t multiplier);

uint64_t multiply(Triplet *Q, int triplSize, uint32_t multiplier, int r);

int scm_float_mult(Bitset_Float* x, Bitset_Float* y, Bitset_Float* result);

int scm_float_rpag_mult(Bitset_Float *a, Bitset_Float *b, Bitset_Float *result);

int getExpr(int m, char* ops, int* fst, int* sec, int k);

int getNumber2(int n,char* ops, int* fst, int* sec, int k);

#endif /* RADIX_H */
