﻿#pragma once

#include "IAlgorithm.h"

class CBubbleSort : public IAlgorithm
{
public:
			CBubbleSort() : halt(false) {}

	void		Run(CData *data);
	void		SetHalt() { halt = true; }
	bool		ShouldHalt() const { return halt; }
private:
	bool		halt;
};
