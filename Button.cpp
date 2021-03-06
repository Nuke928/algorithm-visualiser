﻿#include "Button.h"
#include "IFont.h"
#include "IGraphics.h"
#include "IInput.h"
#include "IResourceManager.h"
#include <SDL/SDL_opengl.h>
#include <algorithm>

#undef DrawText

constexpr int minWidth = 100;

CButton::CButton(const CVector2f &&pos, const std::string &&text)
	: pos(pos)
	, text(text)
	, clicked(false)
	, font(nullptr)
	, hovered(false)
{
}

CButton::~CButton()
{
}

void CButton::Initialize()
{
	font = resMgr->GetFont("data/res/font/ui.fnt");
	const CVector2f size = font->GetTextSize(text.c_str());
	rect = CRect(pos, std::max((int)size.x, minWidth), (int)size.y);
}

void CButton::Update(float dtTime)
{
	const auto &mouseState = input->GetMouseState();
	const auto &mouseStateDelta = input->GetMouseStateDelta();
	const CVector2f mousePos = { (float)mouseState.x, (float)mouseState.y };
	const CRect mouseRect = CRect(mousePos, 1, 1);

	hovered = mouseRect.Collides(rect);
	if(hovered)
		clicked = (mouseStateDelta.buttonMask & EMouseButton_LEFT);
	else
		clicked = false;
}

void CButton::Draw()
{
	CColor fg, bg;

	if(hovered) {
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
}

void CButton::SetText(const std::string &&text)
{
	this->text = text;
	const CVector2f size = font->GetTextSize(text.c_str());
	rect = CRect(pos, std::max((int)size.x, minWidth), (int)size.y);
}
