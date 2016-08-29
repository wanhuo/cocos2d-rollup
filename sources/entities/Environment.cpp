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
Environment::Environment(Node* parent)
: Background(parent)
{
}

Environment::~Environment()
{
}

/**
 *
 *
 *
 */
void Environment::create()
{
  this->plane = new Entity3D(this, true);
  this->plane->setRotation3D(Vec3(0, 0, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  /**
   *
   *
   *
   */
  this->plates = new Pool(new Plate, this->plane);

  /**
   *
   *
   *
   */
  new Ground2(this->plane);
  this->ground = new Ground(this->plane);

  /**
   *
   *
   *
   */
  for(int i = 0; i < 1000; i++)
  {
    this->plates->_create()->setPosition(0, -10000, 0);
  }
}

void Environment::reset()
{
}

/**
 *
 *
 *
 */
void Environment::onAction()
{
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
  this->reset();
}

void Environment::onGame()
{
}

void Environment::onFinish()
{
}

/**
 *
 *
 *
 */
void Environment::updateMenu(float time)
{
}

void Environment::updateGame(float time)
{
}

void Environment::updateFinish(float time)
{
}

/**
 *
 *
 *
 */
void Environment::update(float time)
{
  switch(Application->state)
  {
    case Game::STATE_NONE:
    break;
    case Game::STATE_MENU:
    this->updateMenu(time);
    break;
    case Game::STATE_GAME:
    this->updateGame(time);
    break;
    case Game::STATE_FINISH:
    this->updateFinish(time);
    break;
  }
}
