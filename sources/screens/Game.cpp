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

  float x = 0;
  float y = 0;
  float z = 45;

  float rx = -40;
  float ry = -40;
  float rz = 0;

  this->startCameraX = x;
  this->startCameraY = y;
  this->startCameraZ = z;

  this->startCameraRotationX = rx;
  this->startCameraRotationY = ry;
  this->startCameraRotationZ = rz;

  this->cameras.d->setPosition3D(Vec3(x, y, z));
  this->cameras.d->setRotation3D(Vec3(rx, ry, rz));

  this->addChild(this->cameras.d);
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
  auto size = Size(Director::getInstance()->getWinSizeInPixels().width, Director::getInstance()->getWinSizeInPixels().height);

  this->frameBuffer = FrameBuffer::create(1, size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);

  auto rt = RenderTarget::create(size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);
  auto rtDS = RenderTargetDepthStencil::create(size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);
  this->frameBuffer->attachRenderTarget(rt);
  this->frameBuffer->attachDepthStencilTarget(rtDS);

  this->generate = Sprite::createWithTexture(this->getFrameBuffer()->getRenderTarget()->getTexture());
  this->generate->setScaleX(1 * FRAME_BUFFER_FACTOR);
  this->generate->setScaleY(-1 * FRAME_BUFFER_FACTOR);
  this->generate->setPosition(size.width / 2, size.height / 2);
  this->generate->setCameraMask(2);
  this->generate->setGlobalZOrder(1);
  this->addChild(this->generate);

  for(int i = 0; i < CAPTURE_FPS * CAPTURE_TIME; i++)
  {
    auto render = RenderTexture::create(size.width / FRAME_BUFFER_FACTOR / CAPTURE_SCALE, size.width / FRAME_BUFFER_FACTOR / CAPTURE_SCALE, Texture2D::PixelFormat::RGB565);
    render->retain();

    //this->capturing.textures.push_back(render);
  }

  this->cameras.d->setFrameBufferObject(this->getFrameBuffer());
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
void Game::onGame()
{
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
      case GAME:
      this->onGame();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Game::updateGame(float time)
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
    case GAME:
    this->updateGame(time);
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
