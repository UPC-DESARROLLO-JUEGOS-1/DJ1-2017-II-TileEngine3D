#include "TB3D_World.h"

#include "TB3D_Engine.h"
#include "TB3D_Player.h"
#include <FrameworkUPC\GameFramework.h>
#include <FrameworkUPC\BasicLightingShader.h>
#include <FrameworkUPC\ModelShader3D.h>
#include <FrameworkUPC\ModelBasicLightingShader.h>
#include <FrameworkUPC\NStaticModel3D.h>

const int TB3D_World::TILE_EMPTY = 0;
const int TB3D_World::TILE_BLOCK = 1;
const int TB3D_World::TILE_HOUSE_3D = 2;
const int TB3D_World::TILE_PLAYER = 9;

TB3D_World::TB3D_World(TB3D_Engine* engine)
{
	mEngine = engine;
	mTileSize = mEngine->GetTileSize();

	mWorldPhysics = new TB3D_WorldPhysics(this);

	// Set lights in Shader
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	BasicLightingShader* shader = shaderManagment->LoadAndGetShader<BasicLightingShader>("Shaders/BasicLightingShader");
	ModelShader3D* shader_model = shaderManagment->LoadAndGetShader<ModelShader3D>("Shaders/ModelShader3D");
	ModelBasicLightingShader* shader_primitiveModel = shaderManagment->LoadAndGetShader<ModelBasicLightingShader>("Shaders/ModelBasicLightingShader");
	
	shader->SetLight0("light0");
	shader->SetLight1("light1");
	shader_model->SetLight0("light0");
	shader_model->SetLight1("light1");
	shader_primitiveModel->SetLight0("light0");
	shader_primitiveModel->SetLight1("light1");

	NBasicLight* light0 = shader->GetLight0();
	NBasicLight* light1 = shader->GetLight1();

	light1->SetLightColor(NColor::Red);
	light1->SetIntensity(0.3f);

	light0->SetPosition(30, 4, 0);
	light1->SetPosition(30, 8, 60);
}

TB3D_World::~TB3D_World()
{

}

void TB3D_World::Initialize() {
	std::vector<std::vector<int>> worldCollisions = mEngine->GetWorldConfig()->WorldCollisions();

	float tileSize = mEngine->GetWorldConfig()->TileSize();
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

	float psx = cols * tileSize;
	float psy = rows * tileSize;
	// plane
	mPlane = new NPrimitivePlane3D();
	mPlane->Initialize(psx / 2.0f, 0, psy / 2.0f, psx, psy);
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
		// Si tiene mas de una linea de codigo en un switch tiene que estar en parentesis
		{
			NPrimitiveCube3D* cube = new NPrimitiveCube3D();
			cube->Initialize(posX, posY, posZ, mTileSize, mTileSize, mTileSize);
			cube->SetRenderCamera(camera);
			//cube->SetRotationX(3.14);
			//cube->SetRotationZ(3.14);

			mDrawables.push_back(cube);
			break;
		}
	case TB3D_World::TILE_HOUSE_3D:
		{
			// Inicializamos el Modelo 3D
			NStaticModel3D* staticModel = new NStaticModel3D();
			staticModel->Initialize("Models/", "farmhouse_obj.obj", posX, posY, posZ);
			staticModel->SetRenderCamera(camera);
			staticModel->SetScale(0.6f, 0.6f, 0.6f);

			mDrawables.push_back(staticModel);
			break;
		}
	case TB3D_World::TILE_EMPTY:
		break;
	case TB3D_World::TILE_PLAYER:
		mEngine->GetPlayer()->SetPosition(posX + mTileSize / 2, posY, posZ + mTileSize / 2);
		break;
		
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