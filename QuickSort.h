﻿#pragma once

#include "IAlgorithm.h"

class CQuickSort : public IAlgorithm
{
public:
	CQuickSort() : halt(false) {}

	void Run(CData *data);
	void SetHalt() { halt = true; }
	bool ShouldHalt() const { return halt; }
private:
	void Sort(CData *data, int begin, int end);
	bool halt;
};
