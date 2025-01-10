#include "TitleScene.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),tPict_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	tPict_ = LoadGraph("Assets\\Picture\\title.jpg");
	assert(tPict_ > 0);
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, tPict_, TRUE);
}

void TitleScene::Release()
{
}
