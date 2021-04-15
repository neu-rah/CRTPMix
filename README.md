# CRTPMix
C++ CRTP with Mixins

## Mixins

Open derivation templates, allowing further composition.

mixins are great to combine functionality (composition), but they lack an encapsulation.

CRTP can provide that.

## CRTP

Allow composition to act as a block (encapsulation)

## Example

Mixins
```c++
class API{/*...*/};

template<typename O=API>
class ConstText {/**/};

template<typename O=API>
class FlashText:O {
  using Base=O;
  /*...*/
};

template<typename O>
class Text:O {
  using Base=O;
  /*...*/
};

//composing the parts
using MyText=Text<FlashText<API>>;

//or using Chain
using MyText=Chain<Text,FlashText>::To<API>;

//or enclose the composition
//(so that API can use final composition members)
using MyText=Composition<API,Text,FlashText>;

/*we can then replace FlashText with ConstText according to platform, or compose any extra functionality defined in future.
ex: we could create an Upcase part...
*/
```

`Chain` template helps making the mixin composition easier to write.

`Composition` defined on top of `Chain` to provide an encapsulation and a terminating API

Any composition part can then use:

`Base::Type` to obtain the encapsulation type

`Base::obj()` to obtain the encapsulation object


