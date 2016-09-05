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
Unlock* Unlock::instance;

/**
 *
 *
 *
 */
Unlock* Unlock::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Unlock::Unlock()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->bind(true);

  /**
   *
   *
   *
   */
  this->buttons.action = new UnlockButton(this);
  this->buttons.play = new Button("ui/button-play.png", 2, 1, this, [=] () {
    Application->changeState(Game::STATE_GAME);
  });
}

Unlock::~Unlock()
{
}

/**
 *
 *
 *
 */
void Unlock::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  auto time = 0.5;

  /**
   *
   *
   *
   */
  auto action = Spawn::create(
    EaseSineOut::create(
      ScaleTo::create(time, 1.0)
    ),
    EaseSineOut::create(
      FadeTo::create(time, 255.0)
    ),
    nullptr
  );

  /**
   *
   *
   *
   */
  this->buttons.play->runAction(action->clone());
  //this->buttons.share->runAction(action->clone());
}

void Unlock::onExit()
{
  Popup::onExit();
}

/**
 *
 *
 *
 */
void Unlock::show()
{
  Popup::show();
}

void Unlock::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  auto time = 0.4;

  /**
   *
   *
   *
   */
  auto action = Spawn::create(
    EaseSineIn::create(
      ScaleTo::create(time, 0.8)
    ),
    EaseSineIn::create(
      FadeTo::create(time, 0.0)
    ),
    nullptr
  );

  /**
   *
   *
   *
   */
  this->buttons.play->runAction(action->clone());
  this->buttons.share->runAction(action->clone());

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      DelayTime::create(time),
      CallFunc::create([=] () {
      this->buttons.play->_destroy();
      this->buttons.share->_destroy();
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
void Unlock::changeState(int state)
{
  this->state = state;
}
