#pragma once
#include "core/Application.h"

class Skeleton;

class CCDSolver {
public:
	CCDSolver();
	~CCDSolver();

	void update(float delta_time, Skeleton* skeleton, GameObject* target);
};

