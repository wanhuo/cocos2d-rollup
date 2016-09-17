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
  Director::getInstance()->setCaptureElement(new Capture::Element);
  Director::getInstance()->setCaptureCount(60);
  Director::getInstance()->setCaptureTime(2);
  Director::getInstance()->setCaptureFactor(1);
  Director::getInstance()->setCaptureSize(320, 320);
  Director::getInstance()->setCapturePosition(0, 0);
  Director::getInstance()->setCaptureScale(2);
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

    if(Support::shaders(SHADER_SIMPLE))
    {
      GLProgramCache::getInstance()->addGLProgram(
        GLProgram::createWithFilenames("element.common.vert", "element.common.frag"),
        "@element.common"
      );
    }
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
   * @Shaders
   * | @Create various shaders and add them to the shaders cache;
   *
   */
  if(Support::shaders(SHADER_COMPLEX))
  {
    GLProgramCache::getInstance()->addGLProgram(
      GLProgram::createWithFilenames("shader.opacity.vertical.vert", "shader.opacity.vertical.frag"),
      "@shader.opacity.vertical"
    );
    GLProgramCache::getInstance()->addGLProgram(
      GLProgram::createWithFilenames("shader.main.blur.vert", "shader.main.blur.frag"),
      "@shader.main.blur"
    );
  }

  if(Support::shaders(SHADER_SIMPLE))
  {
    GLProgramCache::getInstance()->addGLProgram(
      GLProgram::createWithFilenames("shader.main.mask.vert", "shader.main.mask.frag"),
      "@shader.main.mask"
    );
  }

  /**
   *
   * @Director
   * | @Capture;
   *
   */
  if(Director::getInstance()->getCaptureState())
  {
    if(Support::shaders(SHADER_COMPLEX))
    {
      Director::getInstance()->getCaptureTexture()->setGLProgram(
        GLProgramCache::getInstance()->getGLProgram("@shader.main.blur")
      );
    }
  }

  /**
   *
   *
   *
   */
  //Music->play("music-1", true);
  this->_defaultCamera = this->cameras.cameraBackground;
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
    case STATE_GAME:
    break;
    case STATE_UNLOCK:
    break;
    case STATE_SETTINGS:
    break;
    case STATE_STORE:
    break;
    case STATE_USERS:
    break;
    case STATE_MENU:
    if(Menu::getInstance()->state == Menu::STATE_MENU)
    {
      this->changeState(STATE_GAME);
    }
    break;
  }

  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_FINISH:
    break;
    case STATE_UNLOCK:
    break;
    case STATE_SETTINGS:
    break;
    case STATE_STORE:
    break;
    case STATE_USERS:
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
    case STATE_UNLOCK:
    break;
    case STATE_SETTINGS:
    break;
    case STATE_STORE:
    break;
    case STATE_USERS:
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
    case STATE_UNLOCK:
    break;
    case STATE_SETTINGS:
    break;
    case STATE_STORE:
    break;
    case STATE_USERS:
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

  /**
   *
   *
   *
   */
  this->reset();
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

void Game::onMail()
{
  Events::onMail();
}

void Game::onSound()
{
  Events::onSound();
}

void Game::onRestorePurchases()
{
  Events::onRestorePurchases();
}

void Game::onShare(
  int width,
  int height,
  int x,
  int y,
  bool animation,
  string text,
  const std::function<void(int)>& callback,
  const std::function<void(int, int)>& update
)
{
  Screenshot::save(
    width,
    height,
    x,
    y,
    [=] (bool state, const string filename) {

      /**
       *
       *
       *
       */
      Social::share(animation, text + " ?", callback, update);
    }
  );

  /**
   *
   *
   *
   */
  Events::onShare();

  /**
   *
   *
   *
   */
  Sound->play("capture");
}

/**
 *
 *
 *
 */
bool Game::onFacebookLike()
{
  return Events::onFacebookLike();
}

bool Game::onTwitterLike()
{
  return Events::onTwitterLike();
}

bool Game::onInstagramLike()
{
  return Events::onInstagramLike();
}

/**
 *
 *
 *
 */
bool Game::onTwitter()
{
  return Events::onTwitter();
}

bool Game::onFacebook()
{
  return Events::onFacebook();
}

bool Game::onInstagram()
{
  return Events::onInstagram();
}

/**
 *
 *
 *
 */
void Game::onMenu()
{
  Menu::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onMenu();
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

void Game::onUnlock()
{
  Unlock::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onUnlock();
}

void Game::onSettings()
{
  Settings::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onSettings();
}

void Game::onStore()
{
  Store::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onStore();
}

void Game::onUsers()
{
  Users::getInstance()->show();

  /**
   *
   *
   *
   */
  this->environment->onUsers();
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
int Game::getFrameWidth()
{
  return Director::getInstance()->getOpenGLView()->getFrameSize().width * Director::getInstance()->getOpenGLView()->getFrameZoomFactor() * Director::getInstance()->getOpenGLView()->getRetinaFactor();
}

int Game::getFrameHeight()
{
  return Director::getInstance()->getOpenGLView()->getFrameSize().height * Director::getInstance()->getOpenGLView()->getFrameZoomFactor() * Director::getInstance()->getOpenGLView()->getRetinaFactor();
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
      case STATE_UNLOCK:
      this->onUnlock();
      break;
      case STATE_SETTINGS:
      this->onSettings();
      break;
      case STATE_STORE:
      this->onStore();
      break;
      case STATE_USERS:
      this->onUsers();
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

void Game::updateUnlock(float time)
{
}

void Game::updateSettings(float time)
{
}

void Game::updateStore(float time)
{
}

void Game::updateUsers(float time)
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
    case STATE_UNLOCK:
    this->updateUnlock(time);
    break;
    case STATE_SETTINGS:
    this->updateSettings(time);
    break;
    case STATE_STORE:
    this->updateStore(time);
    break;
    case STATE_USERS:
    this->updateUsers(time);
    break;
  }

  this->environment->update(time);

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_NONE:
    break;
    case STATE_MENU:
    break;
    case STATE_FINISH:
    break;
    case STATE_UNLOCK:
    break;
    case STATE_SETTINGS:
    break;
    case STATE_STORE:
    break;
    case STATE_USERS:
    break;
    case STATE_GAME:
    if(Director::getInstance()->getCaptureState())
    {
      if(!Application->environment->capture->state->create)
      {
        Director::getInstance()->updateCapture();
      }
    }
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
