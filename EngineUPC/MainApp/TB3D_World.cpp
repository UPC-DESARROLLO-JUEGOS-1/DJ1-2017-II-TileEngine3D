#include "TB3D_World.h"

#include "TB3D_Engine.h"
#include "TB3D_Player.h"
#include <FrameworkUPC\GameFramework.h>
#include <FrameworkUPC\BasicLightingShader.h>

const int TB3D_World::TILE_EMPTY = 0;
const int TB3D_World::TILE_BLOCK = 1;
const int TB3D_World::TILE_PLAYER = 9;

TB3D_World::TB3D_World(TB3D_Engine* engine)
{
	mEngine = engine;
	mTileSize = mEngine->GetTileSize();

	mWorldPhysics = new TB3D_WorldPhysics(this);

	// Set lights in Shader
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	const std::string baseShaderPath = "Shaders/BasicLightingShader";
	BasicLightingShader* shader = shaderManagment->LoadAndGetShader<BasicLightingShader>(baseShaderPath);
	shader->SetLight0("light0");
	shader->SetLight1("light1");

	shader->GetLight1()->SetLightColor(NColor::Red);
	shader->GetLight1()->SetIntensity(0.3f);
}

TB3D_World::~TB3D_World()
{

}

void TB3D_World::Initialize() {
	std::vector<std::vector<int>> worldCollisions = mEngine->GetWorldConfig()->WorldCollisions();

	int rows = worldCollisions.size();
	int cols = worldCollisions[0].size();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			int tileData = worldCollisions[r][c];

			CreateObject(tileData, c, r);
		}
	}

	mWorldPhysics->Initialize(worldCollisions);

	BaseCamera* camera = mEngine->GetCamera()->GetRenderCamera();

	// plane
	mPlane = new NPrimitivePlane3D();
	mPlane->Initialize(40, 0, 30, 80, 60);
	mPlane->SetColor(NColor::White);
	mPlane->SetRenderCamera(camera);
	mPlane->SetRotationX(1.57f);
	mPlane->SetY(-2.0f);

	mDrawables.push_back(mPlane);
}

void TB3D_World::CreateObject(int tileID, int c, int r) {
	float posX = c * mTileSize;
	float posY = 0.0;
	float posZ = r * mTileSize;
	BaseCamera* camera = mEngine->GetCamera()->GetRenderCamera();

	switch (tileID) {
	case TB3D_World::TILE_BLOCK:
		{
			NPrimitiveCube3D* cube = new NPrimitiveCube3D();
			cube->Initialize(posX, posY, posZ, mTileSize, mTileSize, mTileSize);
			cube->SetRenderCamera(camera);
			//cube->SetRotationX(3.14);
			//cube->SetRotationZ(3.14);

			mDrawables.push_back(cube);
	
			break;
		}
	case TB3D_World::TILE_EMPTY:
		//NPrimitiveCube3D cube_empty = new NPrimitiveCube3D(posX, posY, posZ, mTileSize);
		//cube_empty.AmbientColor = Color.Green;
		//cube_empty.ScaleY = 0.01f;

		//mCubes.Add(cube_empty);
		break;
	case TB3D_World::TILE_PLAYER:
		{
			mEngine->GetPlayer()->SetPosition(posX + mTileSize / 2, posY, posZ + mTileSize / 2);
			break;
		}
	}
}

void TB3D_World::Update(float dt) {
	for (int i = 0, size = mDrawables.size(); i < size; i++)
	{
		mDrawables[i]->Update(dt);
	}
}

void TB3D_World::Draw(float dt) {
	for (int i = 0, size = mDrawables.size(); i < size; i++)
	{
		mDrawables[i]->Draw(dt);
	}
}