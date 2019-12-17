/*
* Copyright (c) 2005-2018, BearWare.dk
*
* Contact Information:
*
* Bjoern D. Rasmussen
* Kirketoften 5
* DK-8260 Viby J
* Denmark
* Email: contact@bearware.dk
* Phone: +45 20 20 54 59
* Web: http://www.bearware.dk
*
* This source code is part of the TeamTalk SDK owned by
* BearWare.dk. Use of this file, or its compiled unit, requires a
* TeamTalk SDK License Key issued by BearWare.dk.
*
* The TeamTalk SDK License Agreement along with its Terms and
* Conditions are outlined in the file License.txt included with the
* TeamTalk SDK distribution.
*
*/

#if !defined(TTUNITTEST_H)
#define TTUNITTEST_H

#include <TeamTalk.h>

#include <functional>

#define DEFWAIT 5000

bool InitSound(TTInstance* ttClient, TTBOOL duplex = false, INT32 indev = -1, INT32 outdev = -1);
bool Connect(TTInstance* ttClient, const TTCHAR hostname[TT_STRLEN], INT32 tcpport, INT32 udpport);
bool Login(TTInstance* ttClient, const TTCHAR nickname[TT_STRLEN], const TTCHAR username[TT_STRLEN], const TTCHAR passwd[TT_STRLEN]);
bool JoinRoot(TTInstance* ttClient);
bool WaitForEvent(TTInstance* ttClient, ClientEvent ttevent, std::function<bool(TTMessage)> pred, TTMessage* outmsg, int timeout = DEFWAIT);
bool WaitForEvent(TTInstance* ttClient, ClientEvent ttevent, TTMessage* outmsg = nullptr, int timeout = DEFWAIT);
bool WaitForCmdSuccess(TTInstance* ttClient, int cmdid, TTMessage* outmsg = nullptr, int timeout = DEFWAIT);
bool WaitForCmdComplete(TTInstance* ttClient, int cmdid, TTMessage* outmsg = nullptr, int timeout = DEFWAIT);

#endif