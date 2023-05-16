#include <cstddef>
#include <iostream>
#include <thread>
#include <future>

// 50% more efficient than syncronous execution (on my machine)

/*
    The calculation of area has been split into 4 threads,
    as the result of each part is independent of each other.

    4 functions have been created diving the work
    instead of dividing the input range to increase
    the chance of equal workload distribution
*/

// function to be integrated
inline double func(double x)
{
    return x*x;
}

// partial integration for parallel execution
double integratePP1(double begin, double end, std::size_t bins = 1000000)
{
	double area = 0;
	double dx = (end - begin) / bins;
	for (double x = begin; x <= end; x += (4*dx))
	{
		double y = func(x);
		area += dx * y;
	}
	return area;
}

// partial integration for parallel execution
double integratePP2(double begin, double end, std::size_t bins = 1000000)
{
	double area = 0;
	double dx = (end - begin) / bins;
	for (double x = begin + dx; x <= end; x += (4*dx))
	{
		double y = func(x);
		area += dx * y;
	}
	return area;
}

// partial integration for parallel execution
double integratePP3(double begin, double end, std::size_t bins = 1000000)
{
	double area = 0;
	double dx = (end - begin) / bins;
	for (double x = begin + (2*dx); x <= end; x += (4*dx))
	{
		double y = func(x);
		area += dx * y;
	}
	return area;
}

// partial integration for parallel execution
double integratePP4(double begin, double end, std::size_t bins = 1000000)
{
	double area = 0;
	double dx = (end - begin) / bins;
	for (double x = begin + (3*dx); x <= end; x += (4*dx))
	{
		double y = func(x);
		area += dx * y;
	}
	return area;
}


// thread control and work distribution
void parallel_calculation()
{
    std::future<double> process1 = std::async(std::launch::async, integratePP1, 0, 9, 1000000);
    std::future<double> process2 = std::async(std::launch::async, integratePP2, 0, 9, 1000000);
    std::future<double> process3 = std::async(std::launch::async, integratePP3, 0, 9, 1000000);
    std::future<double> process4 = std::async(std::launch::async, integratePP4, 0, 9, 1000000);
    

    auto result1 = process1.get();
    auto result2 = process2.get();
    auto result3 = process3.get();
    auto result4 = process4.get();

    std::cout<< result1 + result2 + result3 + result4 << std::endl;

    
}

int main()
{
    const auto start_time = std::chrono::steady_clock::now();
    parallel_calculation();
    const auto end_time = std::chrono::steady_clock::now();
    
    const auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout<<elapsed_time.count()<<" microseconds"<< std::endl;
}