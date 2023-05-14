#include "tests.h"
// #define DEBUG_radix

void get_triplets_test()
{
    std::cout << "get_triplets tests" << std::endl;
    // 6890241
    Triplet Q[8];
    int r = getR_coeff(32);
    std::cout << "r = " << r << std::endl;
    int k = get_triplets((unsigned)6890241, r, Q);

    for (int i = 0; i < k; i++)
    {
        std::cout << Q[i].sign << "  " << Q[i].m << "  " << Q[i].k << std::endl;
    }

    // // 25
    Triplet Q_1[8];
    int r_1 = getR_coeff(32);
    std::cout << "r_1 = " << r_1 << std::endl;
    int k_1 = get_triplets((unsigned)25, r_1, Q_1);

    for (int i = 0; i < k_1; i++)
    {
        std::cout << Q[i].sign << "  " << Q[i].m << "  " << Q[i].k << std::endl;
    }

    // // 340
    Triplet Q_2[8];
    int r_2 = getR_coeff(32);
    std::cout << "r = " << r_2 << std::endl;
    int k_2 = get_triplets((unsigned)340, r_2, Q_2);

    for (int i = 0; i < k_2; i++)
    {
        std::cout << Q[i].sign << "  " << Q[i].m << "  " << Q[i].k << std::endl;
    }
}

void multiply_test()
{
    Triplet Q[8];
    int r = getR_coeff(32);
    int k = get_triplets((unsigned)6890241, r, Q);
    Triplet Q_1[8];
    int r_1 = getR_coeff(32);
    int k_1 = get_triplets((unsigned)25, r_1, Q_1);
    Triplet Q_2[8];
    int r_2 = getR_coeff(32);
    int k_2 = get_triplets((unsigned)340, r_2, Q_2);
    std::cout << "_________________________________________" << std::endl;
    std::cout << "multiply tests" << std::endl;
    int r1 = multiply(Q, k, 2, r);
    std::cout << r1 << " = " << 2 << "*" << 6890241 << " = " << 2 * 6890241 << std::endl;
    int r2 = multiply(Q, k, 3, r);
    std::cout << r2 << " = " << 3 << "*" << 6890241 << " = " << 3 * 6890241 << std::endl;
    int r3 = multiply(Q, k, 4, r);
    std::cout << r3 << " = " << 4 << "*" << 6890241 << " = " << 4 * 6890241 << std::endl;
    int r4 = multiply(Q, k, 5, r);
    std::cout << r4 << " = " << 5 << "*" << 6890241 << " = " << 5 * 6890241 << std::endl;
    int r5 = multiply(Q, k, 6, r);
    std::cout << r5 << " = " << 6 << "*" << 6890241 << " = " << 6 * 6890241 << std::endl;
    int r6 = multiply(Q, k, 30, r);
    std::cout << r6 << " = " << 30 << "*" << 6890241 << " = " << 30 * 6890241 << std::endl;
    int r7 = multiply(Q_1, k_1, 30, r_1);
    std::cout << r7 << " = " << 30 << "*" << 25 << " = " << 30 * 25 << std::endl;
    int r8 = multiply(Q_1, k_1, 1245, r_1);
    std::cout << r8 << " = " << 1245 << "*" << 25 << " = " << 1245 * 25 << std::endl;
    int r9 = multiply(Q_1, k_1, 2, r_1);
    std::cout << r9 << " = " << 2 << "*" << 25 << " = " << 2 * 25 << std::endl;
    int r10 = multiply(Q_1, k_1, 1, r_1);
    std::cout << r10 << " = " << 1 << "*" << 25 << " = " << 1 * 25 << std::endl;
    int r11 = multiply(Q_2, k_2, 30, r_2);
    std::cout << r11 << " = " << 30 << "*" << 340 << " = " << 30 * 340 << std::endl;
    int r12 = multiply(Q_2, k_2, 1245, r_2);
    std::cout << r12 << " = " << 1245 << "*" << 340 << " = " << 1245 * 340 << std::endl;
    int r13 = multiply(Q_2, k_2, 2, r_2);
    std::cout << r13 << " = " << 2 << "*" << 340 << " = " << 2 * 340 << std::endl;
    int r14 = multiply(Q_2, k_2, 1, r_2);
    std::cout << r14 << " = " << 1 << "*" << 340 << " = " << 1 * 340 << std::endl;
}

void multBase_test()
{
    std::cout << "_________________________________________" << std::endl;
    std::cout << "mult_base tests" << std::endl;
    std::cout << " 1 * 2**1 + 1 = " << mult_base(3, 1) << std::endl;
    std::cout << " 1 * 2**4 - 1 = " << mult_base(15, 1) << std::endl;
    std::cout << " 1 * 2**4 + 1 * 2**2 - 1 = " << mult_base(19, 1) << std::endl;
    std::cout << " 1 * 2**4 + 1 = " << mult_base(17, 1) << std::endl;
    std::cout << " 1 * 2**5 - 1 = " << mult_base(31, 1) << std::endl;
}

void mult_test()
{
    Triplet Q[8];
    Triplet Q_1[8];
    Triplet Q_2[8];
    std::cout << "_________________________________________" << std::endl;
    std::cout << "mult tests" << std::endl;
    std::cout << mult(Q[0], 1) << std::endl;
    std::cout << mult(Q[1], 1) << std::endl;
    std::cout << mult(Q[2], 1) << std::endl;
    std::cout << mult(Q_1[1], 1) << std::endl;
    std::cout << mult(Q_2[1], 1) << std::endl;
}
