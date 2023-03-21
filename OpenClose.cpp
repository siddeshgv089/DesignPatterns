#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

/*

In this example, we have an interface IFilter and three classes that implement it: EvenFilter, OddFilter, and PositiveFilter. Each filter determines whether a given integer meets a certain criteria.

We also have a class NumberFilter that takes a vector of integers and a filter as input. The Filter() method returns a vector of integers that meet the filter's criteria.

In main(), we create two instances of NumberFilter: one for even numbers and one for positive numbers. We pass in the numbers vector and the appropriate filter to each instance. We then iterate over the filtered numbers and print them out.

This design follows the Open/Closed Principle because we can add new filters without modifying the NumberFilter class. For example, we could add a PrimeFilter class that checks whether a number is prime. We could then create a new instance of NumberFilter with the PrimeFilter and filter the numbers for primes, without changing any existing code.

*/

class IFilter
{
public:
	virtual bool isValid(int value) = 0;
};

class EvenFilter : public IFilter
{
public:
	bool isValid(int value)
	{
		if (value % 2 == 0)
			return true;
		else
			return false;
	}
};

class OddFilter : public IFilter
{
public:
	bool isValid(int value)
	{
		if (value % 2 == 1)
			return true;
		else
			return false;
	}
};

class PositiveNumber : public IFilter
{
public:
	bool isValid(int value)
	{
		if (value > 0)
			return true;
		else
			return false;

	}
};

class NegativeFilter : public IFilter
{
public:
	bool isValid(int value)
	{
		if (value < 0)
			return true;
		else
			return false;
	}
};


class NumberFilter
{
private:
	std::vector<int> &nums;
	 IFilter &filter_;
public:
	NumberFilter(std::vector<int> &nums, IFilter &filter) : nums(nums),filter_(filter) {}

	std::vector<int> filterNum()
	{
		std::vector<int> res;

		for (auto i : nums)
		{
			if (filter_.isValid(i))
				res.push_back(i);
		}

		return res;
	}
};


int main()
{
	std::vector<int> vec{ 1,2,3,4,5,6,-1,-2,-3,5,-10 };

	EvenFilter even;

	NumberFilter numfil(vec, even);


	for (auto i : numfil.filterNum())
	{
		std::cout << i << std::endl;
	}

	NegativeFilter nf;
	NumberFilter numfilt2(vec, nf);

	for (auto i : numfilt2.filterNum())
	{
		std::cout << i << std::endl;
	}

	return 0;
}
