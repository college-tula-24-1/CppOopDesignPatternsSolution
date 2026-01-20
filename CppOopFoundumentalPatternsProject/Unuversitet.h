#pragma once
#include <iostream>
#include <vector>

class Student
{
	int id;
	std::string name;
};

class Teacher;

class Modul
{
	int id;
	std::string title;
	std::vector<Teacher*> teachers;
	std::vector<Student*> students;
};

class Faculty;

class Teacher
{
	int id;
	std::string name;
	std::vector<Modul*> modules;
	std::vector<Faculty*> faculties;
};

class Faculty
{
	int id;
	std::string title;
	std::vector<Teacher*> teachers;
	Teacher* dekan;
	std::vector<Modul*> modules;
};

class Universitet
{
	std::string title;
	std::vector<Faculty*> faculties;
};









