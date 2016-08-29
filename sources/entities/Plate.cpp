/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version of cocos2d is 3.5
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Plate::Plate()
: Element("plate.obj")
{
  this->initWithPhysics();
  this->initWithBody();
}

Plate::~Plate()
{
}

/**
 *
 *
 *
 */
void Plate::initWithPhysics()
{
  Physics3DRigidBodyDes fixture;

  fixture.mass = 0;
  fixture.shape = Physics3DShape::createBox(Vec3(1.0f, Generator::SIZE * 2, 1.0f));

  this->_physicsComponent = Physics3DComponent::create(Physics3DRigidBody::create(&fixture));
  this->_physicsComponent->retain();

  this->addComponent(this->_physicsComponent);
}

void Plate::initWithBody()
{
  this->getBody()->setRestitution(1.0);
  this->getBody()->setFriction(0.0);
}

/**
 *
 *
 *
 */
void Plate::onCreate()
{
  Element::onCreate();

  /**
   *
   *
   *
   */
  this->setColor(Color::t());
}

void Plate::onDestroy(bool action)
{
  Element::onDestroy(action);
  log("%d", this->index);
}

/**
 *
 *
 *
 */
int Plate::setIndex(int index)
{
  return this->index = index;
}

int Plate::getIndex()
{
  return this->index;
}

/**
 *
 *
 *
 */
Plate* Plate::deepCopy()
{
  return new Plate;
}
