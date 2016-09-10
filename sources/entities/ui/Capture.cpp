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
Capture::Capture()
: ExtendedButton("ui/capture-background.png", 1, 1, Application, [=] () {
this->buttons.announce->onAction();
})
{
  this->buttons.announce = new AnnounceButton(this, [=] () {
    Application->onShare(
      Application->getFrameWidth(),
      Application->getFrameWidth(),
      0,
      Application->getFrameHeight() / 2 - Application->getFrameWidth() / 2,
      false,
      "", // @TODO: Add share text;
      [=] (int state) {
        if(state)
        {
          Application->counter->currency.handler->add(50, this->buttons.announce);
        }
      }
    );
  });
  this->buttons.announce->setCameraMask(BACKGROUND);

  /**
   *
   *
   *
   */
  auto holder = ClippingNode::create();
  holder->setAlphaThreshold(0.1f);
  holder->setScale(0.89);
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
  this->element = new Entity(holder, true);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
  this->setScheduleUpdate(true);
}

Capture::~Capture()
{
}

/**
 *
 *
 *
 */
void Capture::onCreate()
{
  ExtendedButton::onCreate();

  /**
   *
   *
   *
   */
  this->index = 0;

  /**
   *
   *
   *
   */
  this->setPosition(Application->getCenter().x, Application->getCenter().y);
  this->setScale(1.8);
  this->setOpacity(0.0);

  /**
   *
   *
   *
   */
  this->element->initWithTexture(Director::getInstance()->getCaptureTextures(this->index));
  this->element->setScaleX(1.0 * 0.6);
  this->element->setScaleY(-1.0 * 0.6);

  /**
   *
   *
   *
   */
  this->setCameraMask(BACKGROUND);
}

void Capture::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);
}

/**
 *
 *
 *
 */
void Capture::onAdd()
{
  ExtendedButton::onAdd();

  /**
   *
   *
   *
   */
  this->buttons.announce->add(this->getWidth() / 2, -20.0);
  this->buttons.announce->stopAllActions();
  this->buttons.announce->setScale(0.2);
  this->buttons.announce->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.5, 0.4)
      ),
      Sequence::create(
        EaseSineOut::create(
          FadeTo::create(0.5, 255.0)
        ),
        CallFunc::create([=] () {

          /**
           *
           *
           *
           */
          this->buttons.announce->onAdd();
        }),
        nullptr
      ),
      nullptr
    )
  );
}

void Capture::onRemove()
{
  ExtendedButton::onRemove();
}

/**
 *
 *
 *
 */
void Capture::add(float x, float y)
{
  if(!this->state->create)
  {
    this->_create();

    /**
     *
     *
     *
     */
    this->runAction(
      Spawn::create(
        EaseSineOut::create(
          ScaleTo::create(0.5, 2.0)
        ),
        Sequence::create(
          EaseSineOut::create(
            FadeTo::create(0.5, 255.0)
          ),
          CallFunc::create([=] () {

            /**
             *
             *
             *
             */
            this->onAdd();
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

void Capture::remove(bool action)
{
  if(this->state->create)
  {
    this->onRemove();

    /**
     *
     *
     *
     */
    this->buttons.announce->remove(action);

    /**
     *
     *
     *
     */
    this->runAction(
      Spawn::create(
        EaseSineIn::create(
          ScaleTo::create(0.5, 1.8)
        ),
        Sequence::create(
          EaseSineIn::create(
            FadeTo::create(0.5 - 0.1, 0.0)
          ),
          CallFunc::create([=] () {

            /**
             *
             *
             *
             */
            this->_destroy(action);
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

/**
 *
 *
 *
 */
void Capture::update(float time)
{
  if(this->index <= 0)
  {
   this->index = Director::getInstance()->getCaptureTexturesCount();
  }

  /**
   *
   *
   *
   */
  this->index--;

  /**
   *
   *
   *
   */
  this->element->initWithTexture(Director::getInstance()->getCaptureTextures(this->index));
}

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
Capture::Element::Element()
: Entity(true)
{
}

Capture::Element::~Element()
{
}

/**
 *
 *
 *
 */
void Capture::Element::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{

  /**
   *
   *
   *
   */
  Entity::visit(renderer, parentTransform, parentFlags);

  /**
   *
   *
   *
   */
  {
    auto scale = Application->environment->background->getScale();
    auto position = Application->environment->background->getPosition();

    /**
     *
     *
     *
     */
    Application->environment->background->setScale(1.0 / Director::getInstance()->getCaptureScale());
    Application->environment->background->setPosition(Director::getInstance()->getCaptureWidth() / 2, Director::getInstance()->getCaptureHeight() / 2);

    /**
     *
     *
     *
     */
    Application->environment->background->visit(renderer, parentTransform, parentFlags);

    /**
     *
     *
     *
     */
    Application->environment->background->setScale(scale);
    Application->environment->background->setPosition(position);
  }
  

  /**
   *
   *
   *
   */
  {
    auto scale = Application->counter->getScale();
    auto position = Application->counter->getPosition();

    /**
     *
     *
     *
     */
    Application->counter->setScale(1.0 / (Director::getInstance()->getCaptureScale() / 1.1));
    Application->counter->setPosition(Director::getInstance()->getCaptureWidth() / 2 - 18, Director::getInstance()->getCaptureHeight() * 0.65);

    /**
     *
     *
     *
     */
    Application->counter->visit(renderer, parentTransform, parentFlags);

    /**
     *
     *
     *
     */
    Application->counter->setScale(scale);
    Application->counter->setPosition(position);
  }
}
