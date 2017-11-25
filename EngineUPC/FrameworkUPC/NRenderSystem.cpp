#include "NRenderSystem.h"
#include "GameFramework.h"
#include "DepthShader.h"

void NRenderSystem::Initialize() {
	IsEnabled_Shadows = false;
}

dtRenderDrawable NRenderSystem::AddDrawable(NBaseDrawable* drawable) {
	dtRenderDrawable render;
	render.Priority = 0;
	render.Drawable = drawable;

	mDrawables.push_back(render);

	return render;
}

dtRenderDrawable NRenderSystem::AddDrawable(NBaseDrawable* drawable, float priority) {
	dtRenderDrawable render;
	render.Priority = priority;
	render.Drawable = drawable;

	mDrawables.push_back(render);

	return render;
}

void NRenderSystem::RemoveDrawable(NBaseDrawable* drawable) {
	
}

void NRenderSystem::Update(float dt) {
	for (int i = 0; i < mDrawables.size(); i++) {
		dtRenderDrawable render = mDrawables.at(i);
		render.Drawable->Update(dt);
	}
}

void NRenderSystem::Draw(float dt) {
	if (IsEnabled_Shadows) {
		GameFramework* framework = GameFramework::GET_FRAMEWORK();

		if (mDepthRenderTarget == nullptr) {
			mDepthRenderTarget = framework->GetGraphicDevice()->CreateDepthRenderTarget(
				1024, 1024);
		}

		mDepthRenderTarget->Set();

		// Render to the depth texture with a special shader
		//const std::string baseShaderPath = "Shaders/DepthShader3D";
		//DepthShader* shader = framework->GetShaderManager()->
		//	LoadAndGetShader<DepthShader>(baseShaderPath);

		//for (int i = 0; i < mDrawables.size(); i++) {
		//	dtRenderDrawable render = mDrawables.at(i);

			//render.Drawable->Draw(dt);
		//}
	}

	for (int i = 0; i < mDrawables.size(); i++) {
		dtRenderDrawable render = mDrawables.at(i);
		render.Drawable->Draw(dt);
	}
}