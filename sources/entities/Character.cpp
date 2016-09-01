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
: Element("character.obj")
{
  this->setTexture("characters/1/texture.png");

  this->touch = new Entity3D("touch.obj", Application->environment->plane);
  this->touch->enableShadow(false);
  this->touch->enableLight(false);

  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->enableShadow(true);
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

  this->plane->setPosition3D(Vec3(0.0, 1.5, 0.0));
  this->plane->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setPosition3D(Vec3(0.0, 0.375 / 2, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->stopAllActions();

  this->index = 0;
  this->action = 0;

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
  this->index++;

  /**
   *
   *
   *
   */
  auto generate = this->action;

  if(this->action)
  {
    this->index++;
  }

  /**
   *
   *
   *
   */
  this->action = 0;

  /**
   *
   *
   *
   */
  auto element = Application->environment->generator->element(this->index);

  auto x = element->getPositionX() - this->plane->getPositionX();
  auto z = element->getPositionZ() - this->plane->getPositionZ();
  auto y = 0.75;

  auto time = 0.2;

  this->plane->runAction(
    Sequence::create(
      MoveBy::create(time, Vec3(x / 2, 0, z / 2)),
      CallFunc::create([=] () {

        /**
         *
         *
         *
         */
        if(generate)
        {
          Application->environment->generator->create(true);
        }
      }),
      MoveBy::create(time, Vec3(x / 2, 0, z / 2)),
      CallFunc::create([=] () {

        /**
         *
         *
         *
         */
        this->plane->runAction(
          Sequence::create(
            ScaleTo::create(0.1, 1.1, 0.7, 1.1),
            ScaleTo::create(0.13, 1.0, 1.0, 1.0),
            nullptr
          )
        );

        /**
         *
         *
         *
         */
        this->plates.current = element;

        /**
         *
         *
         *
         */
        this->touch->_create();
      }),
      CallFunc::create([=] () {

        /**
         *
         *
         *
         */
        if(true)
        {
          Application->environment->generator->create(true);
        }
      }),
      nullptr
    )
  );

  this->plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(time, Vec3(0, y, 0))
      ),
      EaseSineIn::create(
        MoveBy::create(time, Vec3(0, -y, 0))
      ),
      nullptr
    )
  );

  /*this->runAction(
    Sequence::create(
      ScaleTo::create(time, 1.0),
      ScaleTo::create(time, 0.5),
      nullptr
    )
  );*/

  /**
   *
   *
   *
   */
  Application->environment->ground->runAction(
    MoveBy::create(time * 2, Vec3(x, 0, z))
  );

  Application->getCamera()->runAction(
    MoveBy::create(time * 2, Vec3(x, 0, z))
  );

  Application->getShadowsCamera()->runAction(
    MoveBy::create(time * 2, Vec3(x, 0, z))
  );
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
        DelayTime::create(0.2 * 2),
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

  /**
   *
   *
   *
   */
  if(this->touch->state->create)
  {
    this->touch->setPosition3D(this->plates.current->getPosition3D());
    this->touch->setRotation3D(this->plates.current->getRotation3D());
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
