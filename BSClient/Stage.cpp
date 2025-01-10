#include "Stage.h"
Stage::Stage(GameObject* parent)
	: GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{

}

void Stage::Update()
{
}

void Stage::Draw()
{
	Cr = GetColor(0, 0, 0);

	DrawCircle(300, 400, 100, FALSE);
}

void Stage::Release()
{
}
