﻿#pragma once

#include "IAlgorithm.h"

class CInsertionSort : public IAlgorithm
{
public:
			CInsertionSort() : halt(false) {}

	void		Run(CData *data);
	void		SetHalt() { halt = true; }
	bool		ShouldHalt() const { return halt; }
private:
	bool		halt;
};
