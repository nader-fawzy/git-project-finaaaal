#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
//#include "../Registrar.h"

//A full study plan for as student
struct Studyplan
{
	string year;
	string semster;
	vector <string> listofcoursecodes;

};
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	
	vector<AcademicYear*> plan;	//plan is a list of academic years
	string PlanNotes;
public:
	
	double* DeleteCourse(double x_point, double y_point);
	double* DetectCourse(double x_point, double y_point);
	double* Detect_Course(double xpoint, double ypoint);
	StudyPlan();
	//void studyplan(string filename, Registrar* file);
	bool AddCourse(Course*, int year, SEMESTER);
	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
};

