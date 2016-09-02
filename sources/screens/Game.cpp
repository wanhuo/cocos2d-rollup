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
   *
   *
   */
  this->startCameraPosition.x = 0.0;
  this->startCameraPosition.y = 8.0;
  this->startCameraPosition.z = 7.0;

  this->startCameraRotation.x = -40.0;
  this->startCameraRotation.y = 0.0;
  this->startCameraRotation.z = 0.0;

  this->startShadowsCameraPosition.x = -5.0;
  this->startShadowsCameraPosition.y = 10.0;
  this->startShadowsCameraPosition.z = 10.0;

  this->startShadowsCameraRotation.x = -90.0;
  this->startShadowsCameraRotation.y = 0.0;
  this->startShadowsCameraRotation.z = 0.0;

  /**
   *
   *
   *
   */
  this->cameras.cameraElements = Camera::createPerspective(60, this->getWidth() / this->getHeight(), 1, 100);
  this->cameras.cameraElements->setPosition3D(this->startCameraPosition);
  this->cameras.cameraElements->setRotation3D(this->startCameraRotation);

  this->cameras.cameraShadows = Camera::createOrthographic(this->getWidth() / 70, this->getHeight() / 70, 1, 100);
  this->cameras.cameraShadows->setPosition3D(this->startShadowsCameraPosition);
  this->cameras.cameraShadows->setRotation3D(this->startShadowsCameraRotation);

  this->cameras.cameraForeground = Camera::create();
  this->cameras.cameraBackground = Camera::create();

  //this->cameras.cameraBuffer = Camera::create();
  //this->cameras.cameraCapture = Camera::create();

  this->cameras.cameraElements->setCameraFlag(ELEMENTS);
  this->cameras.cameraShadows->setCameraFlag(ELEMENTS);
  this->cameras.cameraForeground->setCameraFlag(FOREGROUND);
  this->cameras.cameraBackground->setCameraFlag(BACKGROUND);
  //this->cameras.cameraBuffer->setCameraFlag(2);
  //this->cameras.cameraCapture->setCameraFlag(2);

  this->cameras.cameraElements->setDepth(1);
  this->cameras.cameraForeground->setDepth(3);
  this->cameras.cameraBackground->setDepth(2);
  /*this->cameras.cameraBuffer->setDepth(3);
  this->cameras.cameraShadows->setDepth(1);
  this->cameras.cameraCapture->setDepth(4);*/

  this->cameras.cameraElements->setIndex(ELEMENTS);
  this->cameras.cameraForeground->setIndex(FOREGROUND);
  this->cameras.cameraBackground->setIndex(BACKGROUND);
  //this->cameras.cameraBuffer->setIndex(3);
  this->cameras.cameraShadows->setIndex(3);
  //this->cameras.cameraCapture->setIndex(4);

  this->addChild(this->cameras.cameraElements);
  this->addChild(this->cameras.cameraForeground);
  this->addChild(this->cameras.cameraBackground);
  this->addChild(this->cameras.cameraShadows);
  //this->addChild(this->cameras.frameBufferCamera);
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
  Director::getInstance()->setAmbient(true , this);

  /**
   *
   * @Director
   * | @Capture;
   *
   */
  Director::getInstance()->setCaptureCamera(this->cameras.cameraElements);
  Director::getInstance()->setCaptureElement(new Entity(true));
  Director::getInstance()->setCaptureCount(60);
  Director::getInstance()->setCaptureTime(2);
  Director::getInstance()->setCaptureFactor(1);
  Director::getInstance()->setCaptureSize(240, 240);
  Director::getInstance()->setCapturePosition(0, 0);
  Director::getInstance()->setCaptureScale(3);
  Director::getInstance()->setCapture(true, this);

  //Director::getInstance()->getCaptureTexture()->setCameraMask(FOREGROUND);

  this->cameras.cameraBackground->setFrameBufferObject(Director::getInstance()->getCaptureFrameBuffer());

  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  Director::getInstance()->setShadowCamera(this->cameras.cameraShadows);
  Director::getInstance()->setShadowFactor(1);
  Director::getInstance()->setShadow(true, this);

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
  return this->cameras.cameraElements;
}

Camera* Game::getShadowsCamera()
{
  return this->cameras.cameraShadows;
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
     * @Development
     *
     */
    case EventKeyboard::KeyCode::KEY_SPACE:
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

  /**
   *
   *
   *
   */
  Music->play("music-1", true);
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
void Game::onRenderStart()
{
}

void Game::onRenderFinish()
{
}

void Game::onRenderStart(int index)
{
  //if(Director::getInstance()->getShadowState())
  {
    if(index == this->getShadowsCamera()->getIndex())
    {
      this->environment->character->setVisible(false);
      this->environment->character->shadow->setVisible(true);
    }
    else if(index == 1)
    {
      this->environment->character->setVisible(true);
      this->environment->character->shadow->setVisible(false);
    }
  }
}

void Game::onRenderFinish(int index)
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

  this->environment->update(time);

  /**
   *
   *
   *
   */
  cocos2d::experimental::FrameBuffer::clearAllFBOs();
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
