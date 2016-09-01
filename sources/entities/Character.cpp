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
void Character::reset()
{
  if(!this->Node::state->create)
  {
    this->_create();
  }

  this->setPosition3D(Vec3(0.0, 3.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));
  this->setScale(0.5);

  this->stopAllActions();

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
  }

  Application->environment->generator->create();
}

/**
 *
 *
 *
 */
void Character::onStart()
{
}

void Character::onNormal()
{
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
