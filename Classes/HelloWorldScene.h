#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt) override;
    bool onMouseMove(cocos2d::EventMouse* event);
    bool onMouseDown(cocos2d::EventMouse* event);
    bool onMouseUp(cocos2d::EventMouse* event);
    void shootBullet(cocos2d::Vec2 position, cocos2d::Vec2 targetPosition);
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Vec2 mousePosition;
    cocos2d::Sprite* character;
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    bool isMoving;
};

#endif // __HELLOWORLD_SCENE_H__