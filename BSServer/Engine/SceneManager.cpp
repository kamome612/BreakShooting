#include "sceneManager.h"

#include "../TestScene.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "../ExplanationScene.h"
#include "time.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	clearFlag_ = false;
	keyFlag_ = false;
	fps_ = 0;
	//�^�C�}�[�̏�����
	Time::Init();
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_EXPLANATION:Instantiate<ExplanationScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;

		}
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
	Time::Refresh();
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

void SceneManager::ChangeScene(SCENE_ID next, bool tmp)
{
	nextSceneID_ = next;
	clearFlag_ = tmp;
	keyFlag_ = tmp;
}

void SceneManager::ChangeScene(SCENE_ID next, bool tmp, int fps)
{
	nextSceneID_ = next;
	clearFlag_ = tmp;
	keyFlag_ = tmp;
	fps_ = fps;
}