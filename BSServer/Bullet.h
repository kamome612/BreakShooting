#pragma once
#include "Engine/GameObject.h"
class Bullet :
    public GameObject
{
 
public :
    Bullet(GameObject* parent);

    ~Bullet();
    
    void Initialize() override;
    void SetPosition(float x,float y);
    void Update() override;
    void Draw() override;

private:
    int hImage_;
    


};

