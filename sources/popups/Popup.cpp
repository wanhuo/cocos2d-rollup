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
Popup::Popup()
: BackgroundColor(Application, Color4B(0, 0, 0, 0))
{
  this->setCascadeOpacityEnabled(false);

  /**
   *
   *
   *
   */
  this->_destroy();
}

Popup::~Popup()
{
}

/**
 *
 *
 *
 */
void Popup::onEnter()
{
  BackgroundColor::onEnter();

  /**
   *
   *
   *
   */
  this->setCameraMask(BACKGROUND);
}

void Popup::onExit()
{
  BackgroundColor::onExit();
}

/**
 *
 *
 *
 */
void Popup::onShow()
{
}

void Popup::onHide()
{
  this->_destroy();
}

/**
 *
 *
 *
 */
void Popup::show()
{
  this->_create();

  this->bind(true);

  this->runAction(
    Sequence::create(
      FadeTo::create(0.5, 70),
      CallFunc::create([=] () {
      this->onShow();
      }),
      nullptr
    )
  );
}

void Popup::hide()
{
  this->bind(false);

  this->runAction(
    Sequence::create(
      FadeTo::create(0.5, 0),
      CallFunc::create([=] () {
      this->onHide();
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
bool Popup::containsTouchLocation(cocos2d::Touch* touch)
{
  return true;
}
