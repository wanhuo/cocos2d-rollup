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
  this->setTexture("plate-texture.png");
  //this->setOpacity(200);
 // this->setCullFaceEnabled(false);
 this->setColor(Color3B(0, 150, 255));
}

Plate::~Plate()
{
}

/**
 *
 *
 *
 */
void Plate::onCreate()
{
  Element::onCreate();
}

void Plate::onDestroy(bool action)
{
  Element::onDestroy(action);
}

/**
 *
 *
 *
 */
bool Plate::setNormal(bool normal)
{
  if(normal)
  {
    this->setScaleX(1.0);
    this->setScaleY(random(0.1, 0.5));
    this->setScaleZ(1.0);
  }
  else
  {
    this->setScaleX(2.0);
    this->setScaleY(0.01);
    this->setScaleZ(2.0);
    //this->setColor(Color3B::RED);

    /**
     *
     *
     *
     */
    auto generator = Application->environment->generator;

    auto x = this->getPositionX();
    auto y = this->getPositionY();
    auto z = this->getPositionZ();

    int px = generator->x + Generator::POSITION_MAX;
    int py = generator->y;
    int pz = generator->z * -1;

        Generator::Element element;

        element.active = true;
        element.normal = false;
        element.element = this;

    /**
     *
     *
     *
     */
    switch((int) generator->direction.x)
    {
      case Generator::LEFT:
      {
        //this->setColor(Color3B::MAGENTA);
        this->setPosition(x - 0.5, y, z - 0.5);

        generator->x--;

        if(probably(50))
        {
          generator->z--;
        }
        else
        {
          if(generator->x <= Generator::POSITION_MIN)
          {
            generator->z--;
          }
          else
          {
            generator->z--;
            generator->min.z++;
          }
        }

        generator->elements[px][pz] = element;
        generator->elements[px - 1][pz] = element;
        generator->elements[px][pz + 1] = element;
        generator->elements[px - 1][pz + 1] = element;
      }
      break;
      case Generator::RIGHT:
      {
        //this->setColor(Color3B::GREEN);
        this->setPosition(x + 0.5, y, z - 0.5);

        generator->x++;

        if(probably(50))
        {
          generator->z--;
        }
        else
        {
          if(generator->x >= Generator::POSITION_MAX)
          {
            generator->z--;
          }
          else
          {
            generator->z--;
            generator->min.z++;
          }
        }

        generator->elements[px][pz] = element;
        generator->elements[px + 1][pz] = element;
        generator->elements[px][pz + 1] = element;
        generator->elements[px + 1][pz + 1] = element;
      }
      break;
    }

    switch((int) generator->direction.z)
    {
      case Generator::FORWARD:
      {
        //this->setColor(Color3B::RED);
        this->setPosition(x + 0.5 * ((generator->x > 0) ? -1 : 1), y, z - 0.5);

        generator->elements[px][pz] = element;
        generator->elements[px + ((generator->x > 0) ? -1 : 1)][pz] = element;
        generator->elements[px][pz + 1] = element;
        generator->elements[px + ((generator->x > 0) ? -1 : 1)][pz + 1] = element;

        generator->z--;
            generator->min.z++;

        {
          if(generator->x > 0)
          {
            generator->x--;
          }
          else
          {
            generator->x++;
          }
        }
      }
      break;
      case Generator::BACK:
      //this->setColor(Color3B::YELLOW);
      break;
    }
  }

  this->normal = normal;

  return this->normal;
}

bool Plate::getNormal()
{
  return this->normal;
}

/**
 *
 *
 *
 */
int Plate::setIndex(int index)
{
  this->index = index;
  return this->index;
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
