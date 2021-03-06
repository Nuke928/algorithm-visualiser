﻿#pragma once

#include "IAlgorithm.h"

class CRadixSort : public IAlgorithm
{
public:
			CRadixSort() : halt(false) {}

	void		Run(CData *data);
	void		SetHalt() { halt = true; }
	bool		ShouldHalt() const { return halt; }
private:
	bool		halt;
};
