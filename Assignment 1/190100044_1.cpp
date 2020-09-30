#include <iostream>

// Used recursion
long long int J(long long int n, int k) {
  // If we have k=1, then we know only the last number would remain.
  // if (k == 1)
  //   return n - 1;
  // I realized it now that k is never 1 in input...

  // If n has reached 1, i.e. only 1 number is remaining then that is the
  // answer.
  if (n == 1)
    return 0;

  // If k is greater than n, we can use recursion one by one
  if (k > n)
    return (J(n - 1, k) + k) % n;

  // If n is greater than k, we use recursion by removing n / k elements in one go.
  long long int count = n / k;
  long long int result = J(n - count, k);
  result -= (n % k);

  // Shifting the number accordingly to get the final result
  if (result < 0)
    result += n;
  else
    result += result / (k - 1);

  return result;
}

int main() {
  //Initialize
  long long int n;
  int k;

  // Input
  std::cin >> n >> k;

  // Output
  std::cout << J(n, k) + 1 << std::endl;
  // +1 is because I had mistakenly started the numbers from 0, whereas in the
  // PS the numbers start from 1.

  return 0;
}

// Tested with large numbers:
// 123456789213456789 123456 gives result 86454349851819302 in 0.15s.

// Found later: https://cp-algorithms.com/others/josephus_problem.html
