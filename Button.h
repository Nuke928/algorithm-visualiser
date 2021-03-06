﻿#pragma once

#include "Rect.h"
#include "Vector2.h"
#include <string>

class IFont;

class CButton
{
public:
			CButton(const CVector2f &&pos, const std::string &&text);
			~CButton();

	void		Initialize();
	void		Update(float dtTime);
	void		Draw();

	void		SetText(const std::string &&text);
	bool		Clicked() const { return clicked; }

	const CRect &	GetRect() const { return rect; }
private:
	CVector2f	pos;
	std::string	text;
	bool		clicked;
	bool		hovered;
	CRect		rect;
	IFont *		font;
};
