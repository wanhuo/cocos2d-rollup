/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Character::Character()
: Element("character.obj", Application->environment->plane)
{
  this->initWithPhysics();
  this->initWithBody();

  this->setTexture("character-texture.png");
}

Character::~Character()
{
}

/**
 *
 *
 *
 */
void Character::initWithPhysics()
{
  Physics3DRigidBodyDes fixture;

  fixture.mass = 10.0;
  fixture.shape = Physics3DShape::createSphere(0.25);

  this->_physicsComponent = Physics3DComponent::create(Physics3DRigidBody::create(&fixture));
  this->_physicsComponent->retain();

  this->addComponent(this->_physicsComponent);
}

void Character::initWithBody()
{
  this->getBody()->setRestitution(0.5);
  this->getBody()->setFriction(1.0);
}

/**
 *
 *
 *
 */
void Character::reset()
{
  if(!this->Node::state->create)
  {
    this->_create();
  }

  this->setPosition3D(Vec3(0.0, 5.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->stopAllActions();
  this->syncNodeToPhysics();

  this->action = false;

  this->index.x = 0;
  this->index.y = 0;
  this->index.z = 0;

  this->direction.x = RIGHT;
  this->direction.y = NONE;
  this->direction.z = NONE;

  /**
   *
   *
   *
   */
  this->changeState(STATE_START);
}

/**
 *
 *
 *
 */
void Character::onCreate()
{
  Element::onCreate();

  /**
   *
   *
   *
   */
  this->reset();
}

void Character::onDestroy(bool action)
{
  Element::onDestroy(action);
}

/**
 *
 *
 *
 */
void Character::onAction()
{
  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_START:
    this->changeState(STATE_NORMAL);
    break;
    case STATE_NORMAL:
    this->action = true;
    break;
  }
}

/**
 *
 *
 *
 */
void Character::onMove()
{
  if(this->action)
  {
    if(this->direction.x == NONE)
    {
      auto left = Application->environment->generator->element(this->index.x - 1, this->index.z);
      auto right = Application->environment->generator->element(this->index.x + 1, this->index.z);

      if(left.element && right.element)
      {
        if(left.element->getNormal())
        {
          right.element = nullptr;
        }
        else
        {
          left.element = nullptr;
        }
      }

      if(left.element)
      {
        this->direction.x = LEFT;
        this->direction.z = NONE;
      }
      else
      {
        this->direction.x = RIGHT;
        this->direction.z = NONE;
      }
    }
    else
    {
      auto up = Application->environment->generator->element(this->index.x, this->index.z - 1);
      auto down = Application->environment->generator->element(this->index.x, this->index.z + 1);

      if(up.element && down.element)
      {
        if(up.element->getNormal())
        {
          down.element = nullptr;
        }
        else
        {
          up.element = nullptr;
        }
      }

      if(up.element)
      {
        this->direction.x = NONE;
        this->direction.z = FORWARD;
      }
      else
      {
        this->direction.x = NONE;
        this->direction.z = BACK;
      }
    }
  }

  this->action = false;

  /**
   *
   *
   *
   */
  switch((int) this->direction.x)
  {
    case LEFT:
    this->index.x--;
    break;
    case RIGHT:
    this->index.x++;
    break;
  }

  switch((int) this->direction.z)
  {
    case FORWARD:
    this->index.z--;
    break;
    case BACK:
    this->index.z++;
    break;
  }

  auto element = Application->environment->generator->element(this->index.x, this->index.z);

  Vec3 a;
  Vec3 b;

  a.x = 0.5;
  a.y = 0.3;
  a.z = 0.5;
  
  b.x = 0.5;
  b.y =-0.3;
  b.z = 0.5;

  switch((int) this->direction.x)
  {
    case LEFT:
    a.x *= -1.0;
    b.x *= -1.0;
    break;
    case RIGHT:
    a.x *= 1.0;
    b.x *= 1.0;
    break;
    case NONE:
    a.x = 0;
    b.x = 0;
    break;
  }

  switch((int) this->direction.z)
  {
    case FORWARD:
    a.z *= -1.0;
    b.z *= -1.0;
    break;
    case BACK:
    a.z *= 1.0;
    b.z *= 1.0;
    break;
    case NONE:
    a.z = 0;
    b.z = 0;
    break;
  }

  this->runAction(
    Sequence::create(
      MoveBy::create(0.15, a),
      MoveBy::create(0.15, b),
      CallFunc::create([=] () {
      if(element.element)
      {
        element.element->runAction(
          Sequence::create(
            TintTo::create(0.0, Color3B(0, 0, 255)),
            TintTo::create(0.1, Color3B(255, 255, 255)),
            nullptr
          )
        );
      }
      else
      {
        log("промазал!!! :)");
      }
      }),
      nullptr
    )
  );

  Application->getCamera()->runAction(
    Sequence::create(
      MoveBy::create(0.15, Vec3(a.x, 0, a.z)),
      MoveBy::create(0.15, Vec3(b.x, 0, b.z)),
      nullptr
    )
  );

  Application->environment->generator->create();
}

/**
 *
 *
 *
 */
void Character::onStart()
{
  this->getBody()->setLinearFactor(Vec3(0, 1, 0));
  this->getBody()->setAngularFactor(Vec3(0, 0, 0));
}

void Character::onNormal()
{
  this->getBody()->setLinearFactor(Vec3(0, 0, 0));
  this->getBody()->setAngularFactor(Vec3(0, 0, 0));

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
        this->onMove();
        }),
        DelayTime::create(0.3),
        nullptr
      )
    )
  );
}

/**
 *
 *
 *
 */
void Character::changeState(State state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_NONE:
      break;
      case STATE_START:
      this->onStart();
      break;
      case STATE_NORMAL:
      this->onNormal();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Character::updateStart(float time)
{
}

void Character::updateNormal(float time)
{
}

/**
 *
 *
 *
 */
void Character::updateStates(float time)
{
  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_START:
    this->updateStart(time);
    break;
    case STATE_NORMAL:
    this->updateNormal(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Character::update(float time)
{
  Element::update(time);

  /**
   *
   *
   *
   */
  this->updateStates(time);
}
