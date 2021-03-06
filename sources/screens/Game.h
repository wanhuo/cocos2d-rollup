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

#ifndef _GAME_H_
#define _GAME_H_

#include "Entity.h"
#include "PhysicsEntity3D.h"
#include "TiledEntity.h"
#include "AnimatedEntity.h"
#include "Entity3D.h"
#include "CameraEntity3D.h"
#include "Button.h"
#include "Text.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "Screen.h"
#include "Pool.h"
#include "Spine.h"

#include "RotateGlobalBy.h"
#include "Shake.h"

#include "Element.h"
#include "Plate.h"
#include "Character.h"

#include "Environment.h"
#include "Generator.h"

#include "Color.h"

/**
 *
 *
 *
 */
using namespace cocos2d;
using namespace cocos2d::experimental;

/**
 *
 *
 *
 */
#define Application Game::getInstance()
#define Generators Application->environment->generator
#define s(parameter) to_string(parameter)

/**
 *
 *
 *
 */
class Game : public Screen
{
  /**
   *
   *
   *
   */
  private:
  static Game* instance;

  const static int NEAR = 1;
  const static int FAR = 10000;

  struct Cameras {
    Camera* defaultCamera;
    Camera* shadowCastCamera;
    Camera* frameBufferCamera;
    Camera* captureBufferCamera;
  };

  /**
   *
   *
   *
   */
  public:
  enum State {
    STATE_NONE,
    STATE_MENU,
    STATE_GAME,
    STATE_FINISH
  };

  /**
   *
   *
   *
   */
  public:
  static Game* getInstance();

  Game();
 ~Game();

  Environment* environment;

  Cameras cameras;

  State state = STATE_NONE;

  virtual Camera* getCamera();

  virtual void onTouchStart(cocos2d::Touch* touch, Event* event);
  virtual void onTouchFinish(cocos2d::Touch* touch, Event* event);

  virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, Event *event);
  virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, Event *event);

  virtual void onEnter();
  virtual void onExit();

  virtual void onBack();

  virtual void onLeaderboards();
  virtual void onAchievements();
  virtual void onRate();
  virtual void onFacebookLike();
  virtual void onTwitterLike();
  virtual void onShare(bool action, bool complete, const std::function<void(int)>& callback, const std::function<void(int, int)>& update);
  virtual void onTwitter();
  virtual void onFacebook();
  virtual void onMail();
  virtual void onRestorePurchases();

  virtual void onMenu();
  virtual void onGame();
  virtual void onFinish();

  virtual void onNoad();

  virtual void changeState(State state);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateFinish(float time);

  virtual void updateStates(float time);

  virtual void update(float time);
};

#endif
