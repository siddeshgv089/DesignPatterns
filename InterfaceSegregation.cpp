#include<iostream>
#include<vector>


class IPrinter
{
public:
	virtual void print() = 0;
};

class IScanner
{
public:
	virtual void scan() = 0;
};

class IFax
{
public:
	virtual void fax() = 0;
};

class IMultifunctionDevice : public IPrinter, public IScanner, public IFax
{
};


class Printer : public IPrinter
{
	// Inherited via IPrinter
	virtual void print() override
	{
		std::cout << "Im a printer " << std::endl;
	}
	//implement printer
};

class Scanner : public IScanner
{
	// Inherited via IScanner
	virtual void scan() override
	{
		std::cout << "Im a scanner " << std::endl;
	}
	//implement scanner
};

class Fax : public IFax
{
	// Inherited via IFax
	virtual void fax() override
	{
		std::cout << "Im a faxer " << std::endl;
	}
	//implement fax
};

class MultifunctionDevice : public IMultifunctionDevice
{
private:
	IPrinter &printer;
	IScanner &scanner;
	IFax &faxer;

public:

	MultifunctionDevice(IPrinter &printer_, IScanner &scanner_, IFax &fax_) : printer(printer_),scanner(scanner_),faxer(fax_) {}

	


	// Inherited via IMultifunctionDevice
	virtual void print() override
	{
		printer.print();
	}

	virtual void scan() override
	{
		scanner.scan();
	}

	virtual void fax() override
	{
		faxer.fax();
	}

};

int main()
{

	Printer print;
	Scanner scan;
	Fax fax;

	MultifunctionDevice mfd(print, scan, fax);
	mfd.print();
	mfd.scan();
	mfd.fax();

	return 0;
}
