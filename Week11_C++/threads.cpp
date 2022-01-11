#include "threads.h"
/*
* The function print I love threads
*/
void I_Love_Threads()
{
    std::cout << "I love threads" << std::endl;
}
/*
* The function call I love threads using a thread.
*/
void call_I_Love_Threads()
{
    std::thread t(I_Love_Threads);
    t.join();
}
/*
* The function print the vector.
*/
void printVector(std::vector<int> primes)
{
    for (std::vector<int>::iterator it = primes.begin(); it != primes.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
/*
* The function gets the primes using the beginning and ending.
*/
void getPrimes(int begin, int end, std::vector<int>& primes)
{
    bool isPrime = true;
    while (begin < end)
    {
        isPrime = true;
        if (begin == 0 || begin == 1)
        {
            isPrime = false;
        }
        else
        {
            for (int i = 2; i <= begin / 2; ++i)
            {
                if (begin % i == 0)
                {
                    isPrime = false;
                    break;
                }
            }
        }
        if (isPrime)
            primes.push_back(begin);
        begin++;
    }
}
/*
* The function return the primes.
*/
std::vector<int> callGetPrimes(int begin, int end)
{
    std::vector<int> primes;
    auto start = std::chrono::high_resolution_clock::now();
    std::thread numsOfTread(getPrimes, begin, end, ref(primes));
    numsOfTread.join();
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> done = stop - start;
    std::cout << "Time is: " << done.count() << std::endl;
    return primes;
}
/*
* The function write the primes to the giving file.
*/
void writePrimesToFile(int begin, int end, std::ofstream& file)
{
    std::string word;
    std::vector<int> p = callGetPrimes(begin, end);
    for (int i = 0; i < p.size(); i++)
    {
        file << p[i];
        file << "\n";
    }
}
/*
* The function Write Primes using Multiple Threads.
*/
void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N)
{
    std::ofstream file;
    file.open(filePath);
    std::thread* threads = new std::thread[N];
    int newPart = (end - begin) / N;
    int rest = (end - begin) % N;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
        {
            threads[i] = std::thread(writePrimesToFile, begin, end + rest, ref(file));
        }
        else
        {
            threads[i] = std::thread(writePrimesToFile, begin, begin + newPart, ref(file));
        }
        //std::thread t(writePrimesToFile, begin, begin + newPart, ref(file));
        begin = +newPart;
    }
    for (int i = 0; i < N; i++)
    {
        threads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> done = stop - start;
    std::cout << "All the time for all the threads is: " << done.count() << std::endl;
    file.close();
}