#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    bool nextScene;
    int passengers, money;
    int speed_level;
    int spawn_level;
    int capacity_level;
    Scene()
    {
        nextScene = false;
        passengers = money = speed_level = spawn_level = capacity_level = 0;
    }
    ~Scene() {}

    virtual void Init() = 0;
    virtual void Update(double dt) = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;
};

#endif