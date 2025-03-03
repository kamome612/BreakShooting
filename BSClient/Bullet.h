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
    float GetAngle() { return angle_; }
    float GetRandomAngle() { return randomAngle_; }
    void SetAngle(float _angle, float _rAngle)
    {
        angle_ = _angle,
        randomAngle_ = _rAngle;
    }

    void SetAngle(float _angle)
    {
        angle_ = _angle;
    }

    float GetBulletTime() { return BulletTime_; }
    void SetBulletTime(float _time) { BulletTime_ = _time; }

private:
    int hImage_;
    float BulletTime_;
    bool isDead_;//�������Ă��邩
    float angle_;//�p�x
    float moveX;
    float moveY;
    float randomAngle_; //�����ɕǂɓ����������̕ύX�Ɏg���p�x
};

