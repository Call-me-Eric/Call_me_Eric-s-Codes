#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include <vector>

/**
 * @brief calculates the discrete convolution of two sequences 
 * @param a the first sequence
 * @param b the second sequence
 * @return the discrete convolution of @p a and @p b modular 998244353
 * 
 * Assume a.size()==n1 && b.size()==n2, then the function works in
 * O((n1+n2) log (n1+n2)) time and O(n1+n2) space. Besides, (n1+n2) must
 * NOT be greater than 8,388,608.
 */
std::vector<int> convolution(const std::vector<int> &a,const std::vector<int> &b);

#endif