#pragma once
#include "Engine/GameObject.h"
class Bullet :
    public GameObject
{

public:
    Bullet(GameObject* parent);

    void Initialize() override;
    void WallJudge();
    void BlockJudge();
    bool IsAlive();
    void SetPosition(float x, float y);
    bool CollideCircle(float x, float y, float r);
    void Update() override;
    void Draw() override;

private:
    int hImage_;
    float BulletTime_;
    bool isDead_;//存在しているか
    float angle_;//角度
    float moveX;
    float moveY;


};

