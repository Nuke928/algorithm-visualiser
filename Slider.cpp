﻿#include "Slider.h"
#include "IFont.h"
#include "IGraphics.h"
#include "IInput.h"
#include "IResourceManager.h"
#include "MathUtil.h"
#include <SDL/SDL_opengl.h>

#undef DrawText

constexpr int sliderWidth = 200;
constexpr int sliderHeight = 10;

CSlider::CSlider(int min, int max, int current, const CVector2f &&pos, const std::string &&text)
	: min(min)
	, max(max)
	, currentValue(current)
	, pos(pos)
	, text(text)
{
}

CSlider::~CSlider()
{
}

void CSlider::Initialize()
{
	font = resMgr->GetFont("data/res/font/slider.fnt");
	CVector2f textOffset = font->GetTextSize(text.c_str());
	rect = CRect(pos + CVector2f(textOffset.x + 30.0f, 0.0f), sliderWidth, sliderHeight);
}

void CSlider::Update(float dtTime)
{
	const auto &mouseStateDelta = input->GetMouseState();
	const CVector2f mousePos = { (float)mouseStateDelta.x, (float)mouseStateDelta.y };
	const CRect mouseRect = CRect(mousePos, 1, 1);

	float selectionOffset = 30.0f;
	CRect selectionRect(rect.pos - CVector2f(selectionOffset, selectionOffset), sliderWidth + 2 * (int)selectionOffset, sliderHeight + 2 * (int)selectionOffset);
	if((mouseStateDelta.buttonMask & EMouseButton_LEFT) && mouseRect.Collides(selectionRect)) {
		float dx = mousePos.x - rect.pos.x;
		currentValue = (int)((dx / (float)rect.width) * this->max) + min;
	}

	currentValue = Math::Clamp(currentValue, min, max);
}

void CSlider::Draw()
{
	CColor fg = CColor::white;

	float width = ((float)(currentValue-this->min)/ (float)this->max) * (float)sliderWidth;
	graphics->DrawRect(CRect(rect.pos, (int)width, sliderHeight), fg);

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

	graphics->DrawText(font, rect.pos + CVector2f((float)sliderWidth / 2.0f, 2.0f * (float)sliderHeight), fg, std::to_string(currentValue), true);
	graphics->DrawText(font, pos - CVector2f(0.0f, (float)sliderHeight / 2.0f), fg, text, false);
}
