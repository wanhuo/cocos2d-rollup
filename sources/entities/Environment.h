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
  Entity3D* ground;
  Entity3D* cube;

  Entity3D* z;

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
  public:
  Environment(Node* parent);
 ~Environment();

  Entity3D* plane;

  Character* character = nullptr;
  Generator* generator = nullptr;

  Pool* plates;

  virtual void create();
  virtual void reset();

  virtual Plate* element(int index);

  virtual void onAction();

  virtual void onMenu();
  virtual void onGame();
  virtual void onFinish();

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateFinish(float time);

  virtual void update(float time);
};

#endif
