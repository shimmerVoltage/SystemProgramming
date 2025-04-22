#include<Windows.h>
#include<iostream>
#include<conio.h>
using namespace std;

#define Enter		13
#define Escape		27

#define MIN_TANK_CAPACITY	20
#define MAX_TANK_CAPACITY	120

class Tank
{
	double fuel_level;
public:
	const int CAPACITY;
	double get_fuel_level()const
	{
		return fuel_level;
	}
	Tank(int capacity):CAPACITY
		(
			capacity < MIN_TANK_CAPACITY ? MIN_TANK_CAPACITY :
			capacity > MAX_TANK_CAPACITY ? MAX_TANK_CAPACITY :
			capacity
		),
		fuel_level(0)
	{
		cout << "Tank: ";
		if (capacity < MIN_TANK_CAPACITY)cout << "Min capacity was applied" << endl;
		if (capacity > MAX_TANK_CAPACITY)cout << "Max capacity was applied" << endl;
		//this->CAPACITY = capacity;
		//this->fuel_level = 0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}
	double fill(double amount)
	{
		if (amount < 0)return fuel_level;
		fuel_level += amount;
		if (fuel_level >= CAPACITY)
		{
			fuel_level = CAPACITY;
			cout << "Full Tank" << endl;
		}
		return fuel_level;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	void info()const
	{
		cout << "Capacity:\t\t" << CAPACITY << "\tliters.\n";
		cout << "Fuel level:\t\t" << fuel_level << "\tliters.\n";
	}
};

#define MIN_ENGINE_CONSUMPTION		3
#define MAX_ENGINE_CONSUMPTION		25	

class Engine
{
	const double CONSUMPTION;
	const double DEFAULT_CONSUMPTION_PER_SECOND;	
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	Engine(double consumption):
		CONSUMPTION
		(
			consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
			consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
			consumption
		),
		DEFAULT_CONSUMPTION_PER_SECOND(CONSUMPTION * 3e-5),
		consumption_per_second(DEFAULT_CONSUMPTION_PER_SECOND)
	{
		is_started = false;
		cout << "Engine is ready..." << endl;
	}
	~Engine()
	{
		cout << "Engine is over!" << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info()const
	{
		cout << "Consumption:\t\t" << CONSUMPTION << " liters/100km" << endl;
		cout << "Default Consumption:\t" << DEFAULT_CONSUMPTION_PER_SECOND << " liters/s" << endl;
		cout << "Consumption:\t\t" << consumption_per_second << " liters/s" << endl;
	}
};

#define MAX_SPEED_LOWER_LIMIT	130
#define MAX_SPEED_HIGHER_LIMIT	408

class Car
{
	Engine engine;
	Tank tank;
	int speed;
	const int MAX_SPEED;
	bool driver_inside;
public:
	Car(double consumption, int capacity, int max_speed = 250):
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOWER_LIMIT ? MAX_SPEED_LOWER_LIMIT:
			max_speed > MAX_SPEED_HIGHER_LIMIT ? MAX_SPEED_HIGHER_LIMIT:
			max_speed
		),
		engine(consumption),
		tank(capacity),
		speed(0)
	{
		driver_inside = false;
		cout << "Your car is ready to go, press 'Enter' to get in ;-)" << endl;
	}
	~Car()
	{
		cout << "The car is over" << endl;
	}
	void get_in()
	{
		driver_inside = true;
		panel();
	}
	void get_out()
	{
		driver_inside = false;
	}
	void control()
	{
		char key = 0;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				driver_inside ? get_out() : get_in();
				break;
			}
		} while (key != Escape);
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level: " << tank.get_fuel_level() << " liters" << endl;
			cout << "Engine is " << (engine.started() ? "started " : "stopped") << endl;
			cout << "Speed:\t" << speed << " km/h" << endl;
			Sleep(100);
		}
	}
	void info()const
	{
		engine.info();
		tank.info();
		cout << "Speed:\t\t" << speed << " km/h" << endl;
		cout << "MaxSpeed\t" << MAX_SPEED << " km/h" << endl;
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
#ifdef TANK_CHECK
	setlocale(LC_ALL, "");
	Tank tank(80);
	double fuel;
	do
	{
		cout << "Укажите количество бензина: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK

	Engine engine(10);
	engine.info();

#endif // ENGINE_CHECK

	Car bnv(10, 80, 270);
	//bnv.info();
	bnv.control();
	
}