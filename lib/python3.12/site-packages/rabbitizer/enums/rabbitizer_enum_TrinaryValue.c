/* SPDX-FileCopyrightText: © 2023-2024 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "enums_utils.h"
#include "common/Utils.h"

#define RAB_DEF_TRINARYVALUE(name) { "TrinaryValue", #name , RAB_TRINARY_VAL_##name, false, NULL },

RabbitizerEnumMetadata rabbitizer_enum_TrinaryValue_enumvalues[] = {
    RAB_DEF_TRINARYVALUE(NONE)
    RAB_DEF_TRINARYVALUE(FALSE)
    RAB_DEF_TRINARYVALUE(TRUE)

    { 0 },
};

#undef RAB_DEF_TRINARYVALUE


static PyMethodDef rabbitizer_enum_TrinaryValue_methods[] = {
    { 0 },
};

DEF_ENUM(TrinaryValue, "")
