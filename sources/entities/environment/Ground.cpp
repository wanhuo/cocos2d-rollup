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
Ground::Ground(Node* parent)
: Element(parent)
{
  this->initWithPhysics();
  this->initWithBody();

  this->texture = new Entity("ground-texture.png", this, true);
  this->texture->getTexture()->generateMipmap();
  this->texture->getTexture()->setTexParameters({GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT});
  this->texture->getTexture()->setAliasTexParameters();
  this->texture->setOpacity(190);
  this->texture->setScale(0.002);

  this->setRotation(-90, 0, 0);

  this->setScheduleUpdate(true);
  this->_create();
  this->update(0);
}

Ground::~Ground()
{
}

/**
 *
 *
 *
 */
void Ground::initWithPhysics()
{
  Physics3DRigidBodyDes fixture;

  fixture.mass = 0.0;
  fixture.shape = Physics3DShape::createBox(Vec3(10.0, 20.0, 0.0));

  this->_physicsComponent = Physics3DComponent::create(Physics3DRigidBody::create(&fixture));
  this->_physicsComponent->retain();

  this->addComponent(this->_physicsComponent);
}

void Ground::initWithBody()
{
  this->getBody()->setRestitution(0.5);
  this->getBody()->setFriction(1.0);
}

/**
 *
 *
 *
 */
void Ground::reset()
{
}

/**
 *
 *
 *
 */
void Ground::update(float time)
{
  auto x = Application->getCamera()->getPositionX();
  auto y = 0;
  auto z = Application->getCamera()->getPositionZ() - 15.0;

  this->setPosition(x, y, z);

  this->texture->setTextureRect(Rect(x / 0.002, z / 0.002, 5000, 10000));
}
