#pragma once

enum
{
	//1->db 2->cs 3->ms 
	//1-200 为client预留的moduleID，server内部的从200开始
    MODULE_TYPE_CLIENT      = 1,
	MODULE_TYPE_CLIENT2     = 2,
	MODULE_TYPE_CLIENT3     = 3,
    MODULE_TYPE_CLIENT7     = 7,
	MODULE_TYPE_SS          = 200,
	MODULE_TYPE_DB,
	MODULE_TYPE_MS,
	MODULE_TYPE_LS,
	MODULE_TYPE_CS,
	MODULE_TYPE_GS,
	MODULE_TYPE_LOG,
};

using EnCodeFunc = int (*)(void* pHost, CNetData* poNetData);
using DeCodeFunc = int (*)(void* pHost, CNetData* poNetData);





#define BEGIN_ENCODE(cls) cls *pstIn = (cls*)pHost
#define ENCODE_BYTE(member) if (-1 == poNetData->AddByte(pstIn->member)) return -1
#define ENCODE_CHAR(member) if (-1 == poNetData->AddChar(pstIn->member)) return -1
#define ENCODE_WORD(member) if (-1 == poNetData->AddWord(pstIn->member)) return -1
#define ENCODE_SHORT(member) if (-1 == poNetData->AddShort(pstIn->member)) return -1
#define ENCODE_DWORD(member) if (-1 == poNetData->AddDword(pstIn->member)) return -1
#define ENCODE_INT(member) if (-1 == poNetData->AddInt(pstIn->member)) return -1
#define ENCODE_INT64(member) if (-1 == poNetData->AddInt64(pstIn->member)) return -1
#define ENCODE_QWORD(member) if (-1 == poNetData->AddQword(pstIn->member)) return -1
#define ENCODE_STRING(member) if (-1 == poNetData->AddString(pstIn->member, _countof(pstIn->member))) return -1
#define ENCODE_FIXSTRING(member, len) if (-1 == poNetData->AddFixString(pstIn->member, pstIn->len)) return -1
#define ENCODE_BLOB(member, size) if (-1 == poNetData->AddBlob((char *)pstIn->member, size)) return -1
//#define ENCODE_INTARRAY(member) if (-1 == poNetData->AddIntArray((pstIn->member, )) return -1
//int size = _countof(pstIn->member)
#define ENCODE_INTARRAY(member,size) \
for (int i = 0; i < size; i++) {\
		 if (-1 == poNetData->AddDword(pstIn->member[i])) \
return -1;\
}

#define ENCODECUSTOM_INFO(member)\
	if (-1 == EnCodeCUSTOM_INFO(&pstIn->member, poNetData))\
return -1;


#define ENCODEBUFF_INFO(member,num,size)\
for (int i = 0; i < size; i++) {\
if (i >= (int)pstIn->num)\
break; \
	if (-1 == EnCodeBUFF_INFO(&pstIn->member[i], poNetData))\
		return -1;\
}
	

#define END_ENCODE() return poNetData->GetDataLen()
#define ENCODE_CHECK_UPBOUND(num, buf) if (pstIn->num > _countof(pstIn->buf)) return -1;

#define BEGIN_DECODE(cls) cls *pstOut = (cls*)pHost
#define DECODE_BYTE(member) if (-1 == poNetData->DelByte(pstOut->member)) return -1
#define DECODE_CHAR(member) if (-1 == poNetData->DelChar(pstOut->member)) return -1
#define DECODE_WORD(member) if (-1 == poNetData->DelWord(pstOut->member)) return -1
#define DECODE_SHORT(member) if (-1 == poNetData->DelShort(pstOut->member)) return -1
#define DECODE_DWORD(member) if (-1 == poNetData->DelDword(pstOut->member)) return -1
#define DECODE_INT(member) if (-1 == poNetData->DelInt(pstOut->member)) return -1
#define DECODE_INT64(member) if (-1 == poNetData->DelInt64(pstOut->member)) return -1
#define DECODE_QWORD(member) if (-1 == poNetData->DelQword(pstOut->member)) return -1
#define DECODE_STRING(member) if (-1 == poNetData->DelString(pstOut->member, _countof(pstOut->member))) return -1
#define DECODE_FIXSTRING(member) DECODE_STRING(member)
#define DECODE_BLOB(member, size) if (-1 == poNetData->DelBlob((char *)pstOut->member, size)) return -1
//#define DECODE_INTARRAY(member, size) if (-1 == poNetData->AddIntArray((int *)pstOut->member, size)) return -1

#define DECODE_INTARRAY(member,size) \
for (unsigned int i = 0; i < size; i++) {\
		 if (-1 == poNetData->DelDword(pstOut->member[i])) \
return -1;\
}

#define DECODECUSTOM_INFO(member)\
	if (-1 == DeCodeCUSTOM_INFO(&pstOut->member, poNetData))\
return -1;

#define DECODEBUFF_INFO(member,num,size)\
for (int i = 0; i < size; i++) {\
	if (i >= (int)pstOut->num)\
		break; \
	if (-1 == DeCodeBUFF_INFO(&pstOut->member[i], poNetData))\
		return -1;\
}

#define END_DECODE() return sizeof(*pstOut)
#define DECODE_CHECK_UPBOUND(num, buf) if (pstOut->num > _countof(pstOut->buf)) return -1;

#define ENCODE_HEAD() ENCODE_WORD(moduleid); ENCODE_WORD(protocolid)
#define ENCODE_HEAD_GS() ENCODE_HEAD(); ENCODE_DWORD(sessionid); ENCODE_DWORD(token); ENCODE_QWORD(playerid)

#define DECODE_HEAD() DECODE_WORD(moduleid); DECODE_WORD(protocolid)
#define DECODE_HEAD_GS() DECODE_HEAD(); DECODE_DWORD(sessionid); DECODE_DWORD(token); DECODE_QWORD(playerid)

#define BEGIN_ENCODE_EX(cls) BEGIN_ENCODE(cls); ENCODE_HEAD()
#define BEGIN_ENCODE_GS(cls) BEGIN_ENCODE(cls); ENCODE_HEAD_GS()

#define BEGIN_DECODE_EX(cls) BEGIN_DECODE(cls); DECODE_HEAD()
#define BEGIN_DECODE_GS(cls) BEGIN_DECODE(cls); DECODE_HEAD_GS()

#define SET_ENCODER_DECODER(protoid, encoder, decoder) m_EnCodeFuncArray[protoid] = encoder; m_DeCodeFuncArray[protoid] = decoder

#define ASSIGN_MEMBER(m) data.m = msg->m
#define ASSIGN_STRING_MEMBER(m) strcpy_s(data.m, _countof(data.m), msg->m)
#define ASSIGN_ARRAY_MEMEBER(m) memcpy_s(data.m, sizeof(data.m), msg->m, sizeof(msg->m))
#define ASSIGN_STRUCT_MEMBER(m) memcpy_s(&data.m, sizeof(data.m), &msg->m, sizeof(msg->m))


inline int EncodeNotImpl(void* pHost, CNetData* poNetData)
{
    return -1;
}

inline int DecodeNotImpl(void* pHost, CNetData* poNetData)
{
    return -1;
}

struct Proto_General
{
    uint16_t    moduleid;
    uint16_t    protocolid;
    void*       data;
};
