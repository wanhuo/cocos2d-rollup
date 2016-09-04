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
{this->enableShadow(true);
  this->setScheduleUpdate(true);

  /**
   *
   *
   *
   */
  if(!Director::getInstance()->getShadowState())
  {
    this->enableLight(false);

    this->setGLProgram(
      GLProgramCache::getInstance()->getGLProgram("@element.direction")
    );
  }
}

Plate::~Plate()
{
}

/**
 *
 *
 *
 */
void Plate::onEnter()
{
  Element::onEnter();
}

void Plate::onExit()
{
  Element::onExit();
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
  this->common = 1.0;
  this->flushed = 0;

  /**
   *
   *
   *
   */
  if(!Director::getInstance()->getShadowState())
  {
    this->update();
  }
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
void Plate::start(bool animation)
{
  this->setTexture(Application->environment->getTextures().environments);
  this->setOpacity(255);

  this->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 90 * (this->rotation == LEFT ? -1 : 1), 0))
    )
  );

  if(animation)
  {
    if(this->stage)
    {
      if(probably(50))
      {
        this->flushed = 1;
      }
    }

    this->setScaleY(0.0);

    this->runAction(
      EaseSineOut::create(
        ScaleTo::create(0.5, 1.0, 1.0 + (this->stage && !this->flushed ? 0.5 : 0.0), 1.0)
      )
    );
  }
  else
  {
    this->setScaleY(1.0);
  }
}

void Plate::finish()
{
  // TODO: Ахтунг!! Тут какая-то лажа происходит!
  this->Node::runAction(
    Spawn::create(
      Sequence::create(
        EaseSineIn::create(
          ScaleTo::create(0.5, 1.0, 0.01, 1.0)
        ),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(1.0),
        FadeTo::create(1.0, 0.0),
        CallFunc::create([=] () {
        this->_destroy(true);
        }),
        nullptr
      ),
      nullptr
    ),
    10
  );
}

void Plate::flush()
{
  this->flushed = 0;

  this->runAction(
    EaseSineOut::create(
      ScaleTo::create(0.5, 1.0, 1.5, 1.0)
    )
  );
}

/**
 *
 *
 *
 */
void Plate::update()
{
  if(this->getGLProgram())
  {
    this->getGLProgramState()->setUniformFloat("common", this->common);
  }
}

void Plate::update(float time)
{
  if(this->common > 1.0)
  {
    this->common -= 0.02;

    /**
     *
     *
     *
     */
    this->update();
  }
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
