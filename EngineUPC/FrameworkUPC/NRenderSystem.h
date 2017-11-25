#pragma once

#include <vector>
#include <algorithm>
#include "NBaseDrawable.h"
#include "NDepthRenderTarget.h"

struct dtRenderDrawable {
	int Priority;
	NBaseDrawable* Drawable;

	bool static Sort (dtRenderDrawable i, dtRenderDrawable j) {
		return (i.Priority < j.Priority); 
	}
};

class NRenderSystem
{
public:
	NRenderSystem() {}
	~NRenderSystem() {}

	bool IsEnabled_Shadows;

	dtRenderDrawable AddDrawable(NBaseDrawable* drawable);
	dtRenderDrawable AddDrawable(NBaseDrawable* drawable, float priority);
	void RemoveDrawable(NBaseDrawable* drawable);
	void Sort() {
		std::sort(mDrawables.begin(), mDrawables.end(), 
			&dtRenderDrawable::Sort);
	}

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

private:
	std::vector<dtRenderDrawable> mDrawables;

	NDepthRenderTarget* mDepthRenderTarget;
};

