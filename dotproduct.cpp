/**************************
** TDDD56 Lab 3
***************************
** Author:
** August Ernstsson
**************************/

#include <iostream>

#include <skepu2.hpp>

/* SkePU user functions */


float ProductFunc(float a, float b)
{
	return a*b;
}

float SumFunc(float a, float b)
{
	return a+b;
}


int main(int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <input size> <backend>\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
	auto spec = skepu2::BackendSpec{skepu2::Backend::typeFromString(argv[2])};
	spec.setCPUThreads(8);
	
	
	/* Skeleton instances */
	auto instancePROD = skepu2::Map<2>(ProductFunc);
	auto instanceSUM = skepu2::Reduce(SumFunc);
	auto instancedPRODSUM = skepu2::MapReduce<2>(ProductFunc , SumFunc);

	
	/* Set backend (important, do for all instances!) */
	instancePROD.setBackend(spec);
	instanceSUM.setBackend(spec);
	instancedPRODSUM.setBackend(spec);
	
	/* SkePU containers */
	skepu2::Vector<float> v1(size, 1.0f), v2(size, 2.0f), vres(size);
	
	/* Compute and measure time */
	float resComb, resSep;
	
	auto timeComb = skepu2::benchmark::measureExecTime([&]
	{
		resComb = instancedPRODSUM(v1, v2);
	});
	
	auto timeSep = skepu2::benchmark::measureExecTime([&]
	{
		instancePROD(vres, v1, v2);
		resSep = instanceSUM(vres);
	});
	//time combine
	//std::cout << (timeComb.count() / 10E6) << "\n";
	std::cout <<( timeSep.count() / 10E6) << "\n";
	
	return 0;
}

