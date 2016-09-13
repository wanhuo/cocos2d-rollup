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

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Character;
class Generator;

/**
 *
 *
 *
 */
class Environment : public Background
{

  /**
   *
   *
   *
   */
  public:
  enum Elements {
    ELEMENT_COUNTER,
    ELEMENT_NOTIFICATION_NODE
  };

  struct Texture {
    string environments;
    string background;
  };

  /**
   *
   *
   *
   */
  private:

  /**
   *
   *
   *
   */
  protected:
  float backgroundIndex = 0;

  /**
   *
   *
   *
   */
  public:
  Environment(Node* parent);
 ~Environment();

  int texture;

  Capture* capture;

  BackgroundColor* clear;

  Entity* background;

  Entity3D* plane;
  Entity3D* status;
  Entity3D* ground;

  Generator* generator;
  Character* character;

  Pool* plates;
  Pool* dusts;
  Pool* coins;

  virtual void create();
  virtual void reset();

  virtual Texture getTextures();

  virtual void onAction();

  virtual void onMenu();
  virtual void onGame();
  virtual void onFinish();
  virtual void onUnlock();
  virtual void onSettings();
  virtual void onStore();
  virtual void onUsers();

  virtual void onBackground(bool state);

  virtual void applyElements(ActionInterval* action, initializer_list<int> elements);
  virtual void showElements(initializer_list<int> elements);
  virtual void hideElements(initializer_list<int> elements);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateFinish(float time);

  virtual void update(float time);
};

#endif
