﻿#pragma once

#include <atomic>

class CData;

extern std::atomic<int> sleepTime;

struct IAlgorithm
{
	virtual		~IAlgorithm() {}
	virtual void	Run(CData *data) = 0;
	virtual void	SetHalt() = 0;
	virtual bool	ShouldHalt() const = 0;
};
