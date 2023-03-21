#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>


/*
S - Single responsibility
O - Open for extension and closed for modification
L - Liskov substitution principle
I - Interface segregation 
D - Dependency Inversion
*/

//Example explaining the single responsibility principle

/*

BRIEF - Car has engine , Engine has functionality of starting and stopping the Car.
		Car knows how to drive or ride from point A to point B.

		Engine has a reponsibility of starting and stopping 
		Car responsibility is to Utilize Engine and drive the car.


*/

class Engine
{
public:
	Engine()
	{
		std::cout << "Engine created " << std::endl;
	}

	void start()
	{
		std::cout << "Engine started " << std::endl;
	}

	void stop()
	{
		std::cout << "Engine stopped " << std::endl;
	}
};

class Car
{
public:
	Car(Engine & e) : e(e) {}
	void drive()
	{
		std::cout << "Driving the car" << std::endl;
	}

private:
	Engine& e;
};

int main()
{

	Engine e;
	Car c(e);
	e.start();
	c.drive();
	e.stop();

	return 0;
}

/*
BRIEF :

Suppose you're developing a class called FileWriter that writes data to a file. The FileWriter class has several methods, including open(), writeData(), and close(). These methods are responsible for opening and closing the file, and for writing data to the file, respectively.

However, according to the SRP, each class should have only one responsibility. In this case, the FileWriter class has multiple responsibilities: it writes data to a file and also handles file I/O operations. To adhere to the SRP, we can refactor the code and separate the file I/O-related responsibilities into a separate class, such as File

By separating the file I/O-related responsibilities into a separate class, we have adhered to the SRP. Now the FileWriter class only writes data to a file, while the File class only handles file I/O operations. This separation of concerns makes the code easier to maintain, test, and modify.
*/

class File
{
public: 
	File(std::string filename) : filename(filename) {}

	void open()
	{
		ofs.open(filename, std::ios::app | std::ios::in | std::ios::out);
	}

	void write(std::string data)
	{
		ofs.write(data.c_str(),strlen(data.c_str()));
	}

	void close()
	{
		ofs.close();
	}

	std::string read()
	{
		char data[1024];
		ofs.read(data, 1024);

		return std::string(data);
	}


private:
	std::fstream ofs;
	std::string filename;
};

class FileWriter
{
private:
	File& f;
public:

	FileWriter(File &f) : f(f){}

	void writeData(std::string data)
	{
		f.write(data);
	}
};

int main()
{
	File f("writer.txt");
	f.open();
	FileWriter fw(f);
	fw.writeData("hello filewriter");
	f.close();

	return 0;
}

/*
BRIEF :

In this example, we have three classes: Customer, CustomerRepository, and CustomerService.

The Customer class has a single responsibility, which is to store the customer's data such as name, email, and age.

The CustomerRepository class is responsible for managing the database, including adding and removing customers from the database, and retrieving customers based on age.

The CustomerService class provides high-level operations such as registering and unregistering a customer. It uses the CustomerRepository class to perform database operations.

Each class has a clear and single responsibility, which makes the code easier to understand, test, and maintain. For example, if we want to change the database system, we only need to modify the CustomerRepository class, without affecting the Customer and CustomerService classes.


*/


class Customer
{
private:
	std::string name;
	std::string email;
	int age;

public:
	Customer(std::string name, std::string email, int age) : name(name), email(email), age(age) {}

	std::string getEmail() const { return email; }
	std::string getName() const { return name;  }
	int getAge() const { return age; }

};

class CustomerRepo
{
private:
	std::vector<Customer*> repo;
public:
	void AddCustomer(Customer* c) {
		repo.push_back(c);
	}

	void removeCustomer(Customer& c)
	{
		for (std::vector<Customer*>::iterator it = repo.begin(); it != repo.end(); it++)
		{
			if ((*it)->getName() == c.getName())
			{
				it = repo.erase(it);
			}
		}
	}

	void listCustomers()
	{
		std::cout << "size = " << repo.size() << std::endl;
		for (auto i : repo)
		{
			std::cout << i->getAge() << ", " << i->getName() << ", " << i->getEmail() << std::endl;
		}
	}
};


class CustomerService
{
private:
	CustomerRepo custrepo;

public:
	void RegisterCustomer(std::string name, std::string email, int age)
	{
		Customer* c = new Customer(name, email, age);
		custrepo.AddCustomer(c);
	}

	void UnregisterCustomer(std::string name, std::string email, int age)
	{
		Customer c(name, email, age);
		custrepo.removeCustomer(c);
	}

	void listCustomers()
	{
		custrepo.listCustomers();
	}

};


int main()
{
	CustomerService customerService;
	customerService.RegisterCustomer("John", "john@example.com", 35);
	customerService.RegisterCustomer("peppa", "peppa@example.com", 35);
	customerService.RegisterCustomer("pig", "pig@example.com", 35);
	customerService.listCustomers();
	customerService.UnregisterCustomer("John", "john@example.com", 35);
	customerService.listCustomers();

	return 0;
}
