#include "sceneManager.h"
#include "../TestScene.h"
#include "../TitleScene.h"
#include "../StandByScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "time.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	winFlag_ = false;
	keyFlag_ = false;
	fps_ = 0;
	sock_ = 0;
	//タイマーの初期化
	Time::Init();
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_STANDBY: Instantiate<StandByScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
	Time::Refresh();
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

void SceneManager::ChangeScene(SCENE_ID next, bool tmp)
{
	nextSceneID_ = next;
	winFlag_ = tmp;
	keyFlag_ = tmp;
}

void SceneManager::ChangeScene(SCENE_ID next, bool tmp, int fps)
{
	nextSceneID_ = next;
	winFlag_ = tmp;
	keyFlag_ = tmp;
	fps_ = fps;
}
