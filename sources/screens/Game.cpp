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

  this->cameras.cameraBackground = Camera::create();

  this->cameras.cameraElements->setCameraFlag(ELEMENTS);
  this->cameras.cameraShadows->setCameraFlag(ELEMENTS);
  this->cameras.cameraBackground->setCameraFlag(BACKGROUND);

  this->cameras.cameraElements->setDepth(2);
  this->cameras.cameraBackground->setDepth(3);
  this->cameras.cameraShadows->setDepth(1);

  this->cameras.cameraElements->setIndex(ELEMENTS);
  this->cameras.cameraBackground->setIndex(BACKGROUND);
  this->cameras.cameraShadows->setIndex(SHADOWS);

  this->addChild(this->cameras.cameraElements);
  this->addChild(this->cameras.cameraBackground);
  this->addChild(this->cameras.cameraShadows);

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

  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  Director::getInstance()->setShadowCamera(this->cameras.cameraShadows);
  Director::getInstance()->setShadowFactor(1);
  Director::getInstance()->setShadow(true, this);

  if(!Director::getInstance()->getShadowState())
  {
    this->cameras.cameraShadows->removeFromParent();

    GLProgramCache::getInstance()->addGLProgram(
      GLProgram::createWithFilenames("element.common.vert", "element.common.frag"),
      "@element.common"
    );
  }

  /**
   *
   *
   *
   */
  this->environment = new Environment(this);
  this->environment->create();

  /**
   *
   *
   *
   */
  this->counter = new Counter;

  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  if(Director::getInstance()->getShadowState())
  {
    Director::getInstance()->setShadowElement(this->environment->plane);
  }

  /**
   *
   *
   *
   */
  //Music->play("music-1", true);
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
    case STATE_FINISH:
    break;
    case STATE_MENU:
    this->changeState(STATE_GAME);
    break;
    case STATE_GAME:
    break;
  }

  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_FINISH:
    break;
    case STATE_MENU:
    case STATE_GAME:
    this->environment->onAction();
    break;
  }
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
  Menu::getInstance()->changeState(Menu::STATE_MENU);
  Menu::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onMenu();

  /**
   *
   *
   *
   */
  this->reset();
}

void Game::onGame()
{
  Menu::getInstance()->hide();

  /**
   *
   *
   *
   */
  this->counter->_create();

  /**
   *
   *
   *
   */
  this->environment->onGame();
}

void Game::onFinish()
{
  Menu::getInstance()->changeState(Menu::STATE_FINISH);
  Menu::getInstance()->show();

  /**
   *
   *
   *
   */
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

void Game::onRenderStart(int index, int step)
{
  /**
   *
   * @Director
   * | @Shadows;
   *
   */
  if(Director::getInstance()->getShadowState())
  {
    /**
     *
     *
     *
     */
    if(index == this->getShadowsCamera()->getIndex())
    {
      if(step == 1)
      {
        this->environment->character->setVisible(false);
        this->environment->character->shadow->setVisible(true);

        this->environment->status->setVisible(false);
      }
    }

    /**
     *
     *
     *
     */
    else if(index == ELEMENTS)
    {
      if(step == 1)
      {
        this->environment->character->setVisible(true);
        this->environment->character->shadow->setVisible(false);

        this->environment->status->setVisible(true);
      }

      if(step == 2)
      {
        CC_LOOP(this->environment->plates)
        {
          ((Plate*) this->environment->plates->element(i))->update();
        }
      }
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
void Game::reset()
{
  this->environment->reset();

  /**
   *
   *
   *
   */
  this->counter->reset();

  /**
   *
   *
   *
   */
  this->cameras.cameraElements->setPosition3D(this->startCameraPosition);
  this->cameras.cameraElements->setRotation3D(this->startCameraRotation);

  if(Director::getInstance()->getShadowState())
  {
    this->cameras.cameraShadows->setPosition3D(this->startShadowsCameraPosition);
    this->cameras.cameraShadows->setRotation3D(this->startShadowsCameraRotation);
  }
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
  if(Director::getInstance()->getCaptureState())
  {
    //Director::getInstance()->updateCapture();
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
