#include "StudyPlan.h"
#include "AcademicYear.h"
//#include "../Registrar.h"
#include <fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>
#include "../Rules.h"
#include "..\Actions\Action.h"

using namespace std;



StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}

StudyPlan::~StudyPlan()
{
}

/*void StudyPlan::studyplan(string filename, Registrar* file) // function to import study plan //load studyplan
{
	fstream studyplan;
	studyplan.open(filename);

	Studyplan year1;
	string data;
	string year;
	string semster;
	string tempyearcourses;
	string yearcourses_part;
	 
	while (getline(studyplan, data));    //to loop the data in lines of the txt file
	{  stringstream ss(data);
	getline(ss, year, ' ');
	getline(ss, year, ',');
	int y = stoi(year);          //function to store an integer as a string
	getline(ss, semster, ',');
	SEMESTER sem;                       //enum semster
	if (semster == "Fall" )  //in file  
	{
	    sem = FALL;     //in enum 
	}
	else if (semster == "Spring") { sem = SPRING; }
	else sem = SUMMER;
	while (getline(ss, yearcourses_part, ','))

	{
		CourseInfo* temp = file->getcourseinfo(yearcourses_part);
		if (temp) {
			Course* pC = new Course(temp->Code, temp->Title, temp->Credits);
			AddCourse(pC, y, sem);
		}

	}

	CourseInfo* temp = file->getcourseinfo(ss.string());
	if (temp) {
		Course* pC = new Course(temp->Code, temp->Title, temp->Credits);
		AddCourse(pC, y, sem);
	}

	}


}*/


double* StudyPlan::DeleteCourse(double x_point, double y_point) {
	double* point = NULL;
	for (int i = 0; i < 5; ++i) {
		point = plan[i]->actiondeletecourse(x_point, y_point);  //plan is list of academic years,
		if (point != NULL) {
			return point;
			break;
		}
	}
	return point;
}
double* StudyPlan::DetectCourse(double x_point, double y_point) {
	double* pointPointer = NULL;
	for (int n = 0; n < 5; ++n) {
		pointPointer = plan[n]->DetectPositionOfCourse(x_point, y_point);
		if (pointPointer != NULL) {
			return pointPointer;
			break;
		}
		
	}
}
double* StudyPlan::Detect_Course(double xpoint, double ypoint) {
	double* pointPointer = NULL;
	for (int n = 0; n < 5; ++n) {
		pointPointer = plan[n]->Detect_Position_Of_Course(xpoint, ypoint);
		if (pointPointer != NULL) {
			return pointPointer;
			break;
		}
	}
}