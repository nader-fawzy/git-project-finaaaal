#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"

//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	//plan is a list of academic years

	string PlanNotes;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	void virtual DrawMe(GUI*) const;
	bool DeleteCourse(int x_point, int y_point, int years, SEMESTER SEMs); //delete course
	Course* DetectCourse(int x_point, int y_point, int year, SEMESTER sem); //detect course position
	int setYearSem(int x);
	SEMESTER Sem(int x);
	/*bool add_course(Course* code, int year, SEMESTER sem);*/
	virtual ~StudyPlan();
};

