#pragma once
#include "Engine/GameObject.h"

class Bullet :
    public GameObject
{
    // ①一通りの動作　２、当たり判定　３，反射　
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


