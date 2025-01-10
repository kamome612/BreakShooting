#pragma once
#include "Engine/GameObject.h"

class Bullet :
    public GameObject
{
    // �@��ʂ�̓���@�Q�A�����蔻��@�R�C���ˁ@
public:
    Bullet(GameObject* parent);

    ~Bullet();

    void Initialize() override;
    void SetPosition(float x, float y);
    void Update() override;
    void Draw() override;

private:
    int hImage_;



};


