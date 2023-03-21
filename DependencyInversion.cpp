#include<iostream>]
#include<vector>


class IReader
{
public:
	virtual std::string read() = 0;
};

class Reader : public IReader
{
public:


	// Inherited via IReader
	virtual std::string read()
	{
		return "Hello DIP";
	}

};


class DataProcessor
{
private:

	IReader& reader_;


public:

	DataProcessor(IReader& reader) :reader_(reader) {}

	void processData()
	{
		std::cout << reader_.read();
	}

};

int main()
{
	Reader read;

	DataProcessor dp(read);
	dp.processData();

	return 0;
}
