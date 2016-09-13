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
  this->buttons.rate = new ExtendedButton("ui/button-rate.png", 2, 1, this, std::bind(&Store::onRate, this));
  this->buttons.menu = new ExtendedButton("ui/button-menu.png", 2, 1, this, std::bind(&Store::onMenu, this));
  this->buttons.share = new ExtendedButton("ui/button-share.png", 2, 1, this, std::bind(&Store::onShare, this));
  this->buttons.services = new ExtendedButton("ui/button-services.png", 2, 1, this, std::bind(&Store::onServices, this));
  this->buttons.next = new ExtendedButton("ui/button-next.png", 2, 1, this, std::bind(&Store::onNext, this));
  this->buttons.present = new PresentButton(this);
  this->buttons.video = new VideoButton(this);
  this->buttons.announce = new AnnounceButton(this, [=] () {
    Application->onShare(
      Application->getFrameWidth(),
      Application->getFrameWidth(),
      0,
      Application->getFrameHeight() / 2 - Application->getFrameWidth() / 2,
      false,
      this->texts.character->getString(),
      [=] (int state) {
        if(state)
        {
          Application->counter->currency.handler->add(50, this->buttons.announce);
        }
      }
    );
  });

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

  this->separator2->setCascadeOpacityEnabled(true);
  this->separator3->setCascadeOpacityEnabled(true);

  /**
   *
   *
   *
   */
  this->texts.more1 = new Text("@store.more", this->scroll);
  this->texts.more2 = new Text("@store.more", this->scroll);
  this->texts.connect = new Text("@store.connect", this->scroll);
  this->texts.character = new Text("@store.new.character", this->scroll);

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

      state = Storage::get("@store.states." + convert(index)) || state;

      this->states.push_back({
        index,
        category,
        state,
        action,
        price,
        false
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
  this->showButtons();

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
    auto update = [&] (int category) -> Vec2 {
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

        if(category == CATEGORY_MYTHICAL)
        {
          position.y += 0.2;
        }
      }

      return Vec2(Application->getCenter().x + (position.x - 2.5) * 160, Application->getHeight() - 200 - position.y * 160);
    };

    /**
     *
     * @Store.Elements
     * | @New Element;
     *
     */
    auto handler = [&] (State state) {
      state.state = state.update ? state.state : max(Storage::get("@store.states." + convert(state.index)), state.state);
      state.update = false;

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
        element->setIndex(state.index);
        element->setCategory(state.category);
        element->setState(state.state);
        element->setAction(state.action);
        element->setPrice(state.price);

        /**
         *
         *
         *
         */
        element->setPosition(update(state.category));

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
    CC_VOOP(this->states)
    {
      if(element.category == CATEGORY_REGULAR)
      {
        handler(element);

        /**
         *
         *
         *
         */
        if(this->elements->count == 4)
        {
          auto a = ((Element*) this->elements->element(1))->getState();
          auto b = ((Element*) this->elements->element(2))->getState();
          auto c = ((Element*) this->elements->element(3))->getState();

          if(!a || !b || !c) position.y += 0.1;
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
      CC_VOOP(this->states)
      {
        if(element.category == CATEGORY_RARE)
        {
          handler(element);
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
        this->texts.more2->data(this->count(CATEGORY_RARE));
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
      CC_VOOP(this->states)
      {
        if(element.category == CATEGORY_MYTHICAL)
        {
          handler(element);
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
  auto position = Application->getHeight() - size - 300;

  /**
   *
   *
   *
   */
  this->scroll->stopAutoScroll();
  this->scroll->setTouchEnabled(true);
  this->scroll->getInnerContainer()->setPosition(Vec2(0, position));

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
  CC_LOOP(this->elements)
  {
    auto element = (Element*) this->elements->element(i);

    /**
     *
     *
     *
     */
    if(element->getState() == Element::STATE_SELECTED)
    {
      auto p = max(position, position + (size - element->getPositionY() - Application->getHeight() / 2 + 150));

      /**
       *
       *
       *
       */
      this->scroll->getInnerContainer()->setPosition(Vec2(0, p));
    }
  }

  /**
   *
   *
   *
   */
  Application->environment->showElements({Environment::ELEMENT_NOTIFICATION_NODE});

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
  Application->onShare(
    Application->getFrameWidth(),
    Application->getFrameHeight(),
    0,
    0,
    false,
    "", // @TODO: Add share text;
    [=] (int a) {
    }
  );
}

void Store::onRate()
{
  Application->onRate();
}

void Store::onServices()
{
  Application->onLeaderboards();
}

void Store::onNext()
{
  this->buttons.announce->remove();
  this->buttons.next->remove();

  /**
   *
   *
   *
   */
  this->texts.character->runAction(
    Spawn::create(
      EaseSineIn::create(
        FadeTo::create(0.2, 0.0)
      ),
      EaseSineIn::create(
        ScaleTo::create(0.2, 0.8)
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->current->runAction(
    Spawn::create(
      EaseSineIn::create(
        FadeTo::create(0.2, 0.0)
      ),
      EaseSineIn::create(
        ScaleTo::create(0.2, 1.3)
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->separator2->runAction(
    Spawn::create(
      EaseSineIn::create(
        FadeTo::create(0.2, 0.0)
      ),
      EaseSineIn::create(
        ScaleTo::create(0.2, 0.8)
      ),
      nullptr
    )
  );
  this->separator3->runAction(
    Spawn::create(
      EaseSineIn::create(
        FadeTo::create(0.2, 0.0)
      ),
      EaseSineIn::create(
        ScaleTo::create(0.2, 0.8)
      ),
      nullptr
    )
  );

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      DelayTime::create(0.2),
      CallFunc::create([=] () {
      this->onEnter();
      }),
      nullptr
    )
  );
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
  this->hideButtons();

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

    element->bind(false);
  }
}

/**
 *
 *
 *
 */
void Store::showButtons()
{
  auto position = Vec2(Application->getCenter().x, 200.0);

  /**
   *
   *
   *
   */
  this->buttons.menu->add(position.x, position.y);
  this->buttons.rate->add(position.x - 128, position.y);
  this->buttons.share->add(position.x - 256, position.y);
  this->buttons.present->add(position.x + 256, position.y);

  /**
   *
   *
   *
   */
  if(Heyzap::available(AD_TYPE_VIDEO))
  {
    this->buttons.video->add(position.x + 128, position.y);
  }
  else
  {
    this->buttons.services->add(position.x + 128, position.y);
  }
}

void Store::hideButtons()
{
  this->buttons.menu->remove();
  this->buttons.share->remove();
  this->buttons.rate->remove();
  this->buttons.video->remove();
  this->buttons.present->remove();
  this->buttons.services->remove();
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
   CC_VOOP(this->states)
    {
      if(element.category == category && (element.state || element.action))
      {
        count++;
      }
    }
  }
  else
  {
   CC_VOOP(this->states)
    {
      if(element.category == category)
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
Store::State Store::element(bool action)
{
  if(Application->counter->values.currency.count < 1000)
  {
    return {
      0
    };
  }

  vector<State*> elements;

  /**
   *
   *
   *
   */
  CC_VOOP(this->states)
  {
    if(element.state == Element::STATE_LOCKED)
    {
      if(!element.action)
      {
        if(element.category == ((probably(10) || !this->count(CATEGORY_REGULAR)) ? CATEGORY_RARE : CATEGORY_REGULAR))
        {
          elements.push_back(&element);
        }
      }
    }
  }

  /**
   *
   *
   *
   */
  if(elements.size())
  {
    auto &element = CC_RANDOM(elements);

    /**
     *
     *
     *
     */
    if(action)
    {
      CC_VOOP(this->states)
      {
        if(element.state == Element::STATE_SELECTED)
        {
          element.state = Element::STATE_NORMAL;
          Storage::set(
            "@store.states." + convert(element.index),
            Element::STATE_NORMAL
          );
        }
      }

      element->state = Element::STATE_SELECTED;
      Storage::set(
        "@store.states." + convert(element->index),
        Element::STATE_SELECTED
      );
    }

    return *element;
  }
  else
  {
    return {
      0
    };
  }
}

/**
 *
 *
 *
 */
void Store::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
  if(Support::shaders(SHADER_COMPLEX))
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
: Button("ui/store-element-1.png", 2, 1, nullptr, std::bind(&Store::Element::onAction, this))
{
  this->currency = new Text("@store.element.currency", this);

  /**
   *
   *
   *
   */
  this->icon = new TiledEntity("ui/store-element-icon.png", 4, 1, this);
  this->icon->setPosition(this->getWidth() / 2, 12.0);
  this->icon->setLocalZOrder(2);

  /**
   *
   *
   *
   */
  this->texture = new Entity("characters/1001/texture.png", this);
  this->texture->setPosition(this->getWidth() / 2, this->getHeight() / 2);

  /**
   *
   *
   *
   */
  this->setCascadeOpacityEnabled(true);
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
  this->bind(true, false);

  /**
   *
   *
   *
   */
  this->setScale(0.8);
  this->setOpacity(0.0);
  this->setRotation3D(Vec3(0, 0, 0));
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
void Store::Element::onAction()
{
  Store::getInstance()->current = this;

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_NORMAL:
    this->setState(STATE_SELECTED);
    break;
    case STATE_SELECTED:
    this->bind(false);

    /**
     *
     *
     *
     */
    Store::getInstance()->hide();
    break;
  }

  /**
   *
   *
   *
   */
  switch(this->action)
  {
    case ACTION_FACEBOOK:
    case ACTION_TWITTER:
    case ACTION_INSTAGRAM:
    case ACTION_INAPP:
    switch(this->state)
    {
      case STATE_NORMAL:
      break;
      case STATE_LOCKED:
      CC_VOOP(Store::getInstance()->scroll->getChildren())
      {
        if(element != this)
        {
          auto v = Vec2(0, 0);

          v.x = element->getPositionX() - this->getPositionX();
          v.y = element->getPositionY() - this->getPositionY();

          v.normalize();

          /**
           *
           *
           *
           */
          element->runAction(
            Spawn::create(
              EaseSineIn::create(
                MoveBy::create(0.2, v * 50)
              ),
              EaseSineIn::create(
                ScaleTo::create(0.2, 1.1)
              ),
              EaseSineIn::create(
                FadeTo::create(0.2, 0.0)
              ),
              nullptr
            )
          );
        }

        /**
         *
         *
         *
         */
        Store::getInstance()->scroll->setTouchEnabled(false);
        Store::getInstance()->scroll->getInnerContainer()->stopAllActions();

        /**
         *
         *
         *
         */
        element->bind(false);
      }

      /**
       *
       *
       *
       */
      this->runAction(
        Spawn::create(
          EaseSineIn::create(
            FadeTo::create(0.2, 0.0)
          ),
          Sequence::create(
            EaseSineIn::create(
              ScaleTo::create(0.2, 0.8)
            ),
            CallFunc::create([=] () {
              Store::getInstance()->scroll->getInnerContainer()->setPositionY(-(Store::getInstance()->scroll->getInnerContainer()->getContentSize().height - Application->getHeight()) - 300);

              /**
               *
               *
               *
               */
              auto position = Vec2(Application->getCenter().x, Store::getInstance()->scroll->getInnerContainer()->getContentSize().height - Application->getHeight() / 2 - 35);

              /**
               *
               *
               *
               */
              this->setPosition(position);

              /**
               *
               *
               *
               */
              Store::getInstance()->texts.connect->_create();
              Store::getInstance()->texts.connect->setCameraMask(BACKGROUND);
              Store::getInstance()->texts.connect->setScale(0.8);
              Store::getInstance()->texts.connect->setOpacity(0.0);
              Store::getInstance()->texts.connect->setText("@store.connect." + convert(this->action));
              Store::getInstance()->texts.connect->setPosition(position.x, position.y - 180);
              Store::getInstance()->texts.connect->runAction(
                Spawn::create(
                  EaseSineOut::create(
                    FadeTo::create(0.2, 255.0)
                  ),
                  EaseSineOut::create(
                    ScaleTo::create(0.2, 1.0)
                  ),
                  nullptr
                )
              );

              /**
               *
               *
               *
               */
              this->runAction(
                Spawn::create(
                  EaseSineOut::create(
                    ScaleTo::create(0.2, 1.5)
                  ),
                  EaseSineOut::create(
                    FadeTo::create(0.2, 255.0)
                  ),
                  Sequence::create(
                    EaseSineOut::create(
                      RotateTo::create(2.0, Vec3(0.0, 360.0 * 5, 0.0))
                    ),
                    DelayTime::create(0.5),
                    CallFunc::create([=] () {
                      auto callback = [&] (bool state) {
                        if(state)
                        {
                          /**
                           *
                           * @Action
                           * |@Action successful;
                           *
                           */
                          Application->environment->clear->runAction(
                            Sequence::create(
                              DelayTime::create(0.5),
                              FadeTo::create(0.1, 255.0),
                              CallFunc::create([=] () {
                                Application->environment->showElements({Environment::ELEMENT_NOTIFICATION_NODE});

                                /**
                                 *
                                 *
                                 *
                                 */
                                this->setState(STATE_SELECTED);

                                /**
                                 *
                                 *
                                 *
                                 */
                                this->currency->_destroy();
                                this->icon->_destroy();

                                /**
                                 *
                                 *
                                 *
                                 */
                                Store::getInstance()->texts.connect->_destroy();

                                /**
                                 *
                                 *
                                 *
                                 */
                                Store::getInstance()->texts.character->_create();
                                Store::getInstance()->texts.character->setText("@store.new.character." + convert(random(1, 2)));
                                Store::getInstance()->texts.character->setCameraMask(BACKGROUND);
                                Store::getInstance()->texts.character->setScale(1.0);
                                Store::getInstance()->texts.character->setScaleX(0.9);
                                Store::getInstance()->texts.character->setOpacity(255.0);
                                Store::getInstance()->texts.character->setPosition(this->getPositionX(), this->getPositionY() + 160);

                                /**
                                 *
                                 *
                                 *
                                 */
                                Store::getInstance()->buttons.announce->add(Application->getCenter().x - 64, 200);
                                Store::getInstance()->buttons.next->add(Application->getCenter().x + 64, 200);

                                /**
                                 *
                                 *
                                 *
                                 */
                                Entity* separator = nullptr;

                                /**
                                 *
                                 *
                                 *
                                 */
                                switch(this->getCategory())
                                {
                                  case CATEGORY_REGULAR:
                                  break;
                                  case CATEGORY_RARE:
                                  separator = Store::getInstance()->separator2;
                                  break;
                                  case CATEGORY_MYTHICAL:
                                  separator = Store::getInstance()->separator3;
                                  break;
                                }

                                /**
                                 *
                                 *
                                 *
                                 */
                                if(separator)
                                {
                                  separator->setPosition(position.x, position.y + 100);
                                  separator->setScale(0.8);
                                  separator->setOpacity(0.0);
                                  separator->runAction(
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

                                  this->runAction(
                                    EaseSineOut::create(
                                      MoveBy::create(0.5, Vec2(0.0, -30.0))
                                    )
                                  );
                                }
                              }),
                              DelayTime::create(0.1),
                              FadeTo::create(0.3, 0.0),
                              nullptr
                            )
                          );
                        }
                        else
                        {
                          /**
                           *
                           * @Action
                           * |@Action failed;
                           *
                           */
                          Store::getInstance()->texts.connect->runAction(
                            Spawn::create(
                              EaseSineIn::create(
                                FadeTo::create(0.2, 0.0)
                              ),
                              EaseSineIn::create(
                                ScaleTo::create(0.2, 0.8)
                              ),
                              nullptr
                            )
                          );

                          /**
                           *
                           *
                           *
                           */
                          this->runAction(
                            Spawn::create(
                              EaseSineIn::create(
                                FadeTo::create(0.2, 0.0)
                              ),
                              Sequence::create(
                                EaseSineIn::create(
                                  ScaleTo::create(0.2, 1.2)
                                ),
                                CallFunc::create([=] () {
                                Store::getInstance()->onEnter();
                                }),
                                nullptr
                              ),
                              nullptr
                            )
                          );
                        }
                      };

                      /**
                       *
                       *
                       *
                       */
                      switch(this->action)
                      {
                        case ACTION_TWITTER:
                        Application->onTwitterLike();
                        break;
                        case ACTION_FACEBOOK:
                        Application->onFacebookLike();
                        break;
                        case ACTION_INSTAGRAM:
                        Application->onInstagramLike();
                        break;
                        case ACTION_INAPP:
                        //Purchase::purchaseItem("com", callback);
                        callback(true);
                        break;
                      }

                      /**
                       *
                       *
                       *
                       */
                      switch(this->action)
                      {
                        case ACTION_TWITTER:
                        case ACTION_FACEBOOK:
                        case ACTION_INSTAGRAM:
                        callback(true);
                        case ACTION_INAPP:
                        break;
                      }
                    }),
                    nullptr
                  ),
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
      Application->environment->hideElements({Environment::ELEMENT_NOTIFICATION_NODE});

      /**
       *
       *
       *
       */
      Store::getInstance()->hideButtons();
      break;
    }
    break;
  }
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
  Storage::set("@store.states." + convert(this->index), this->state);

  /**
   *
   *
   *
   */
  this->texture->stopAllActions();

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_SELECTED:
    this->setAction(ACTION_NONE);

    /**
     *
     *
     *
     */
    for(auto &element : Store::getInstance()->states)
    {
      if(element.index == this->index)
      {
        element.state = STATE_SELECTED;
        element.update = false;
      }

      if(element.state == STATE_SELECTED)
      {
        if(element.index != this->index)
        {
          element.state = STATE_NORMAL;
          element.update = true;
        }
      }
    }

    /**
     *
     *
     *
     */
    CC_LOOP(Store::getInstance()->elements)
    {
      auto element = (Store::Element*) Store::getInstance()->elements->element(i);

      if(element->index != this->index)
      {
        if(element->state == STATE_SELECTED)
        {
          element->setState(STATE_NORMAL);
        }
      }
    }

    this->setTexture("ui/store-element-3.png");
    break;
    case STATE_NORMAL:
    this->setTexture("ui/store-element-2.png");
    break;
    case STATE_LOCKED:
    this->setTexture("ui/store-element-1.png");
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
  switch(this->state)
  {
    case STATE_SELECTED:
    this->texture->runAction(
      RepeatForever::create(
        RotateBy::create(20.0, 360)
      )
    );
    case STATE_NORMAL:
    this->texture->setTexture("characters/" + convert(this->getIndex()) + "/texture.png");
    this->texture->_create();
    break;
    case STATE_LOCKED:
    break;
  }

  switch(this->state)
  {
    case STATE_SELECTED:
    this->texture->setLocalZOrder(1);
    break;
    case STATE_NORMAL:
    this->texture->setLocalZOrder(-1);
    break;
    case STATE_LOCKED:
    break;
  }

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_SELECTED:
    this->currency->_destroy();
    break;
    case STATE_NORMAL:
    this->currency->_destroy();
    this->icon->_destroy();
    break;
    case STATE_LOCKED:
    if(this->category == CATEGORY_MYTHICAL)
    {
      this->currency->_create();
      this->currency->data(convert(1.99), "USD");
      this->currency->setCameraMask(BACKGROUND);
      this->currency->setPosition(this->getWidth() / 2, -10);
    }
    break;
  }
}

void Store::Element::setAction(int action)
{
  this->action = action;

  /**
   *
   *
   *
   */
  this->icon->_destroy();

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_NORMAL:
    break;

    case STATE_SELECTED:
    this->icon->_create();
    this->icon->setCameraMask(BACKGROUND);
    this->icon->setCurrentFrameIndex(0);
    this->icon->setScale(0.8);
    this->icon->setOpacity(0.0);
    this->icon->runAction(
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
    break;

    case STATE_LOCKED:
    switch(this->action)
    {
      case ACTION_INAPP:
      // TODO: Price?
      break;
      case ACTION_FACEBOOK:
      case ACTION_TWITTER:
      case ACTION_INSTAGRAM:
      this->icon->_create();
      this->icon->setCurrentFrameIndex(this->action);
      break;
    }
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
int Store::Element::getIndex()
{
  return this->index;
}

int Store::Element::getState()
{
  return this->state;
}

int Store::Element::getAction()
{
  return this->action;
}

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
