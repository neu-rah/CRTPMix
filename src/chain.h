#pragma once

//chain open derivation types (mixins)
//this helper cleans up code
// transforming a clean list of templates into a nested derivation template
// write this: A<B,C,D>
// get this: A<B<C<D>>>::To
// resulting type is still open for further extension
// close it by provifing a type X, ie: `...::To<X>`

namespace CRTPMix {
  
  //Chain template<template>...
  //implements partially applyed mixins
  //this is an open chain derivation/inheritance
  //the mixins chains can be combined with others or built upon, 
  //until a terminal is added, turning it into a simple type
  //further this is combined with a CRTP as a terminal,
  //providing an encapsulation to the mixin.
  template<template<typename> class... OO>
  #define Expr template<typename> class
  #define Term typename
  struct Chain {
    template<typename _T,template<typename> class _O, template<typename> class... _OO>
    struct Links:_O<Links<_T,_OO...>> {using _O<Links<_T,_OO...>>::_O;};

    template<typename _T,template<typename> class _O>
    struct Links<_T,_O>: _O<_T> {using _O<_T>::_O;};

    template<typename T>
    struct To:Links<T,OO...> {
      using Links<T,OO...>::Links;
    };
    template<typename T>
    using Part=To<T>;
    //provide a continuation
    template<template<typename> class... _O>
    using With=Chain<OO...,_O...>;
  };
};
