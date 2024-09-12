#include "HelloWorldScene.h"
#include <math.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tạo nhân vật
    character = Sprite::create("survivor-idle_rifle_0.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    character->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(character);
    isMoving = false;
    for (int i = 0; i < 19; ++i) {
        std::string frameName = "survivor-idle_rifle_" + std::to_string(i) + ".png";
        frames.pushBack(SpriteFrame::create(frameName, Rect(0, 0, character->getContentSize().width, character->getContentSize().height)));
    }
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
    listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
    listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update));

    return true;
}

void HelloWorld::update(float dt)
{
    Vec2 characterPosition = character->getPosition();
    float targetAngle = CC_RADIANS_TO_DEGREES(atan2(mousePosition.y - characterPosition.y, mousePosition.x - characterPosition.x));
    float currentAngle = character->getRotation();
    float deltaAngle = targetAngle - currentAngle;
    if (deltaAngle > 180) deltaAngle -= 360;
    if (deltaAngle < -180) deltaAngle += 360;
    float rotationSpeed = 5.0f;
    currentAngle += deltaAngle * rotationSpeed * dt;
    character->setRotation(-currentAngle);

    if (isMoving) {
        if (!character->getActionByTag(1)) {
            auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
            auto animate = Animate::create(animation);
            animate->setTag(1);
            character->runAction(RepeatForever::create(animate));
        }
    }
    else {
        character->stopAllActions();
        character->setTexture("survivor-idle_rifle_0.png");
    }
}
bool HelloWorld::onMouseMove(EventMouse* event)
{
    isMoving = true;
    mousePosition = event->getLocation();
    return true;
}

bool HelloWorld::onMouseDown(EventMouse* event)
{
    isMoving = true;
    mousePosition = event->getLocation(); 
    return true;
}

bool HelloWorld::onMouseUp(EventMouse* event)
{
    isMoving = false;
    return true;
}

void HelloWorld::shootBullet(Vec2 position, Vec2 targetPosition)
{
    auto bullet = Sprite::create("bullet.png");
    bullet->setPosition(position);
    this->addChild(bullet);

    Vec2 direction = targetPosition - position;
    direction.normalize();

    auto moveAction = MoveTo::create(1.0f, targetPosition);
    bullet->runAction(moveAction);
}