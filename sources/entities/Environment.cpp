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
  this->plane->setPosition(0, 0, 0);
  this->plane->setRotation(0, 0, 0);

  this->ground = new Entity3D("plane.obj", this->plane, true);
  this->ground->setPosition(0, 0, 0);
  this->ground->setRotation(0, 0, 0);
  this->ground->setColor(Color3B(255, 255, 255));
  this->ground->setScale(10.5);

  this->background = new Entity("environments/1/background.png", this->plane, true);
  this->background->setPosition(Application->getCenter().x, Application->getCenter().y - 1280/2/2);
  this->background->setCameraMask(BACKGROUND);
  this->background->setScaleY(1.5);

  this->generator = new Generator;
  this->character = new Character;

  this->plates = new Pool(new Plate, this->plane);
}

void Environment::reset()
{
  this->texture = 1;

  //this->character->reset();
  this->generator->reset();

  this->background->setTexture(this->getBackgroundTexture());
  this->ground->setTexture(this->getPlaneTexture());
}
/**
 *
 *
 *
 */
string Environment::getBackgroundTexture()
{
  return "environments/" + s(this->texture) + "/background.png";
}

string Environment::getPlaneTexture()
{
  return "environments/" + s(this->texture) + "/plane-texture.png";
}

string Environment::getPlateTexture()
{
  return "environments/" + s(this->texture) + "/plate-texture.png";
}

/**
 *
 *
 *
 */
void Environment::onAction()
{
  this->character->onAction();
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
