// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/include/fpdfapi/cpdf_indirect_object_holder.h"
#include "core/include/fpdfapi/cpdf_object.h"
#include "core/include/fpdfapi/cpdf_parser.h"

CPDF_IndirectObjectHolder::CPDF_IndirectObjectHolder(CPDF_Parser* pParser)
    : m_pParser(pParser), m_LastObjNum(0) {
  if (pParser)
    m_LastObjNum = m_pParser->GetLastObjNum();
}

CPDF_IndirectObjectHolder::~CPDF_IndirectObjectHolder() {
  for (const auto& pair : m_IndirectObjs)
    pair.second->Destroy();
}

CPDF_Object* CPDF_IndirectObjectHolder::GetIndirectObject(FX_DWORD objnum) {
  if (objnum == 0)
    return nullptr;

  auto it = m_IndirectObjs.find(objnum);
  if (it != m_IndirectObjs.end())
    return it->second->GetObjNum() != -1 ? it->second : nullptr;

  if (!m_pParser)
    return nullptr;

  CPDF_Object* pObj = m_pParser->ParseIndirectObject(this, objnum);
  if (!pObj)
    return nullptr;

  pObj->m_ObjNum = objnum;
  m_LastObjNum = std::max(m_LastObjNum, objnum);
  if (m_IndirectObjs[objnum])
    m_IndirectObjs[objnum]->Destroy();

  m_IndirectObjs[objnum] = pObj;
  return pObj;
}

FX_DWORD CPDF_IndirectObjectHolder::AddIndirectObject(CPDF_Object* pObj) {
  if (pObj->m_ObjNum)
    return pObj->m_ObjNum;

  m_LastObjNum++;
  m_IndirectObjs[m_LastObjNum] = pObj;
  pObj->m_ObjNum = m_LastObjNum;
  return m_LastObjNum;
}

void CPDF_IndirectObjectHolder::ReleaseIndirectObject(FX_DWORD objnum) {
  auto it = m_IndirectObjs.find(objnum);
  if (it == m_IndirectObjs.end() || it->second->GetObjNum() == -1)
    return;
  it->second->Destroy();
  m_IndirectObjs.erase(it);
}

FX_BOOL CPDF_IndirectObjectHolder::InsertIndirectObject(FX_DWORD objnum,
                                                        CPDF_Object* pObj) {
  if (!objnum || !pObj)
    return FALSE;
  auto it = m_IndirectObjs.find(objnum);
  if (it != m_IndirectObjs.end()) {
    if (pObj->GetGenNum() <= it->second->GetGenNum()) {
      pObj->Destroy();
      return FALSE;
    }
    it->second->Destroy();
  }
  pObj->m_ObjNum = objnum;
  m_IndirectObjs[objnum] = pObj;
  m_LastObjNum = std::max(m_LastObjNum, objnum);
  return TRUE;
}
