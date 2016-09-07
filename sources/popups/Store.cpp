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
Store* Store::instance;

/**
 *
 *
 *
 */
Store* Store::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Store::Store()
: Popup()
{
  instance = this;

  /**
   *
   *
   *
   */
  this->texture = RenderTexture::create(Application->getWidth(), Application->getHeight() - 300, Texture2D::PixelFormat::RGBA8888);
  this->texture->setPosition(Application->getCenter());
  this->addChild(this->texture);

  this->texture->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("@shader.opacity.vertical"));
  this->texture->getSprite()->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
  this->texture->getSprite()->getTexture()->setAntiAliasTexParameters();

  /**
   *
   *
   *
   */
  this->buttons.services = new ExtendedButton("ui/button-services.png", 2, 1, this, std::bind(&Store::onServices, this));
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, std::bind(&Store::onMenu, this));
  this->buttons.share = new ExtendedButton("ui/button-share.png", 2, 1, this, std::bind(&Store::onShare, this));
  this->buttons.present = new PresentButton(this);
  this->buttons.video = new VideoButton(this);

  /**
   *
   *
   *
   */
  this->scroll = new BackgroundScroll(this);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 300));
  this->scroll->setBounceEnabled(true);
  this->scroll->setTouchEnabled(true);
  this->scroll->setSwallowTouches(false);
  this->scroll->setScrollBarEnabled(false);
  this->scroll->setPositionY(300);

  /**
   *
   *
   *
   */
  this->separator2 = new Entity("ui/store-separator.png", this->scroll);
  this->separator3 = new Entity("ui/store-separator.png", this->scroll);

  /**
   *
   *
   *
   */
  this->texts.more1 = new Text("@store.more", this->scroll);
  this->texts.more2 = new Text("@store.more", this->scroll);

  this->texts.separator2 = new Text("@store.separator.1", this->separator2, true);
  this->texts.separator3 = new Text("@store.separator.2", this->separator3, true);

  /**
   *
   *
   *
   */
  this->elements = new Pool(new Element, this->scroll);

  /**
   *
   *
   *
   */
  auto rootJsonData = Json_create(FileUtils::getInstance()->getStringFromFile("store.json").c_str());
  auto charactersJsonData = Json_getItem(rootJsonData, "@characters");
  auto regularJsonData = Json_getItem(charactersJsonData, "@regular");
  auto rareJsonData = Json_getItem(charactersJsonData, "@rare");
  auto mythicalJsonData = Json_getItem(charactersJsonData, "@mythical");

  for(auto state : {regularJsonData, rareJsonData, mythicalJsonData})
  {
    for(auto element = state->child; element; element = element->next)
    {
      auto index = Json_getInt(element, "index", 0);
      auto category = Json_getInt(element, "category", 0);
      auto state = Json_getInt(element, "state", 0);
      auto action = Json_getInt(element, "action", 0);
      auto price = Json_getFloat(element, "price", 0.0);

      this->states.push_back({
        index,
        category,
        state,
        action,
        price
      });
    }
  }
}

Store::~Store()
{
}

/**
 *
 *
 *
 */
void Store::onEnter()
{
  auto position = Vec2(Application->getCenter().x, 200.0);

  /**
   *
   *
   *
   */
  this->buttons.menu->add(position.x, position.y);
  this->buttons.services->add(position.x - 128, position.y);
  this->buttons.share->add(position.x - 256, position.y);
  this->buttons.video->add(position.x + 128, position.y);
  this->buttons.present->add(position.x + 256, position.y);

  /**
   *
   *
   *
   */
  this->elements->clear();

  /**
   *
   * @Store
   * | @Store.Elements;
   *
   */
   {
    /**
     *
     *
     *
     */
    auto time = 0.0;
    auto position = Vec2(0, 0);

    /**
     *
     * @Store.Elements
     * | @Position Reset;
     *
     */
    auto reset = [&] () -> Vec2 {
      position.x = 0;

      return Vec2(Application->getCenter().x + (position.x - 2.5) * 160, Application->getHeight() - 200 - position.y * 160);
    };

    /**
     *
     * @Store.Elements
     * | @Position Update;
     *
     */
    auto update = [&] () -> Vec2 {
      time += 0.02;

      /**
       *
       *
       *
       */
      if(++position.x > 4)
      {
        position.x = 1;
        position.y++;
      }

      return Vec2(Application->getCenter().x + (position.x - 2.5) * 160, Application->getHeight() - 200 - position.y * 160);
    };

    /**
     *
     * @Store.Elements
     * | @New Element;
     *
     */
    auto handler = [&] (Data state) {
      state.state = Storage::get("@store.states." + convert(state.index)) || state.state;

      /**
       *
       *
       *
       */
      if(state.state || state.action)
      {
        auto element = (Store::Element*) this->elements->_create();

        /**
         *
         *
         *
         */
        element->setState(state.state);
        element->setAction(state.action);
        element->setIndex(state.index);
        element->setPrice(state.price);
        element->setCategory(state.category);

        /**
         *
         *
         *
         */
        element->setPosition(update());

        /**
         *
         *
         *
         */
        element->runAction(
          Spawn::create(
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                FadeTo::create(0.2, 255.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                ScaleTo::create(0.2, 1.1)
              ),
              EaseSineIn::create(
                ScaleTo::create(0.5, 1.0)
              ),
              nullptr
            ),
            nullptr
          )
        );
      }
    };

    /**
     *
     * @Store.Elements
     * | @1;
     *
     */
    for(auto state : this->states)
    {
      if(state.category == CATEGORY_REGULAR)
      {
        handler(state);

        /**
         *
         *
         *
         */
        if(this->count(CATEGORY_REGULAR, true) == 4)
        {
          position.y += 0.1;
        }
      }
    }

    /**
     *
     * @Store.Elements
     * | @1.Text.More;
     *
     */
    if(true)
    {
      if(this->count(CATEGORY_REGULAR))
      {
        this->texts.more1->_create();
        this->texts.more1->data(this->count(CATEGORY_REGULAR));
        this->texts.more1->setOpacity(0);
        this->texts.more1->setScale(0.8);
        this->texts.more1->setPosition(Application->getCenter().x, reset().y - 90);
        this->texts.more1->runAction(
          Spawn::create(
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                FadeTo::create(0.2, 255.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                ScaleTo::create(0.2, 1.1)
              ),
              EaseSineIn::create(
                ScaleTo::create(0.5, 1.0)
              ),
              nullptr
            ),
            nullptr
          )
        );
      }
    }

    /**
     *
     * @Store.Elements
     * | @2;
     *
     */
    if(this->count(CATEGORY_RARE, true))
    {
      /**
       *
       * @Store.Elements
       * | @2.Separator;
       *
       */
      this->texts.separator2->setPosition(this->separator2->getWidth() / 2 , this->separator2->getHeight() / 2 + 5);

      this->separator2->_create();
      this->separator2->setCascadeOpacityEnabled(true);
      this->separator2->setOpacity(0);
      this->separator2->setScale(0.8);
      this->separator2->setPosition(Application->getCenter().x, reset().y - 150);
      this->separator2->runAction(
        Spawn::create(
          Sequence::create(
            DelayTime::create(time),
            EaseSineOut::create(
              FadeTo::create(0.2, 255.0)
            ),
            nullptr
          ),
          Sequence::create(
            DelayTime::create(time),
            EaseSineOut::create(
              ScaleTo::create(0.2, 1.1)
            ),
            EaseSineIn::create(
              ScaleTo::create(0.5, 1.0)
            ),
            nullptr
          ),
          nullptr
        )
      );

      position.y += 1.6;

      /**
       *
       * @Store.Elements
       * | @2;
       *
       */
      for(auto state : this->states)
      {
        if(state.category == CATEGORY_RARE)
        {
          handler(state);
        }
      }

      /**
       *
       * @Store.Elements
       * | @2.Text.More;
       *
       */
      if(this->count(CATEGORY_RARE))
      {
        this->texts.more2->_create();
        this->texts.more2->setOpacity(0);
        this->texts.more2->setScale(0.8);
        this->texts.more2->setPosition(Application->getCenter().x, reset().y - 90);
        this->texts.more2->runAction(
          Spawn::create(
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                FadeTo::create(0.2, 255.0)
              ),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(time),
              EaseSineOut::create(
                ScaleTo::create(0.2, 1.1)
              ),
              EaseSineIn::create(
                ScaleTo::create(0.5, 1.0)
              ),
              nullptr
            ),
            nullptr
          )
        );
      }
    }

    /**
     *
     * @Store.Elements
     * | @3;
     *
     */
    if(true)
    {
      /**
       *
       * @Store.Elements
       * | @2.Separator;
       *
       */
      this->texts.separator3->setPosition(this->separator3->getWidth() / 2 , this->separator3->getHeight() / 2 + 5);

      this->separator3->_create();
      this->separator3->setCascadeOpacityEnabled(true);
      this->separator3->setOpacity(0);
      this->separator3->setScale(0.8);
      this->separator3->setPosition(Application->getCenter().x, reset().y - 150);
      this->separator3->runAction(
        Spawn::create(
          Sequence::create(
            DelayTime::create(time),
            EaseSineOut::create(
              FadeTo::create(0.2, 255.0)
            ),
            nullptr
          ),
          Sequence::create(
            DelayTime::create(time),
            EaseSineOut::create(
              ScaleTo::create(0.2, 1.1)
            ),
            EaseSineIn::create(
              ScaleTo::create(0.5, 1.0)
            ),
            nullptr
          ),
          nullptr
        )
      );

      position.y += 1.6;

      /**
       *
       * @Store.Elements
       * | @3;
       *
       */
      for(auto state : this->states)
      {
        if(state.category == CATEGORY_MYTHICAL)
        {
          handler(state);
        }
      }
    }
   }

   /**
    *
    *
    *
    */
  auto size = max(Application->getHeight() - 300, Application->getHeight() - this->elements->last()->getPositionY() + 200);

   /**
    *
    *
    *
    */
  this->scroll->setInnerContainerSize(
    Size(
      Application->getWidth(),
      size
    )
  );

  /**
   *
   *
   *
   */
  for(auto element : this->scroll->getChildren())
  {
    element->setPositionY(element->getPositionY() - Application->getHeight() + size);
  }

  /**
   *
   *
   *
   */
  this->scroll->getInnerContainer()->setPosition(Vec2(0, Application->getHeight() - size - 300));

  /**
   *
   *
   *
   */
  Popup::onEnter();
}

void Store::onExit()
{
  Popup::onExit();

  /**
   *
   *
   *
   */
  Application->changeState(Game::STATE_MENU);
}

/**
 *
 *
 *
 */
void Store::onMenu()
{
  this->hide();
}

void Store::onShare()
{
}

void Store::onServices()
{
}

/**
 *
 *
 *
 */
void Store::show()
{
  Popup::show();
}

void Store::hide()
{
  Popup::hide();

  /**
   *
   *
   *
   */
  this->buttons.menu->remove();
  this->buttons.share->remove();
  this->buttons.services->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();

  /**
   *
   *
   *
   */
  for(auto element : this->scroll->getChildren())
  {
    element->runAction(
      Spawn::create(
        EaseSineIn::create(
          ScaleTo::create(0.5, 0.8)
        ),
        EaseSineIn::create(
          FadeTo::create(0.5, 0.0)
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
int Store::count(int category, bool create)
{
  auto count = 0;

  /**
   *
   *
   *
   */
  if(create)
  {
    CC_LOOP(this->elements)
    {
      auto element = (Store::Element*) this->elements->element(i);

      if(element->getCategory() == category)
      {
        count++;
      }
    }
  }
  else
  {
   for(auto element : this->states)
    {
      if(element.category== category)
      {
        count++;
      }
    }

    count -= this->count(category, true);
  }

  /**
   *
   *
   *
   */
  return count;
}

/**
 *
 *
 *
 */
void Store::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
  if(true)
  {
    this->texture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    this->scroll->getInnerContainer()->setVisible(true);
    this->scroll->getInnerContainer()->visit(renderer, parentTransform, parentFlags);
    this->texture->end();

    /**
     *
     *
     *
     */
    this->scroll->getInnerContainer()->setVisible(false);
  }

  /**
   *
   *
   *
   */
  Popup::visit(renderer, parentTransform, parentFlags);
}

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

Store::Element::Element()
: Button("ui/store-element-1.png", 2, 1, nullptr, [=] () {
})
{
  this->icon = new TiledEntity("ui/store-element-icon.png", 4, 1, this);
  this->icon->setPosition(this->getWidth() / 2, 12.0);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);

  /**
   *
   *
   *
   */
  this->bind(true, false);
}

Store::Element::~Element()
{
}

/**
 *
 *
 *
 */
void Store::Element::onCreate()
{
  Button::onCreate();

  /**
   *
   *
   *
   */
  this->setScale(0.8);
  this->setOpacity(0.0);
  this->setRotation(0.0);
}

void Store::Element::onDestroy(bool action)
{
  Button::onDestroy(action);
}

/**
 *
 *
 *
 */
void Store::Element::setState(int state)
{
  this->state = state;

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_LOCKED:
    this->setTexture("ui/store-element-1.png");
    break;
    case STATE_NORMAL:
    this->setTexture("ui/store-element-2.png");
    break;
  }

  /**
   *
   *
   *
   */
  this->updateTexturePoistion();

  /**
   *
   *
   *
   */
  this->icon->_destroy();
}

void Store::Element::setAction(int action)
{
  this->action = action;

  /**
   *
   *
   *
   */
  switch(this->action)
  {
    case ACTION_NORMAL:
    break;
    case ACTION_SELECTED:
    case ACTION_FACEBOOK:
    case ACTION_TWITTER:
    case ACTION_INSTAGRAM:
    this->icon->_create();
    this->icon->setCurrentFrameIndex(this->action - 1);
    break;
  }
}

void Store::Element::setIndex(int index)
{
  this->index = index;
}

void Store::Element::setPrice(float price)
{
  this->price = price;
}

void Store::Element::setCategory(int category)
{
  this->category = category;
}

/**
 *
 *
 *
 */
int Store::Element::getCategory()
{
  return this->category;
}

/**
 *
 *
 *
 */
Store::Element* Store::Element::deepCopy()
{
  return new Element;
}

/**
 *
 *
 *
 */
bool Store::Element::containsTouchLocation(cocos2d::Touch* touch)
{
  if(Node::containsTouchLocation(touch))
  {
    return (this->convertToWorldSpace(Vec2::ZERO).y > 300);
  }

  return false;
}
