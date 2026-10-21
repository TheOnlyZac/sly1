/**
 * @file splice/serialize.h
 */
#ifndef SPLICE_SERIALIZE_H
#define SPLICE_SERIALIZE_H

#include <common.h>
#include <bis.h>
#include <splice/pair.h>

CPair *PpairSerializeIn(CBinaryInputStream *pstrm);

#endif // SPLICE_SERIALIZE_H
