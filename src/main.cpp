#include "TESTS//tests.h"
#include <cstdlib>

#define DEBUG_mult

int main()
{
#ifdef DEBUG_mult
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "DEMONSTRATION" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    Bitset_Float *arg01 = new Bitset_Float(-77.543);
    Bitset_Float *arg02 = new Bitset_Float(234);
    Bitset_Float *res0 = new Bitset_Float(0);

    Bitset_Float *arg11 = new Bitset_Float(3.0);
    Bitset_Float *arg12 = new Bitset_Float(0);
    Bitset_Float *res1 = new Bitset_Float(0);

    Bitset_Float *arg21 = new Bitset_Float(2222.65);
    Bitset_Float *arg22 = new Bitset_Float(0.0005);
    Bitset_Float *res2 = new Bitset_Float(0);

    Bitset_Float *arg31 = new Bitset_Float(2222.65);
    Bitset_Float *arg32 = new Bitset_Float(123.564);
    Bitset_Float *res3 = new Bitset_Float(0);

    Bitset_Float *arg41 = new Bitset_Float(0.03);
    Bitset_Float *arg42 = new Bitset_Float(0.054);
    Bitset_Float *res4 = new Bitset_Float(0);

    Bitset_Float *arg51 = new Bitset_Float(-11.0);
    Bitset_Float *arg52 = new Bitset_Float(-4.0);
    Bitset_Float *res5 = new Bitset_Float(0);

    Bitset_Float *arg61 = new Bitset_Float(8.5);
    Bitset_Float *arg62 = new Bitset_Float(2);
    Bitset_Float *res6 = new Bitset_Float(0);

    long double el_time = 0.0;
    scm_float_mult(arg01, arg02, res0);
    el_time += get_total_radix_time();
    scm_float_mult(arg11, arg12, res1);
    el_time += get_total_radix_time();
    scm_float_mult(arg21, arg22, res2);
    el_time += get_total_radix_time();
    scm_float_mult(arg31, arg32, res3);
    el_time += get_total_radix_time();
    scm_float_mult(arg41, arg42, res4);
    el_time += get_total_radix_time();
    scm_float_mult(arg51, arg52, res5);
    el_time += get_total_radix_time();
    scm_float_mult(arg61, arg62, res6);
    el_time += get_total_radix_time();
    std::cout << "Count of operations for Radix:" << std::endl;
    for (auto itr = radix_op_count.begin(); itr != radix_op_count.end(); ++itr)
    {
        std::cout << itr->first << ": " << itr->second << std::endl;
    }
    std::cout << "Time for Radix for used scm_float_mult functions: " << el_time << std::endl;
    std::cout << "Results: " << std::endl;
    std::cout << arg01->to_float() << " * " << arg02->to_float() << " = " << res0->to_float() << std::endl;
    std::cout << arg11->to_float() << " * " << arg12->to_float() << " = " << res1->to_float() << std::endl;
    std::cout << arg21->to_float() << " * " << arg22->to_float() << " = " << res2->to_float() << std::endl;
    std::cout << arg31->to_float() << " * " << arg32->to_float() << " = " << res3->to_float() << std::endl;
    std::cout << arg41->to_float() << " * " << arg42->to_float() << " = " << res4->to_float() << std::endl;
    std::cout << arg51->to_float() << " * " << arg52->to_float() << " = " << res5->to_float() << std::endl;
    std::cout << arg61->to_float() << " * " << arg62->to_float() << " = " << res6->to_float() << std::endl;

    delete arg01;
    delete arg02;
    delete arg11;
    delete arg12;
    delete arg21;
    delete arg22;
    delete arg31;
    delete arg32;
    delete arg41;
    delete arg42;
    delete arg51;
    delete arg52;
    delete arg61;
    delete arg62;
    delete res0;
    delete res1;
    delete res2;
    delete res3;
    delete res4;
    delete res5;
    delete res6;
#endif
    return 0;
}
