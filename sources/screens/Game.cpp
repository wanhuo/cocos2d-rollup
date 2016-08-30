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

  /**
   *
   * Setup cameras
   *
   */
  this->cameras.defaultCamera = Camera::createPerspective(50, this->getWidth() / this->getHeight(), 1, 100);
  this->cameras.defaultCamera->setPosition(0, 14, 9);
  this->cameras.defaultCamera->setRotation(-50, 0, 0);

  this->cameras.shadowCastCamera = Camera::createOrthographic(this->getWidth() / 70, this->getHeight() / 70, 1, 100);
  this->cameras.shadowCastCamera->setPosition(-10, 0.5, 10);
  this->cameras.shadowCastCamera->setRotation(-10, -20, 0);

  this->cameras.frameBufferCamera = Camera::create();
  this->cameras.captureBufferCamera = Camera::create();

  this->cameras.defaultCamera->setCameraFlag(1);
  this->cameras.frameBufferCamera->setCameraFlag(2);
  this->cameras.shadowCastCamera->setCameraFlag(1);
  this->cameras.captureBufferCamera->setCameraFlag(2);

  this->cameras.defaultCamera->setDepth(2);
  this->cameras.frameBufferCamera->setDepth(3);
  this->cameras.shadowCastCamera->setDepth(1);
  this->cameras.captureBufferCamera->setDepth(4);

  this->cameras.defaultCamera->setIndex(1);
  this->cameras.frameBufferCamera->setIndex(3);
  this->cameras.shadowCastCamera->setIndex(2);
  this->cameras.captureBufferCamera->setIndex(4);

  this->addChild(this->cameras.defaultCamera);
  //this->addChild(this->cameras.frameBufferCamera);
  //this->addChild(this->cameras.shadowCastCamera);
  //this->addChild(this->cameras.captureBufferCamera);

  /**
   *
   * @Director
   * | @Ambient;
   *
   */
  Director::getInstance()->setAmbientColor1(255, 255, 255);
  Director::getInstance()->setAmbientColor2(150, 150, 150);
  Director::getInstance()->setAmbientDirection(0, -1, 1);
  Director::getInstance()->setAmbient(true, this);

  /**
   *
   * @Director
   * | @Capture;
   *
   */
  Director::getInstance()->setCaptureCamera(this->cameras.defaultCamera);
  Director::getInstance()->setCaptureElement(new Entity(true));
  Director::getInstance()->setCaptureCount(60);
  Director::getInstance()->setCaptureTime(2);
  Director::getInstance()->setCaptureFactor(1);
  Director::getInstance()->setCaptureSize(240, 240);
  Director::getInstance()->setCapturePosition(0, 0);
  Director::getInstance()->setCaptureScale(3);
  Director::getInstance()->setCapture(false, this);

  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  Director::getInstance()->setShadowCamera(this->cameras.shadowCastCamera);
  Director::getInstance()->setShadowFactor(1);
  Director::getInstance()->setShadow(false, this);

  /**
   *
   *
   *
   */
  this->environment = new Environment(this);
  this->environment->create();

  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  Director::getInstance()->setShadowElement(this->environment->plane);

  /**
   *
   *
   *
   */
  if(this->initWithPhysics())
  {
    this->getPhysics3DWorld()->setGravity(Vec3(0, -50, 0));
  }
}

Game::~Game()
{
}

/**
 *
 *
 *
 */
Camera* Game::getCamera()
{
  return this->cameras.defaultCamera;
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
    case STATE_NONE:
    break;
    case STATE_MENU:
    this->changeState(STATE_GAME);
    break;
    case STATE_GAME:
    break;
    case STATE_FINISH:
    break;
  }

  this->environment->onAction();
}

void Game::onTouchFinish(cocos2d::Touch* touch, Event* event)
{
  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_MENU:
    break;
    case STATE_GAME:
    break;
    case STATE_FINISH:
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
    case STATE_NONE:
    break;
    case STATE_MENU:
    break;
    case STATE_GAME:
    break;
    case STATE_FINISH:
    break;
  }

  switch(key)
  {
    default:
    break;

    /**
     *
     *
     *
     */
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    this->environment->character->direction.x = Character::NONE;
    this->environment->character->direction.z = Character::FORWARD;
    break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    this->environment->character->direction.x = Character::NONE;
    this->environment->character->direction.z = Character::BACK;
    break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    this->environment->character->direction.x = Character::LEFT;
    this->environment->character->direction.z = Character::NONE;
    break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    this->environment->character->direction.x = Character::RIGHT;
    this->environment->character->direction.z = Character::NONE;

    break;

    /**
     *
     * @Development
     *
     */
    case EventKeyboard::KeyCode::KEY_SPACE:
    this->getPhysics3DWorld()->setDebugDrawEnable(!this->getPhysics3DWorld()->isDebugDrawEnabled());
    //this->environment->onAction();
    break;
    case EventKeyboard::KeyCode::KEY_C:
    if(Director::getInstance()->getShadowTexture()->state->create)
    {
      Director::getInstance()->getShadowTexture()->_destroy();
    }
    else
    {
      Director::getInstance()->getShadowTexture()->_create();
    }
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
   this->changeState(STATE_MENU);
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
      case STATE_NONE:
      break;
      case STATE_MENU:
      this->onMenu();
      break;
      case STATE_GAME:
      this->onGame();
      break;
      case STATE_FINISH:
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
    case STATE_NONE:
    break;
    case STATE_MENU:
    this->updateMenu(time);
    break;
    case STATE_GAME:
    this->updateGame(time);
    break;
    case STATE_FINISH:
    this->updateFinish(time);
    break;
  }

  /**
   *
   *
   *
   */
  //cocos2d::experimental::FrameBuffer::clearAllFBOs();
  //Director::getInstance()->updateCapture();
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
