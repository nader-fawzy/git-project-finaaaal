#pragma once

//This file contains data sturctures required to store all registration RULES
#include <vector>
using namespace std;
#include "DEFs.h"


//Information for each course
//Title, code, credit hours, and pre-req list, type
struct CourseInfo
{
	string Title;
	Course_Code	Code;
	vector<Course_Code> PreReqList;	//Pre-requesite list of courses codes
	vector<Course_Code> CoReqList;	//Co-requesite list of courses codes
	int Credits;
	string type;	//Univ, track, major course
};

struct AcademicYearOfferings
{
	string Year; //academic year of the offerings e.g. 2019-2020


	//Each year has an array of of 3 vectors of courses CODE. 
	//Each vector cossrsponds to a semester
	//So Offerings[FALL] is a vector of courses offered in FALL in THAT year
	//So Offerings[SPRING] is a vector of courses offered in SPRING in THAT year
	//So Offerings[SUMMER] is a vector of courses offered in SUMMER in THAT year
	vector<Course_Code> Offerings[SEM_CNT];
};

struct Rules	//contains all objects for registrations rules
{
	//TODO: add more fields if needed
	int TotalCr;
	int University_CompulsoryCr;
	int University_ElectiveCr;
	int Track_CompulsoryCr;
	//int Major_Commom_CompulsoryCr;
	//int Major_Commom_ElectiveCr;
	int Number_Of_Concentrations;
	//int Major_Concentration1_CompulsoryCr;
	int Major_Concentration1_ElectiveCr;

	vector<int>Major_Concentration_CompulsoryCr;
	vector<int>Major_Concentration_ElectiveCr;

	vector<CourseInfo> CourseCatalog;	//List of ALL courses with full info
	vector<AcademicYearOfferings> OffringsList;	//all offerings for all acedmic years

	int SemMinCredit;		//min no. of credit hours per semester
	int SemMaxCredit;		//max no. of credit hours per semester
	int ReqUnivCredits;		//total no. of credits req by Univ courses
	int ReqTrackCredits;	//total no. of credits req by Track courses
	int ReqMajorCredits;	//total no. of credits req by Major courses

	vector<Course_Code> UnivCompulsory;	//Univ Compulsory courses
	vector<Course_Code> UnivElective;	//Univ Elective courses

	vector<Course_Code> TrackCompulsory;//Track Compulsory courses
	vector<Course_Code> TrackElective;	//Track Elective courses (added for future)

	vector<Course_Code> MajorCompulsory;//Major Compulsory courses
	vector<Course_Code> MajorElective;	//Major Elective courses

};

