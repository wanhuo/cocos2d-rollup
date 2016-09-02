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
static MotionStreak3D* streak;
Character::Character()
: Element("character.obj")
{
  this->enableShadow(true);
  this->enableLight(true);

  this->setTexture("characters/2/character-texture.png");

  this->shadow = new Entity3D("character.obj",  Application->environment->plane, true);
  this->shadow->enableShadow(true);
  this->shadow->enableLight(true);

  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->enableShadow(true);
  this->plane->addChild(this);

  this->setScheduleUpdate(true);


   streak = MotionStreak3D::create(0.25f, 0.0f, 0.6f, Color3B(255, 255, 255), "test.png");
   //streak->setBlendFunc((BlendFunc) {GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA});
   streak->setBlendFunc((BlendFunc) {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA});
   streak->enableShadow(false);
   streak->enableLight(false);
   
  Application->addChild(streak);
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
  this->plane->setScale(1.0);

  this->setPosition3D(Vec3(0.0, 0.375 / 2, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));
  this->setScale(1.0);

  this->stopAllActions();

  this->plates.current = nullptr;
  this->plates.previous = nullptr;

  this->index = 0;
  this->stage = 0;
  this->action = 0;

  streak->reset();

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

  /**
   *
   *
   *
   */
  streak->setVisible(false);
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
    case STATE_CRASH:
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
  auto d = 0.0;

  if(this->action)
  {
    auto element = Application->environment->generator->element(this->index);

    if(this->plates.current && element)
    {
      if(element->stage <= this->plates.current->stage)
      {
        this->index++;
      }
    }
    else
    {
      this->index++;
    }
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
///////

if(!element)
{
  this->stopAllActions();
  this->changeState(STATE_CRASH);
  ////
  log("-------");
  if(generate)
  {
    log("успел нажать");
  }
  else
  {
    log("не успел нажать");
  }
    log("в яме");
  log("-------");
  ///
  return;
}

if(!generate)
{
if(this->plates.current)
{
  if(this->plates.current->stage != element->stage)
  {
    if(this->plates.current->stage < element->stage)
    {
      this->stopAllActions();
      this->changeState(STATE_CRASH);
      ////
      log("-------");
      if(generate)
      {
        log("успел нажать");
      }
      else
      {
        log("не успел нажать");
      }
        log("ударился");
      log("-------");
      ///
      return;
    }
  }
}
}


if(this->plates.current)
{
  if(this->plates.current->stage != element->stage)
  {
    if(this->plates.current->stage > element->stage)
    {
      d = -0.75;
    }
    else
    {
      d = 0.75;
    }
  }
}

         auto tt = CC_RADIANS_TO_DEGREES(atan2(element->getPositionX() - this->plane->getPositionX(), element->getPositionZ() - this->plane->getPositionZ())) - 180;
        //this->setRotation(this->getRotation3D().x, tt, this->getRotation3D().z);

  auto x = element->getPositionX() - this->plane->getPositionX();
  auto z = element->getPositionZ() - this->plane->getPositionZ();
  auto y = 0.75;

  y += (generate ? 0.5 : 0.0);

  this->plane->setRotation3D(Vec3(0, tt, 0));

  auto time = 0.2;

  this->plates.previous = this->plates.current;
  this->plates.current = element;

  this->plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(time, Vec3(0, y, 0))
      ),
      EaseSineIn::create(
        MoveBy::create(time, Vec3(0, -y + d, 0))
      ),
      nullptr
    )
  );

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
            ScaleTo::create(0.17, 0.9, 1.2, 0.9),
            ScaleTo::create(0.13, 1.0, 1.0, 1.0),
            nullptr
          )
        );
      }),
      CallFunc::create([=] () {
        if(this->plates.current)
        {
          this->plates.current->direction = 2.0;
        }

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
      CallFunc::create([=] () {

        /**
         *
         *
         *
         */
        this->onMove();
      }),
      nullptr
    )
  );

  this->runAction(
    RotateBy::create(time * 2, Vec3(-180, 0, 0))
  );

  this->shadow->setScale(0.2);
  this->shadow->runAction(
    Sequence::create(
      EaseSineOut::create(
        ScaleTo::create(time, 1.2)
      ),
      EaseSineIn::create(
        ScaleTo::create(time, 0.2)
      ),
      nullptr
    )
  );

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
  this->onMove();

  streak->setVisible(true);
}

void Character::onCrash()
{
  this->runAction(
    Sequence::create(
      ScaleTo::create(0.5, 1.5),
      CallFunc::create([=] () {
      this->_destroy(true);
      }),
      CallFunc::create([=] () {
      Application->changeState(Game::STATE_FINISH);
      }),
      nullptr
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
      case STATE_CRASH:
      this->onCrash();
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

void Character::updateCrash(float time)
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
    case STATE_CRASH:
    this->updateCrash(time);
    break;
  }

  /**
   *
   *
   *
   */
  this->shadow->setPosition3D(this->plane->getPosition3D());
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
  streak->setPosition3D(this->plane->getPosition3D());
  streak->setPositionY(this->plane->getPositionY() + 0.375/2);
}
