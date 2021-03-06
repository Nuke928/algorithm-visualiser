﻿#pragma once

class IFont;

#include "Rect.h"
#include "Vector2.h"
#include <string>

class CSlider
{
public:
			CSlider(int min, int max, int current, const CVector2f &&pos, const std::string &&text);
			~CSlider();

	void		Initialize();
	void		Update(float dtTime);
	void		Draw();

	int		GetValue() const { return currentValue; }
private:
	CVector2f	pos;
	int		min;
	int		max;
	int		currentValue;
	IFont *		font;
	CRect		rect;
	std::string	text;
};
