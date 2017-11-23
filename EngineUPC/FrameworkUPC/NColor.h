#pragma once

struct NColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	static NColor White;
	static NColor Red;
	static NColor Green;
	static NColor Blue;

	float NormalizedR() { return ((float)r) / 255.0f; }
	float NormalizedG() { return ((float)g) / 255.0f; }
	float NormalizedB() { return ((float)b) / 255.0f; }
	float NormalizedA() { return ((float)a) / 255.0f; }
};