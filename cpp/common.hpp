#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#include <vector>

#include <btVector3.h>
#include <btQuaternion.h>
#include <btAlignedObjectArray.h>

#include <event-emitter.hpp>


// Bullet stuff

#define VEC3_TO_OBJ(VEC3, NAME)                                               \
	Local<Array> NAME = Nan::New<Array>(3);                                   \
	SET_I(NAME, 0, JS_NUM(VEC3.getX()));                                      \
	SET_I(NAME, 1, JS_NUM(VEC3.getY()));                                      \
	SET_I(NAME, 2, JS_NUM(VEC3.getZ()));                                      \
	SET_PROP(NAME, "x", JS_NUM(VEC3.getX()));                                 \
	SET_PROP(NAME, "y", JS_NUM(VEC3.getY()));                                 \
	SET_PROP(NAME, "z", JS_NUM(VEC3.getZ()));

#define QUAT_TO_OBJ(QUAT, NAME)                                               \
	Local<Array> NAME = Nan::New<Array>(4);                                   \
	SET_I(NAME, 0, JS_NUM(QUAT.getX()));                                      \
	SET_I(NAME, 1, JS_NUM(QUAT.getY()));                                      \
	SET_I(NAME, 2, JS_NUM(QUAT.getZ()));                                      \
	SET_I(NAME, 3, JS_NUM(QUAT.getW()));                                      \
	SET_PROP(NAME, "x", JS_NUM(QUAT.getX()));                                 \
	SET_PROP(NAME, "y", JS_NUM(QUAT.getY()));                                 \
	SET_PROP(NAME, "z", JS_NUM(QUAT.getZ()));                                 \
	SET_PROP(NAME, "w", JS_NUM(QUAT.getW()));

#define OBJ_TO_VEC3(OBJ, NAME)                                                \
	btVector3 NAME;                                                           \
	if (OBJ->Has(Nan::GetCurrentContext(), JS_STR("x")).ToChecked()) {        \
		NAME.setX(Nan::To<double>(OBJ->Get(JS_STR("x"))).FromJust());         \
		NAME.setY(Nan::To<double>(OBJ->Get(JS_STR("y"))).FromJust());         \
		NAME.setZ(Nan::To<double>(OBJ->Get(JS_STR("z"))).FromJust());         \
	} else {                                                                  \
		NAME.setX(Nan::To<double>(OBJ->Get(0)).FromJust());                   \
		NAME.setY(Nan::To<double>(OBJ->Get(1)).FromJust());                   \
		NAME.setZ(Nan::To<double>(OBJ->Get(2)).FromJust());                   \
	}

#define OBJ_TO_QUAT(OBJ, NAME)                                                \
	btQuaternion NAME;                                                        \
	if (OBJ->Has(Nan::GetCurrentContext(), JS_STR("x")).ToChecked()) {        \
		NAME.setX(Nan::To<double>(OBJ->Get(JS_STR("x"))).FromJust());         \
		NAME.setY(Nan::To<double>(OBJ->Get(JS_STR("y"))).FromJust());         \
		NAME.setZ(Nan::To<double>(OBJ->Get(JS_STR("z"))).FromJust());         \
		NAME.setW(Nan::To<double>(OBJ->Get(JS_STR("w"))).FromJust());         \
	} else {                                                                  \
		NAME.setX(Nan::To<double>(OBJ->Get(0)).FromJust());                   \
		NAME.setY(Nan::To<double>(OBJ->Get(1)).FromJust());                   \
		NAME.setZ(Nan::To<double>(OBJ->Get(2)).FromJust());                   \
		NAME.setW(Nan::To<double>(OBJ->Get(3)).FromJust());                   \
	}


#define REQ_VEC3_ARG(I, VAR)                                                  \
	REQ_OBJ_ARG(I, _obj_##VAR);                                               \
	OBJ_TO_VEC3(_obj_##VAR, VAR);

#define REQ_QUAT_ARG(I, VAR)                                                  \
	REQ_OBJ_ARG(I, _obj_##VAR);                                               \
	OBJ_TO_QUAT(_obj_##VAR, VAR);


#define SETTER_VEC3_ARG                                                       \
	SETTER_CHECK(IsObject(), "object");                                       \
	Local<Object> _obj_v = Local<Object>::Cast(value);                        \
	OBJ_TO_VEC3(_obj_v, v);

#define SETTER_QUAT_ARG                                                       \
	SETTER_CHECK(IsObject(), "object");                                       \
	Local<Object> _obj_v = Local<Object>::Cast(value);                        \
	OBJ_TO_QUAT(_obj_v, v);


#define ALIGNED_NEW(C, ...) new (btAlignedAlloc(sizeof(C), 16)) C(__VA_ARGS__)


#define ALIGNED_DELETE(C, V)                                                  \
	if (V) {                                                                  \
		static_cast<C*>(V)->~C();                                             \
		btAlignedFree(V);                                                     \
		V = nullptr;                                                          \
	}


#define EACH(V) for (int i = V.size() - 1; i >= 0; i--)


// Fix bad defines

#undef True
#undef False


#endif /* _COMMON_HPP_ */
