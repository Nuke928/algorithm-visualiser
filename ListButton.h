﻿#pragma once

#include "Rect.h"
#include "Vector2.h"
#include <string>
#include <vector>

class CButton;
class IFont;

class CListButton
{
public:
			CListButton(const CVector2f &&pos, const std::string &&text, std::initializer_list<std::string> items);
			~CListButton();

	void		Initialize();
	void		Update(float dtTime);
	void		Draw();

	bool		Clicked() const { return clicked; }

	const CRect &	GetRect() const { return rect; }
	const std::string &GetSelectedItem() { return items[selectedItem]; }
private:
	CVector2f	pos;
	std::string	text;
	bool		clicked;
	bool		hovered;
	bool		active;	/* are we showing the list */
	CRect		rect;
	IFont *		font;
	int		selectedItem;
	std::vector<std::string> items;
	std::vector<CButton *> buttons;
};
