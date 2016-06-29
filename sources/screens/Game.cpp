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
Game* Game::instance;

/**
 *
 *
 *
 */
Game* Game::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Game::Game()
{
  instance = this;

  Modal::show();

  this->cameras.d = Camera::createPerspective(60, this->getWidth() / this->getHeight(), NEAR, FAR);

  this->cameras.d->setCameraFlag(1);

  this->cameras.d->setDepth(1);

  this->generateFrameBuffer();

  this->startCameraX = 0;
  this->startCameraY = 4.0;
  this->startCameraZ = 10.0;

  this->startCameraRotationX = -30;
  this->startCameraRotationY = 0;
  this->startCameraRotationZ = 0;

  this->cameras.d->setPosition3D(Vec3(this->startCameraX, this->startCameraY, this->startCameraZ));
  this->cameras.d->setRotation3D(Vec3(this->startCameraRotationX, this->startCameraRotationY, this->startCameraRotationZ));

  this->addChild(this->cameras.d);

  this->environment = new Environment(this);
  this->environment->create();
}

Game::~Game()
{
}

/**
 *
 *
 *
 */
void Game::generateFrameBuffer()
{
  if(Screenshot::support())
  {
  }
}

/**
 *
 *
 *
 */
FrameBuffer* Game::getFrameBuffer()
{
  return this->frameBuffer;
}

/**
 *
 *
 *
 */
void Game::onTouchStart(cocos2d::Touch* touch, Event* event)
{
  switch(this->state)
  {
    default:
    break;
    case GAME:
    break;
  }
}

void Game::onTouchFinish(cocos2d::Touch* touch, Event* event)
{
  switch(this->state)
  {
    default:
    break;
  }
}

/**
 *
 *
 *
 */
void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
  switch(this->state)
  {
    default:
    break;
    case GAME:
    break;
  }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
}

/**
 *
 *
 *
 */
void Game::onEnter()
{
  Screen::onEnter();

  /**
   *
   *
   *
   */
  Internal::onStart();

  /**
   *
   *
   *
   */
   this->changeState(MENU);
}

void Game::onExit()
{
  Screen::onExit();
}

/**
 *
 *
 *
 */
void Game::onBack()
{
}

/**
 *
 *
 *
 */
void Game::onLeaderboards()
{
  Events::onLeaderboards();
}

void Game::onAchievements()
{
  Events::onAchievements();
}

void Game::onRate()
{
  Events::onRate();
}

void Game::onFacebookLike()
{
  Events::onFacebookLike();
}

void Game::onTwitterLike()
{
  Events::onTwitterLike();
}

void Game::onShare(bool action, bool complete, const std::function<void(int)>& callback, const std::function<void(int, int)>& update)
{
  Events::onShare(action, complete, callback, update);
}

void Game::onTwitter()
{
  Events::onTwitter();
}

void Game::onFacebook()
{
  Events::onFacebook();
}

void Game::onMail()
{
  Events::onMail();
}

void Game::onRestorePurchases()
{
  Events::onRestorePurchases();
}

/**
 *
 *
 *
 */
void Game::onMenu()
{
  this->environment->onMenu();
}

void Game::onGame()
{
  this->environment->onGame();
}

void Game::onFinish()
{
  this->environment->onFinish();
}

/**
 *
 *
 *
 */
void Game::onNoad()
{
}

/**
 *
 *
 *
 */
void Game::changeState(State state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      default:
      break;
      case MENU:
      this->onMenu();
      break;
      case GAME:
      this->onGame();
      break;
      case FINISH:
      this->onFinish();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Game::updateMenu(float time)
{
}

void Game::updateGame(float time)
{
}

void Game::updateFinish(float time)
{
}

/**
 *
 *
 *
 */
void Game::updateStates(float time)
{
  switch(this->state)
  {
    default:
    break;
    case MENU:
    this->updateMenu(time);
    break;
    case GAME:
    this->updateGame(time);
    break;
    case FINISH:
    this->updateFinish(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Game::update(float time)
{
  Screen::update(time);

  /**
   *
   *
   *
   */
  this->updateStates(time);
}
