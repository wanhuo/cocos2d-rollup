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
  this->buttons.announce = new AnnounceButton(Application, [=] () {
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
  }, AnnounceButton::TYPE_LARGE);
  this->buttons.announce->setPosition(Application->getCenter().x, Application->getCenter().y - 320.0);
  this->buttons.announce->setCameraMask(BACKGROUND);

  /**
   *
   *
   *
   */
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
  this->element = new Entity(holder, true);

  /**
   *
   *
   *
   */
  this->elements = new Pool(new Entity("ui/ring-pulse.png"), this);

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
  this->element->initWithTexture(Director::getInstance()->getCaptureTextures(this->index));
  this->element->setScaleX(1.0 * 1.1);
  this->element->setScaleY(-1.0 * 1.1);

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
void Capture::onAdd()
{
  ExtendedButton::onAdd();

  /**
   *
   *
   *
   */
  this->buttons.announce->add();

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
                  ScaleTo::create(1.4, 1.3)
                ),
                nullptr
              ),
              Sequence::create(
                EaseSineInOut::create(
                  FadeTo::create(1.4, 0.0)
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
        DelayTime::create(0.6),
        nullptr
      )
    )
  );
}

void Capture::onRemove()
{
  ExtendedButton::onRemove();

  /**
   *
   *
   *
   */
  this->buttons.announce->remove();
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
