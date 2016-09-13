/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) by Igor Mats
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
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Steps::Steps(Node* parent)
: ExtendedButton("ui/capture-background.png", 1, 1, parent, [=] () {
// @TODO:
})
{
  auto holder = ClippingNode::create();
  holder->setAlphaThreshold(0.05f);
  holder->setScale(0.88);
  holder->setPosition(this->getWidth() / 2, this->getHeight() / 2);
  holder->setCascadeOpacityEnabled(true);
  holder->setStencil(
    Sprite::create(this->textureFileName)
  );

  this->addChild(holder);

  /**
   *
   *
   *
   */
  this->element = new Entity("ui/steps.png", holder, true);
  this->element->setScale(2.0);

  /**
   *
   *
   *
   */
  this->elements = new Pool(new Entity(this->textureFileName), this);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

Steps::~Steps()
{
}

/**
 *
 *
 *
 */
void Steps::onCreate()
{
  ExtendedButton::onCreate();

  /**
   *
   *
   *
   */
  this->setCameraMask(BACKGROUND);
}

void Steps::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);

  /**
   *
   *
   *
   */
  this->elements->clear();
}

/**
 *
 *
 *
 */
void Steps::onAdd()
{
  ExtendedButton::onAdd();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {

          /**
           *
           *
           *
           */
          auto element = this->elements->_create();

          element->setScale(1.0);
          element->setOpacity(255);
          element->setLocalZOrder(-1);
          element->setPosition(this->getWidth() / 2, this->getHeight() / 2);
          element->setCameraMask(BACKGROUND);
          element->runAction(
            Spawn::create(
              Sequence::create(
                EaseSineInOut::create(
                  ScaleTo::create(1.0, 1.5)
                ),
                nullptr
              ),
              Sequence::create(
                EaseSineInOut::create(
                  FadeTo::create(1.0, 0.0)
                ),
                CallFunc::create([=] () {
                element->_destroy();
                }),
                nullptr
              ),
              nullptr
            )
          );
        }),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );
}

void Steps::onRemove()
{
  ExtendedButton::onRemove();
}
