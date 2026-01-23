#pragma once
#include <iostream>
#include <string>

namespace AdapterNamespace
{
	class Interface
	{
	public:
		virtual std::string Method() = 0;
		virtual ~Interface() = default;
	};

	class ConcreteClassA : public Interface
	{
		int value;
	public:
		ConcreteClassA(int value = 0) : value{ value } {}
		int& Value() { return value; }

		//

		std::string Method() override
		{
			return "Class A. Value = " + std::to_string(value);
		}
	};

	class ConcreteClassB : public Interface
	{
		int value;
	public:
		ConcreteClassB(int value = 0) : value{ value } {}
		int& Value() { return value; }

		//

		std::string Method() override
		{
			return "Class B. Value = " + std::to_string(value);
		}
	};


	class Service
	{
		int data;
	public:
		int ServiceMethod(int data)
		{
			return 1000 * data;
		}
	};

	class ServiceAdapter : public Interface
	{
		Service* service;
		int data;
	public:
		ServiceAdapter(Service* service, int data) 
			: service{ service }, data{ data } {}

		std::string Method() override
		{
			return "Class Service. Value = "
				+ std::to_string(service->ServiceMethod(data));
		}
	};


	class Client
	{
	public:
		void ClientCode(Interface* source)
		{
			std::cout << source->Method() << "\n";
		}
	};


	// Sensor
	class ISensor
	{
	public:
		virtual double GetSensorData() = 0;
	};

	class SensorCelsium : public ISensor
	{
	public:
		double GetSensorData() override
		{
			return -20 + rand() % 40;
		}
	};

	class SensorPressure : public ISensor
	{
	public:
		double GetSensorData() override
		{
			return 400 + rand() % 400;
		}
	};

	class SensorClient
	{
	public:
		void PrintSensorData(ISensor* sensor)
		{
			std::cout << sensor->GetSensorData() << "\n";
		}
	};

	class SensorFahrenheit
	{
	public:
		double GetTemperature()
		{
			return -4 + rand() % 72;
		}
	};

	class SensorFahrenheitAdapter : public ISensor
	{
		SensorFahrenheit* sensorFahrenheit;
	public:
		SensorFahrenheitAdapter(SensorFahrenheit* sensorFahrenheit)
			: sensorFahrenheit{ sensorFahrenheit }{}

		double GetSensorData() override
		{
			return (sensorFahrenheit->GetTemperature() - 32) * 5 / 9;
		}
	};
}


