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
Ground2::Ground2(Node* parent)
: Entity3D(parent, true)
{
  this->texture = new Entity("sphere-texture.png", this, true);
  this->texture->getTexture()->setTexParameters({GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT});
  this->texture->getTexture()->setAliasTexParameters();
  this->texture->setScale(0.01);

  this->setRotation(-90, 0, 0);
  this->setGlobalZOrder(-1);
  this->texture->setGlobalZOrder(-1);

  this->setScheduleUpdate(true);
}

Ground2::~Ground2()
{
}

/**
 *
 *
 *
 */
void Ground2::reset()
{
}

/**
 *
 *
 *
 */
void Ground2::update(float time)
{
y-=1.01f;
  this->texture->setTextureRect(Rect(x, y, 100000, 100000));
}
