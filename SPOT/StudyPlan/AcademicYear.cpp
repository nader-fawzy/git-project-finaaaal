#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include "StudyPlan.h"
#include <list>
#include <vector>
#include <iostream>
using namespace std;
AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete

	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}

double* AcademicYear::actiondeletecourse(double x_point, double y_point) {
	double* point = NULL;
	for (int i = 0; i < 3 ; ++i) {  //loop on array of four
		
		for (auto ITERATOR = YearCourses[i].begin(); ITERATOR != YearCourses[i].end(); ITERATOR++) {
			Course* cpointer = *ITERATOR;   //cpointer it contains courses details
			double* position = cpointer->getpositionofcourse();   //function that detect the position of the rectangle course
			for (double X = position[0]; X < position[1] + 1; X++) {   //loop on x point
				if (x_point == X) {
					for (double Y = position[2]; Y < position[3] + 1; Y++) {   //loop on y point
						if (y_point == Y) {
							point = position;
							double RectanglePoint[4] = { position[0], position[1], position[2], position[3] };
							TotalCredits = TotalCredits - cpointer->getCredits();
							YearCourses[i].erase(ITERATOR);   //it will delete the selected course
							return RectanglePoint;
							break;
						}
					}
					break;
				}
			}
			if (point != NULL) {
				break;
			}
		}
		if (point != NULL) {
			break;
		}
	}
	return point;
}

double* AcademicYear::DetectPositionOfCourse(double x_point, double y_point) {
	double* p = NULL;
	for (int j = 0; j < 3; ++j) {

		for (auto iter = YearCourses[j].begin(); iter != YearCourses[j].end(); iter++) {
			Course* coursepointer = *iter;
			double* pos = coursepointer->getpositionofcourse(); //get position of the course
			for (double X_point = pos[0]; X_point < pos[1] + 1; ++X_point) {
				if (X_point == x_point) {
					for (double Y_point = pos[2]; Y_point < pos[3] + 1; ++Y_point) {
						if (Y_point == y_point) {
							p = pos;
							double coursepoints[4] = { pos[0], pos[1], pos[2], pos[3] };
							//TotalCredits = TotalCredits - coursepointer->getCredits();
							
							return coursepoints;
							break;
						}
					}
					break;
				}
			}
			if (p != NULL) {
				break;
			}
		}
		if (p != NULL) {
			break;
		}
	}
	return p;
}
double* AcademicYear::Detect_Position_Of_Course(double xpoint, double ypoint) {
	double* p = NULL;
	for (int j = 0; j <= 2; ++j) {

		for (auto iter = YearCourses[j].begin(); iter != YearCourses[j].end(); iter++) {
			Course* coursepointer = *iter;
			double* pos = coursepointer->getpositionofcourse(); //get position of the course
			for (double X_point = pos[0]; X_point < pos[1] + 1; ++X_point) {
				if (X_point == xpoint) {
					for (double Y_point = pos[2]; Y_point < pos[3] + 1; ++Y_point) {
						if (Y_point == ypoint) {
							p = pos;
							double course_points[4] = { pos[0], pos[1], pos[2], pos[3] };
							//TotalCredits = TotalCredits - coursepointer->getCredits();

							return course_points;
							break;
						}
					}
					break;
				}
			}
			if (p != NULL) {
				break;
			}
		}
		if (p != NULL) {
			break;
		}
	}
	return p;
}



void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}