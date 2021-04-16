#pragma once

#include "chain.h"

namespace CRTPMix {
  ////////////////////////////////////////////////////////////////////////////////
  //implement CRTP
  // allow open chain derivation to pack components as unifyed object
  template<typename T>
  struct Obj {
    using Type=T;
    inline Type& obj() {return *(Type*)this;}
  };

  ////////////////////////////////////////////////////////////////////////////////
  // generalize composition with CRTP available by:
  // `Type` get packed top type
  // `obj()` get the top packed object
  template<template<typename> class API,template<typename> class... I>
  struct Composition:Chain<I...,API>::template To<Obj<Composition<API,I...>>> {
    using Base=typename Chain<I...,API>::template To<Obj<Composition<API,I...>>>;
    using This=Composition<API,I...>;
    using Base::Base;
    template<typename... OO>
    Composition(OO... oo):Base(oo...) {}
  };

};