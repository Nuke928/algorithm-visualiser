﻿#include "ListButton.h"
#include "Button.h"
#include "IFont.h"
#include "IGraphics.h"
#include "IInput.h"
#include "IResourceManager.h"
#include <algorithm>
#include <SDL/SDL_opengl.h>

#undef DrawText

constexpr int minWidth = 100;

CListButton::CListButton(const CVector2f &&pos, const std::string &&text, std::initializer_list<std::string> items)
	: pos(pos)
	, text(text)
	, clicked(false)
	, font(nullptr)
	, hovered(false)
	, items(items)
	, active(false)
	, selectedItem(0)
{
	std::sort(this->items.begin(), this->items.end());
}

CListButton::~CListButton()
{
}

void CListButton::Initialize()
{
	font = resMgr->GetFont("data/res/font/ui.fnt");
	const CVector2f size = font->GetTextSize(text.c_str());
	rect = CRect(pos, std::max((int)size.x, minWidth), (int)size.y);

	/* Construct list buttons */
	float x = pos.x;
	float y = pos.y - (float)rect.height;
	for(const auto &item : items) {
		CButton *btn = new CButton(CVector2f(x, y), std::move(item));
		btn->Initialize();
		buttons.push_back(btn);
		y -= (float)btn->GetRect().height;
	}
}

void CListButton::Update(float dtTime)
{
	const auto &mouseState = input->GetMouseState();
	const auto &mouseStateDelta = input->GetMouseStateDelta();
	const CVector2f mousePos = { (float)mouseState.x, (float)mouseState.y };
	const CRect mouseRect = CRect(mousePos, 1, 1);

	hovered = mouseRect.Collides(rect);
	clicked = (mouseStateDelta.buttonMask & EMouseButton_LEFT);

	if(active) {
		int i = 0;
		for(auto btn : buttons) {
			btn->Update(dtTime);
			if(btn->Clicked())
				selectedItem = i;
			i++;
		}
	}

	if(clicked && !hovered)
		active = false;
	else if(clicked && hovered)
		active = !active;
}

void CListButton::Draw()
{
	CColor fg, bg;

	if(hovered || active) {
		fg = CColor(0, 0, 0);
		bg = CColor::white;
	} else {
		fg = CColor::white;
		bg = CColor(0, 0, 0);
	}
	graphics->DrawRect(rect, bg);
	graphics->DrawText(font, pos + CVector2f((float)rect.width / 2.0f, (float)rect.height / 2.0f), fg, text, true);

	/* Outline */
	glColor4ub(fg.r, fg.g, fg.b, fg.a);
	glBegin(GL_LINES);
		glVertex2f(rect.pos.x, rect.pos.y);
		glVertex2f(rect.pos.x+(float)rect.width, rect.pos.y);
		glVertex2f(rect.pos.x+(float)rect.width, rect.pos.y);
		glVertex2f(rect.pos.x+(float)rect.width, rect.pos.y+(float)rect.height);
		glVertex2f(rect.pos.x+(float)rect.width, rect.pos.y+(float)rect.height);
		glVertex2f(rect.pos.x, rect.pos.y+(float)rect.height);
		glVertex2f(rect.pos.x, rect.pos.y+(float)rect.height);
		glVertex2f(rect.pos.x, rect.pos.y);
	glEnd();

	if(active)
		for(auto btn : buttons)
			btn->Draw();
}
