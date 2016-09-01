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
Generator::Generator()
{
}

Generator::~Generator()
{
}

/**
 *
 *
 *
 */
Plate* Generator::element(int index)
{
  auto elements = Application->environment->plates;

  /**
   *
   *
   *
   */
  for(auto el : *elements->elements)
  {
    auto element = static_cast<Plate*>(el);

    if(element->index == index)
    {
      return element;
    }
  }

  return nullptr;
}

/**
 *
 *
 *
 */
void Generator::create(bool animation)
{
  auto elements = Application->environment->plates;

  /**
   *
   *
   *
   */
  switch(this->direction)
  {
    case NONE:
    this->parameters.rotation = random(-this->parameters.pullement, this->parameters.pullement);
    break;
    case RIGHT:
    case LEFT:
    auto rotation = 0.0;

    this->parameters.pullement *= this->parameters.escarpment;
    rotation += this->parameters.pullement;

    switch(this->direction)
    {
      case RIGHT:
      this->parameters.rotation = rotation;
      break;
      case LEFT:
      this->parameters.rotation = rotation;
      break;
    }
    break;
  }

  /**
   *
   *
   *
   */
  if((this->parameters.length.current > this->parameters.length.min && probably(this->parameters.probability)) || this->parameters.length.current >= this->parameters.length.max)
  {
    this->direction = random(0, 2);

    switch(this->direction)
    {
      case RIGHT:
      case LEFT:
      this->parameters.length.min = random(2, 20);
      this->parameters.length.max = random(this->parameters.length.min, this->parameters.length.min * 2);
      this->parameters.probability = random(0, 100);

      this->parameters.escarpment = random(1.0, 1.2);
      this->parameters.pullement = random(1.0, 40.0);
      break;
      case NONE:
      this->parameters.length.min = random(2, 10);
      this->parameters.length.max = random(this->parameters.length.min, this->parameters.length.min * 2);
      this->parameters.probability = random(0, 100);

      this->parameters.pullement = random(0.0, 50.0);
      break;
    }

    this->parameters.length.current = 0;
  }

  /**
   *
   *
   *
   */
  auto rotation = 180 + 22.5 / 4 / 2 - this->parameters.rotation;
  auto r = 0.9;

  this->previous.position.x =  elements->count ? (r * sin(CC_DEGREES_TO_RADIANS(rotation)) + this->previous.position.x) : 0;
  this->previous.position.z =  elements->count ? (r * cos(CC_DEGREES_TO_RADIANS(rotation)) + this->previous.position.z) : 0;
  this->previous.position.y = 0;

  this->previous.rotation.y = elements->count ? (-(22.5 - rotation * 2) - this->previous.rotation.y) : 0;
  this->previous.rotation.x = 0;
  this->previous.rotation.z = 0;

  if(true)
  {
    if(animation)
    {
      this->previous.rotation.y = -(22.5 - rotation * 2) - elements->last()->getRotation3D().y;
    }

    auto current = static_cast<Plate*>(elements->_create());

    current->setPosition(this->previous.position.x, this->previous.position.y, this->previous.position.z);
    current->setRotation(this->previous.rotation.x, this->previous.rotation.y, this->previous.rotation.z);

    /**
     *
     *
     *
     */
    current->index = this->index;
    current->rotation = this->rotation;

    current->start(animation);
  }

  /**
   *
   *
   *
   */
  this->rotation = this->rotation == LEFT ? RIGHT : LEFT;
  this->index++;

  this->parameters.length.current++;
}

void Generator::destroy()
{
}

/**
 *
 *
 *
 */
void Generator::reset()
{
  this->index = 0;
  this->rotation = 0;
  this->direction = 0;

  this->previous.position.x = 0;
  this->previous.position.y = 0;
  this->previous.position.z = 0;

  this->previous.rotation.x = 0;
  this->previous.rotation.y = 0;
  this->previous.rotation.z = 0;

  this->parameters.rotation = 0;
  this->parameters.length.current = 0;
  this->parameters.length.min = 10;
  this->parameters.length.max = 20;
  this->parameters.probability = 50;

  this->parameters.pullement = random(0.0, 50.0);

  /**
   *
   *
   *
   */
  for(int i = 0; i < COUNT_START; i++)
  {
    this->create();
  }
}
