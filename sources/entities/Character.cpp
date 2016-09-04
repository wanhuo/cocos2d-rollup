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

  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->enableShadow(true);
  this->plane->addChild(this);

  if(Director::getInstance()->getShadowState())
  {
    this->shadow = new Entity3D("character.obj",  Application->environment->plane, true);
    this->shadow->enableShadow(true);
    this->shadow->enableLight(true);
  }

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
  this->setOpacity(255);
  this->setScale(1.0);

  this->stopAllActions();

  this->plates.current = nullptr;
  this->plates.previous = nullptr;

  this->index = 0;
  this->stage = 0;

  this->action = false;
  this->bind = false;

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
static Speed* speed1 = nullptr;
static Speed* speed2 = nullptr;
static Speed* speed3 = nullptr;
static Speed* speed4 = nullptr;
static Speed* speed5 = nullptr;
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
    if(this->bind)
    {
      auto t = 1.3;
      if(speed1) speed1->setSpeed(t);
      if(speed2) speed2->setSpeed(t);
      if(speed3) speed3->setSpeed(t);
      if(speed4) speed4->setSpeed(t);
      if(speed5) speed5->setSpeed(t);
      this->action = true;
    }
    break;
    case STATE_CRASH:
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
  speed1 = nullptr;
  speed2 = nullptr;
  speed3 = nullptr;
  speed4 = nullptr;
  speed5 = nullptr;

  this->index++;

  /**
   *
   *
   *
   */
  auto generate = this->action;
  auto d = 0.0;
  auto a = 0.0;

  auto skip = false;

  if(this->action)
  {
    auto element = Application->environment->generator->element(this->index);

    if(this->plates.current && element)
    {
      if(element->stage <= this->plates.current->stage)
      {
        this->index++;
        skip=true;
      }
    }
    else
    {
      this->index++;
        skip=true;
    }
  }

  /**
   *
   *
   *
   */
  this->action = false;

  /**
   *
   *
   *
   */
  auto element = Application->environment->generator->element(this->index);
///////

if(!element)
{
  this->changeState(STATE_CRASH, CRASH_MISS);
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
}

if(!generate)
{
if(this->plates.current && element)
{
  if(this->plates.current->stage != element->stage)
  {
    if(this->plates.current->stage < element->stage)
    {
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


if(this->plates.current && element)
{
  if(this->plates.current->stage != element->stage)
  {
    if(this->plates.current->stage > element->stage)
    {
      d = -0.75;
      a = -0.2;

      if(skip)
      {
        a -= 0.25;
      }
    }
    else
    {
      d = 0.75;
      a = 0.2;

      if(skip)
      {
        a += 0.25;
      }
    }
  }
}

float x;
float z;
float y = 0.7;



if(skip)
if(this->plates.current && element)
{
  if(element->stage == 1)
  if(this->plates.current->stage == element->stage)
  {
    y -= 0.4;
  }
}

if(element)
{

  x = element->getPositionX() - this->plane->getPositionX();
  z = element->getPositionZ() - this->plane->getPositionZ();

  this->plates.previous = this->plates.current;
  this->plates.current = element;
  }
  else
  {
    
  element = Application->environment->generator->element(this->index+1);
  x = (element->getPositionX() - this->plane->getPositionX()) / 2;
  z = (element->getPositionZ() - this->plane->getPositionZ()) / 2;
  }

  y += (generate ? 0.3 : 0.0);

  

         auto tt = CC_RADIANS_TO_DEGREES(atan2(element->getPositionX() - this->plane->getPositionX(), element->getPositionZ() - this->plane->getPositionZ())) - 180;
        this->plane->setRotation3D(Vec3(0, tt, 0));



  auto time = 0.2;

  speed1 = Speed::create(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(time, Vec3(0, y + a, 0))
      ),
      EaseSineIn::create(
        MoveBy::create(time, Vec3(0, -y + d - a, 0))
      ),
      nullptr
    ),
    1.0
  );

  speed2 = Speed::create(
    Spawn::create(
      Sequence::create(
        DelayTime::create(time / 3),
        CallFunc::create([=] () {
          this->bind = true;
          this->action = false;
        }),
        nullptr
      ),

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
          if(this->plates.current)
          {
            this->plates.current->common = 2.0;
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
          this->bind = false;

          /**
           *
           *
           *
           */
          switch(this->state)
          {
            case STATE_NORMAL:
            this->onMove();
            break;
            case STATE_CRASH:
            // ??
            this->plane->runAction(
              Spawn::create(
                Sequence::create(
                  MoveTo::create(0.175, Vec3(this->plane->getPosition3D().x, 0.0, this->plane->getPosition3D().z)),
                  CallFunc::create([=] () {
                  Application->changeState(Game::STATE_FINISH);
                  this->_destroy(true);
                  }),
                  nullptr
                ),
                nullptr
              )
            );
            this->runAction(
              Sequence::create(
                DelayTime::create(0.175 / 2.0),
                FadeOut::create(0.175 / 2.0),
                nullptr
              )
            );
            break;
          }
        }),
        nullptr
      ),
    nullptr
    ),
    1.0
  );

  speed3 = Speed::create(
    RotateBy::create(time * 2, Vec3(-180, 0, 0)),
    1.0
  );
  


  speed4 = Speed::create(
    Sequence::create(
      DelayTime::create(time * 2 - 0.035),
      ScaleTo::create(0.04, 1.2, 0.6, 1.2),
      ScaleTo::create(0.05, 0.8, 1.3, 0.8),
      ScaleTo::create(0.13, 1.0, 1.0, 1.0),
      nullptr
    ),
    1.0
  );

  this->plane->runAction(
    speed1
  );

  this->plane->runAction(
    speed2
  );

  this->runAction(
    speed3
  );
  
  this->plane->runAction(speed4);

  if(Director::getInstance()->getShadowState())
  {
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
  }

  /**
   *
   *
   *
   */
  Application->environment->ground->runAction(
    MoveBy::create(time * 2, Vec3(x, 0, z))
  );

  speed5 = Speed::create(
    Sequence::create(
      MoveBy::create(time * 2, Vec3(x, 0, z)),
      nullptr
    ),
    1.0
  );
  Application->getCamera()->runAction(
    speed5
  );

  if(Director::getInstance()->getShadowState())
  {
    Application->getShadowsCamera()->runAction(
      MoveBy::create(time * 2, Vec3(x, 0, z))
    );
  }

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    default:
    if(speed4) {speed4->setSpeed(0.0); speed4= nullptr;}
    break;
    case STATE_NORMAL:
    break;
  }
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

void Character::onCrash(int parameter)
{
  switch(parameter)
  {
    default:
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
    break;
    case CRASH_MISS:
    break;
  }
}

/**
 *
 *
 *
 */
void Character::changeState(State state, int parameter)
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
      this->onCrash(parameter);
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
  if(Director::getInstance()->getShadowState())
  {
    this->shadow->setPosition3D(this->plane->getPosition3D());
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
  streak->setPosition3D(this->plane->getPosition3D());
  streak->setPositionY(this->plane->getPositionY() + 0.375/2);
}
