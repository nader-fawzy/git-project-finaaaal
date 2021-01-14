#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include <vector>
#include <list>
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
//delete course
bool AcademicYear::actiondeletecourse(int x_point, int y_point, SEMESTER SEMs) {
	//int* point = nullptr;
		for (ITERATOR = YearCourses[SEMs].begin(); ITERATOR != YearCourses[SEMs].end(); ITERATOR++) {
			Course* cpointer = *ITERATOR;   //cpointer it contains courses details
			
			graphicsInfo position = cpointer->getGfxInfo();   //function that detect the position of the rectangle course
			 
				if (x_point>position.x && x_point<position.x+80 && y_point > position.y && y_point <position.y+40) {
					
							TotalCredits = TotalCredits - cpointer->getCredits();
							YearCourses[SEMs].erase(ITERATOR);  
							delete *ITERATOR; //it will delete the selected course...
							return true;
						
				}
				
		}
		return true;
}
//detect course position
Course* AcademicYear::DetectPositionOfCourse(int x_point, int y_point, SEMESTER sem) {
	
	for (iter = YearCourses[sem].begin(); iter != YearCourses[sem].end(); iter++) {
		Course* coursepointer = *iter;
		graphicsInfo pos = coursepointer->getGfxInfo();   //function that detect the position of the rectangle course
		if (x_point > pos.x && x_point<pos.x + 80 && y_point > pos.y && y_point < pos.y + 40) {
			return coursepointer;
		}

	}
	return nullptr;
}
