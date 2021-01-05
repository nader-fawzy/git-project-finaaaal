#pragma once
#include "Actions\Action.h"
class ActionReorderCourses : public Action
{
public:
	ActionReorderCourses(Registrar *);
	void swapFunction(double *PointerOnFirstCourse, double *PointerOnSecCourse);
	bool Execute();
	virtual ~ActionReorderCourses();
};

