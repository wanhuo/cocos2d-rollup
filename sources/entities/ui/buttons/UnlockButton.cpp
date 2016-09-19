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
UnlockButton::UnlockButton(Node* parent)
: ExtendedButton("ui/button-unlock.png", 3, 1, parent, std::bind(&UnlockButton::onAction, this))
{
  this->texture = new Entity("characters/1000/texture.png", this);
  this->texture->setLocalZOrder(-1);
  this->texture->setScale(1.627);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
}

UnlockButton::~UnlockButton()
{
}

/**
 *
 *
 *
 */
void UnlockButton::onCreate()
{
  ExtendedButton::onCreate();

  /**
   *
   *
   *
   */
  this->setPosition(Application->getCenter());
  this->setCurrentFrameIndex(0);

  /**
   *
   *
   *
   */
  Unlock::getInstance()->texts.currency->_create();
  Unlock::getInstance()->texts.currency->setCameraMask(BACKGROUND);
  Unlock::getInstance()->texts.currency->setOpacity(0);
  Unlock::getInstance()->texts.currency->setScale(0.8);
  Unlock::getInstance()->texts.currency->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 255.0)
      ),
      nullptr
    )
  );

  Unlock::getInstance()->icon->_create();
  Unlock::getInstance()->icon->setCameraMask(BACKGROUND);
  Unlock::getInstance()->icon->setOpacity(0);
  Unlock::getInstance()->icon->setScale(0.8);
  Unlock::getInstance()->icon->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 255.0)
      ),
      nullptr
    )
  );

  Unlock::getInstance()->texts.text->_create();
  Unlock::getInstance()->texts.text->setText("@buttons.unlock.character." + convert(random(1, 2)));
  Unlock::getInstance()->texts.text->setCameraMask(BACKGROUND);
  Unlock::getInstance()->texts.text->setOpacity(0);
  Unlock::getInstance()->texts.text->setScale(0.8);
  Unlock::getInstance()->texts.text->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 1.0)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 255.0)
      ),
      nullptr
    )
  );
}

void UnlockButton::onDestroy(bool action)
{
  ExtendedButton::onDestroy(action);

  /**
   *
   *
   *
   */
  this->texture->_destroy();
}

/**
 *
 *
 *
 */
void UnlockButton::onAdd()
{
  ExtendedButton::onAdd();

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      CallFunc::create([=] () {

      /**
       *
       *
       *
       */
      auto count = random(2, 5);
      auto d = random(0.5, 1.0);
      auto time = 0.1;

      /**
       *
       *
       *
       */
      this->runAction(
        RepeatForever::create(
          Spawn::create(
            Sequence::create(
              DelayTime::create(d),
              Repeat::create(
                Sequence::create(
                  EaseSineIn::create(
                    RotateTo::create(time, -15.0)
                  ),
                  EaseSineIn::create(
                    RotateTo::create(time, 15.0)
                  ),
                  nullptr
                ),
                count
              ),
              EaseSineIn::create(
                RotateTo::create(time, 0.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(d),
              EaseSineOut::create(
                ScaleTo::create(time * (count + 1) * 2, 1.1)
              ),
              EaseSineIn::create(
                ScaleTo::create(time * 2, 1.0)
              ),
              nullptr
            ),
            nullptr
            )
          )
        );
      }),
      nullptr
    )
  );
}

void UnlockButton::onRemove()
{
  ExtendedButton::onRemove();
}

/**
 *
 *
 *
 */
void UnlockButton::onAction()
{
  Unlock::getInstance()->texts.currency->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 0.8)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 0.0)
      ),
      nullptr
    )
  );

  Unlock::getInstance()->icon->runAction(
    Spawn::create(
      EaseSineOut::create(
        ScaleTo::create(0.2, 0.8)
      ),
      EaseSineOut::create(
        FadeTo::create(0.2, 0.0)
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->stopAllActions();

  /**
   *
   *
   *
   */
  this->runAction(
    Spawn::create(
      RotateTo::create(0.2, 0),
      ScaleTo::create(0.2, 1.0),
      Sequence::create(
        DelayTime::create(0.2),
        EaseSineIn::create(
          RotateBy::create(3.0, Vec3(0.0, 360.0 * 10, 0.0))
        ),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(2.8),
        CallFunc::create([=] () {
          this->stopAllActions();
          this->setRotation3D(Vec3(0, 0, 0));
          this->setCurrentFrameIndex(2);

          /**
           *
           *
           *
           */
          Application->environment->clear->runAction(
            Sequence::create(
              FadeTo::create(0.1, 255.0),
              CallFunc::create([=] () {
                auto element = Store::getInstance()->element(true);

                /**
                 *
                 *
                 *
                 */
                this->texture->_create();
                this->texture->setCameraMask(BACKGROUND);
                this->texture->setPosition(this->getWidth() / 2, this->getHeight() / 2);
                this->texture->setTexture("characters/" + convert(element.index) + "/texture.png");

                /**
                 *
                 *
                 *
                 */
                Unlock::getInstance()->texts.text->setText("@store.new.character." + convert(random(1, 2)));

                /**
                 *
                 *
                 *
                 */
                Unlock::getInstance()->showButtons();
              }),
              DelayTime::create(0.1),
              FadeTo::create(0.3, 0.0),
              nullptr
            )
          );
        }),
        nullptr
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->bind(false);
}
