#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <chrono>
#include <time.h>
#include <sys/time.h>

using namespace std;
using cho_clk = std::chrono::high_resolution_clock;

const string SEPERATOR(42, '#');
constexpr int HASH_TABLE_SIZE = 100; // 60 is also fine

// uses a hash map to keep some of the privious calculation results. The hash map size is restricted to HASH_TABLE_SIZE.
// when the code goes to do the calculations for a specific input, it first looks for that input in the hash map, 
// if it was not found, the recursive function calls would take place, otherwise, the result is retrieved from the hash map and 
// a significant cut happens in the number of calls to the optimizedRecursiveF().   
long long int optimizedRecursiveF(long long int n, map<long long int, long long int> *hash)
{
    if (n == 0 || n == 1 || n == 2 || n == 4 || n == 8)
        return 1;
    if (n == 3 || n == 5 || n == 6 || n == 10)
        return 2;
    if (n == 7 || n == 9)
        return 3;

    // first check the hash map
    auto it = hash->find(n);
    if (it != hash->end())
        return get<1>(*it);

    auto half = n / 2;
    auto ret = optimizedRecursiveF(half, hash);

    if (n % 2 == 1)
        ret += optimizedRecursiveF(half - 1, hash);

    if (hash->size() < HASH_TABLE_SIZE)
        hash->insert(make_pair(n, ret));
    return ret;
}

long long int recursiveF(long long int n)
{
    if (n == 0 || n == 1 || n == 2 || n == 4 || n == 8)
        return 1;
    if (n == 3 || n == 5 || n == 6 || n == 10)
        return 2;
    if (n == 7 || n == 9)
        return 3;

    auto half = n / 2;
    auto ret = recursiveF(half);

    if (n % 2 == 1)
        ret += recursiveF(half - 1);
    return ret;
}

int main(int argc, char **argv)
{
    long long int n = 123456789012345678;
    if (argc > 1)
    {
        stringstream ss;
        ss << argv[1];
        ss >> n;
    }
    
    map<long long int, long long int> hash;
    cout << SEPERATOR << endl
         << "n: " << n << "\n\n"
         << "running OPTIMIZED recursive implementation ..."
         << "\n\n";

    // call the optimized recursive implementation
    auto begin_opt = cho_clk::now();
    auto ret_opt = optimizedRecursiveF(n, &hash);
    auto end_opt = cho_clk::now();

    auto elapsed_opt = std::chrono::duration_cast<std::chrono::milliseconds>(end_opt - begin_opt);
    cout << "[optimized recursive implementation]" << endl
         << "result: " << std::dec << ret_opt << endl
         << "wall-time: " << elapsed_opt.count() * 1e-3
         << "\n\n";

    cout << "running NON-OPTIMIZED recursive implementation ..." << "\n\n";

    // call the non-optimized recursive implementation
    auto begin = cho_clk::now();    
    auto ret = recursiveF(n);
    auto end = cho_clk::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "[non-optimized recursive implementation]" << endl
         << "result: " << std::dec << ret << endl
         << "wall-time: " << elapsed.count() * 1e-3 << endl
         << SEPERATOR << endl;

    return 0;
}