#pragma once
#include "Engine/GameObject.h"
class Bullet :
    public GameObject
{

public:
    Bullet(GameObject* parent);

    void Initialize() override;
    void WallJuge();
    void SetPosition(float x, float y);
    bool CollideCircle(float x, float y, float r);
    void Update() override;
    void Draw() override;

private:
    int hImage_;
    float BulletTime_;
    float angle_;//Šp“x
    float moveX;
    float moveY;


};

