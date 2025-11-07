#pragma once

#include <stdint.h>

#define VFT_UNKNOWN_SLOTS(n, x) uint32_t unknown_slots_##x[n * 3]

#define _VFT_FORWARD__CALL_ARGS(...) (this __VA_OPT__(, ) __VA_ARGS__)

#define VFT_FORWARD(name, ret, params, args)                                   \
  inline ret name params { return vft()->name _VFT_FORWARD__CALL_ARGS args; }

#define VFT_FORWARD_TO(name, to, ret, params, args)                            \
  inline ret name params { return vft()->to _VFT_FORWARD__CALL_ARGS args; }

#define _VFT_REGISTER__FUNC_PARAMS(...) (void *self __VA_OPT__(, ) __VA_ARGS__)

#define VFT_REGISTER(type, method, params, args)                               \
  vftNew()->method.func = [] _VFT_REGISTER__FUNC_PARAMS params {               \
    return static_cast<type *>(static_cast<type##_Thin *>(self)->vft()->owner) \
        ->method args;                                                         \
  }

#define VFT_REGISTER_TO(type, method, to, params, args)                        \
  vftNew()->to.func = [] _VFT_REGISTER__FUNC_PARAMS params {                   \
    return static_cast<type *>(static_cast<type##_Thin *>(self)->vft()->owner) \
        ->method args;                                                         \
  }

#define _VFT_VIRTUAL__CALL_ARGS(...) (obj() __VA_OPT__(, ) __VA_ARGS__)

#define VFT_VIRTUAL(type, method, ret, params, args)                           \
  ret type::method params {                                                    \
    return vftOld()->method _VFT_VIRTUAL__CALL_ARGS args;                      \
  }

#define VFT_VIRTUAL_TO(type, method, to, ret, params, args)                    \
  ret type::method params { return vftOld()->to _VFT_VIRTUAL__CALL_ARGS args; }

// Dummy paramater to fix the signature
typedef int DUMMY;

template <typename TReturn, typename... TArgs> struct VFTableFunction {
  int32_t offset;
  uint32_t unused;
  TReturn (*func)(void *self, TArgs...);

  inline TReturn operator()(void *self, TArgs... args) {
    void *self2 =
        reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(self) + offset);

    return func(self2, args...);
  }
};

struct Element_VFTable {
  Element_VFTable() = delete; // delete default constructor
  Element_VFTable(const Element_VFTable &) = delete; // delete copy constructor
  Element_VFTable(Element_VFTable &&) = delete;      // delete move constructor

  // TODO: Check if it is safe to use the free space.
  // If not, we could save the owner at -4
  void *owner;
  uint32_t _pad[2];
};

class Element_Thin {
  Element_Thin() = delete;                     // delete default constructor
  Element_Thin(const Element_Thin &) = delete; // delete copy constructor
  Element_Thin(Element_Thin &&) = delete;      // delete move constructor
};

class Wrapper {
protected:
  Wrapper(void *obj) { _obj = obj; }
  ~Wrapper() = default;

  Wrapper(Wrapper const &) = delete;
  void operator=(Wrapper const &) = delete;

  void *_obj;
};

class Element : public Wrapper {
public:
  Element(void *obj) : Wrapper(obj) {}

protected:
  void *_vftNew;
  void *_vftOld;
};
