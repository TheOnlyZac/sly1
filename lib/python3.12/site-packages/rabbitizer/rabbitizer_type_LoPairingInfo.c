/* SPDX-FileCopyrightText: © 2022-2024 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "rabbitizer_module.h"


static void rabbitizer_type_LoPairingInfo_dealloc(PyRabbitizerLoPairingInfo *self) {
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static int rabbitizer_type_LoPairingInfo_init(PyRabbitizerLoPairingInfo *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist)) {
        return -1;
    }

    RabbitizerLoPairingInfo_Init(&self->pairingInfo);

    return 0;
}


static PyMemberDef rabbitizer_type_LoPairingInfo_members[] = {
    { "shouldProcess", T_BOOL, offsetof(PyRabbitizerLoPairingInfo, pairingInfo.shouldProcess), 0, "" },
    { "isGpRel", T_BOOL, offsetof(PyRabbitizerLoPairingInfo, pairingInfo.isGpRel), 0, "" },
    { "isGpGot", T_BOOL, offsetof(PyRabbitizerLoPairingInfo, pairingInfo.isGpGot), 0, "" },

    { 0 }
};


#define DEF_MEMBER_GET_INT32(name) \
    static PyObject *rabbitizer_type_LoPairingInfo_member_get_##name(PyRabbitizerLoPairingInfo *self, UNUSED PyObject *closure) { \
        return PyLong_FromLong(self->pairingInfo.name); \
    }

#define DEF_MEMBER_GET_INT64(name) \
    static PyObject *rabbitizer_type_LoPairingInfo_member_get_##name(PyRabbitizerLoPairingInfo *self, UNUSED PyObject *closure) { \
        return PyLong_FromLongLong(self->pairingInfo.name); \
    }

DEF_MEMBER_GET_INT32(instrOffset)
DEF_MEMBER_GET_INT64(value)


#define MEMBER_GET(name, docs)      { #name, (getter) rabbitizer_type_LoPairingInfo_member_get_##name, (setter) NULL,                                            PyDoc_STR(docs), NULL }
#define MEMBER_SET(name, docs)      { #name, (getter) NULL,                                            (setter) rabbitizer_type_LoPairingInfo_member_set_##name, PyDoc_STR(docs), NULL }
#define MEMBER_GET_SET(name, docs)  { #name, (getter) rabbitizer_type_LoPairingInfo_member_get_##name, (setter) rabbitizer_type_LoPairingInfo_member_set_##name, PyDoc_STR(docs), NULL }

static PyGetSetDef rabbitizer_type_LoPairingInfo_getsetters[] = {
    MEMBER_GET(instrOffset, ""),
    MEMBER_GET(value, ""),

    { 0 }
};


DEF_RAB_TYPE(LoPairingInfo)


PyTypeObject rabbitizer_type_LoPairingInfo_TypeObject = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "rabbitizer.LoPairingInfo",
    .tp_doc = PyDoc_STR("LoPairingInfo"),
    .tp_basicsize = sizeof(PyRabbitizerLoPairingInfo),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc) rabbitizer_type_LoPairingInfo_init,
    .tp_dealloc = (destructor) rabbitizer_type_LoPairingInfo_dealloc,
    // .tp_repr = (reprfunc) rabbitizer_type_LoPairingInfo_repr,
    // .tp_str = (reprfunc) rabbitizer_type_LoPairingInfo_str,
    .tp_members = rabbitizer_type_LoPairingInfo_members,
    // .tp_methods = rabbitizer_type_Instr_methods,
    .tp_getset = rabbitizer_type_LoPairingInfo_getsetters,
};
