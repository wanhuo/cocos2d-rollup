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
Tutorial* Tutorial::instance;

/**
 *
 *
 *
 */
Tutorial* Tutorial::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Tutorial::Tutorial()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->buttons.play = new ExtendedButton("ui/button-tutorial.png", 2, 1, this, std::bind(&Tutorial::onPlay, this));

  /**
   *
   *
   *
   */
  this->element = new TiledEntity("ui/tutorial-element.png", 2, 1, this);
  this->element->setPosition(Application->getCenter().x + 100, Application->getCenter().y - 300);
  this->element->setOpacity(0);
  this->element->setCurrentFrameIndex(1);
}

Tutorial::~Tutorial()
{
}

/**
 *
 *
 *
 */
void Tutorial::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      DelayTime::create(10.0),
      CallFunc::create([=] () {
      this->buttons.play->add(Application->getCenter().x, 200);
      }),
      nullptr
    )
  );
}

void Tutorial::onExit()
{
  Popup::onExit();
}

/**
 *
 *
 *
 */
void Tutorial::onPlay()
{
  Application->state = Game::STATE_NONE;

  /**
   *
   *
   *
   */
  Director::getInstance()->getScheduler()->setTimeScale(1.0);

  /**
   *
   *
   *
   */
  this->hide([=] () {
    Application->changeState(Game::STATE_MENU);

    Application->environment->clear->runAction(
      Sequence::create(
        FadeTo::create(0.3, 255.0),
        CallFunc::create([=] () {
        Application->reset();
        }),
        DelayTime::create(0.1),
        FadeTo::create(0.3, 0.0),
        nullptr
      )
    );

    /**
     *
     *
     *
     */
    Storage::set("@app.tutorial.complete", 1);
  });
}

/**
 *
 *
 *
 */
void Tutorial::show()
{
  this->_create();
}

void Tutorial::hide(const std::function<void()>& callback)
{
  Popup::hide(callback);

  /**
   *
   *
   *
   */
  this->buttons.play->remove();
}
