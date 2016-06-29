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
: Element("")
{
  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->addChild(this);

  this->setScheduleUpdate(true);
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

  this->plane->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->plane->setRotation3D(Vec3(0.0, 0.0, 0.0));
  this->plane->setScale(1.0);
  this->plane->stopAllActions();

  /**
   *
   *
   *
   */
  this->changeState(STATE_NORMAL);
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
void Character::onNormal()
{
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
