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

  this->setTexture("character.png");
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
  fixture.shape = Physics3DShape::createSphere(0.18);

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

  this->setPosition3D(Vec3(-3.0, 20.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->stopAllActions();
  this->syncNodeToPhysics();

  this->direction = true;

  this->index = 0;
  this->test = 1;

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
  this->index++; /// ?
  this->test = 2;
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

  /**
   *
   *
   *
   */
  auto plate = Application->environment->element(++this->index);

  auto direction = plate->getPositionZ() == this->getPositionZ();
  auto factor = (this->test > 1 ? (direction ? 2 : 1) : 1);

  auto x1 = (direction ? 0.5 : (this->test > 1 ? 0.5 : 0.0)) * (this->direction ? 1 : -1) * factor;
  auto y1 = 0;
  auto z1 = 0;
  
  auto x2 = (direction ? 0.5 : (this->test > 1 ? 0.5 : 0.0)) * (this->direction ? 1 : -1) * factor;
  auto y2 = 0;
  auto z2 = 0;

  this->runAction(
    Sequence::create(
      //EaseSineIn::create(
        MoveBy::create(0.15, Vec3(x1, 0.5 * factor, direction ? 0.0 : -0.5))
      //)
      ,
      //EaseSineOut::create(
        MoveBy::create(0.15, Vec3(x2, -(0.5 * factor) + (direction || this->test > 1 ? 1.0 / Generator::HEIGHT : 0.0) * factor, direction ? 0.0 : -0.5))
      //)
      ,
      //DelayTime::create(1.0),
      CallFunc::create([=] () {
      this->onNormal();
      }),
      nullptr
    )
  );

  if(!direction)
  {
    this->direction = !this->direction;
  }

  Application->getCamera()->runAction(
    MoveBy::create(0.3, Vec3(0.0, direction ? 1.0 / Generator::HEIGHT : 0.0, direction ? 0.0 : -1.0))
  );

  Application->cameras.shadowCastCamera->runAction(
    MoveBy::create(0.3, Vec3(0.0, direction ? 1.0 / Generator::HEIGHT : 0.0, direction ? 0.0 : -1.0))
  );

  this->test = 1;
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
