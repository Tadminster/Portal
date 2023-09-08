#pragma once
class Fruit : public Actor
{
private:
    Vector3 dir;
    float   power = 0.0f;

    float   gravity = 0.0f;
    bool    isFire = false;
    float  boomPower;
public:
    static Fruit* Create(string name = "Fruit");
private:
    Fruit();
    virtual ~Fruit();
public:
    void	Update() override;
    void	Render() override;
    bool    Fire(Vector3 pos,Vector3 dir, float power);
    void    Boom();
    bool GetIsFire() { return isFire; }

};

