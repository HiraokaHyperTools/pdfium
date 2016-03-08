// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/include/fwl/adapter/fwl_adapternative.h"
#include "xfa/include/fwl/adapter/fwl_adaptertimermgr.h"
#include "xfa/include/fwl/core/fwl_app.h"
#include "xfa/include/fwl/core/fwl_timer.h"
#include "xfa/src/fwl/src/core/fwl_appimp.h"
#include "xfa/src/fwl/src/core/fwl_targetimp.h"
#include "xfa/src/fwl/src/core/fwl_threadimp.h"

FWL_HTIMER FWL_StartTimer(IFWL_Timer* pTimer,
                          FX_DWORD dwElapse,
                          FX_BOOL bImmediately) {
  IFWL_AdapterNative* pAdapterNative = FWL_GetAdapterNative();
  if (!pAdapterNative)
    return NULL;
  IFWL_AdapterTimerMgr* pAdapterTimerMgr = pAdapterNative->GetTimerMgr();
  if (!pAdapterTimerMgr)
    return NULL;
  FWL_HTIMER hTimer = NULL;
  pAdapterTimerMgr->Start(pTimer, dwElapse, hTimer, bImmediately);
  return hTimer;
}
int32_t FWL_StopTimer(FWL_HTIMER hTimer) {
  IFWL_AdapterNative* pAdapterNative = FWL_GetAdapterNative();
  if (!pAdapterNative)
    return FWL_ERR_Indefinite;
  IFWL_AdapterTimerMgr* pAdapterTimerMgr = pAdapterNative->GetTimerMgr();
  if (!pAdapterTimerMgr)
    return FWL_ERR_Indefinite;
  return pAdapterTimerMgr->Stop(hTimer);
}
