#include "Stage.h"
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
}

void Stage::Initialize()
{

}

void Stage::Update()
{
	Cr = GetColor(255, 0, 0);
}

void Stage::Draw()
{
	
	
	DrawOval(640, 360,550,350, Cr, FALSE);
	
}

void Stage::Release()
{
}
