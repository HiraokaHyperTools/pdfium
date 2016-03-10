// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FPDFAPI_CFDF_DOCUMENT_H_
#define CORE_INCLUDE_FPDFAPI_CFDF_DOCUMENT_H_

#include "core/include/fpdfapi/cpdf_indirect_object_holder.h"
#include "core/include/fpdfapi/cpdf_object.h"
#include "core/include/fxcrt/fx_basic.h"

class CPDF_Dictionary;

class CFDF_Document : public CPDF_IndirectObjectHolder {
 public:
  static CFDF_Document* CreateNewDoc();
  static CFDF_Document* ParseFile(IFX_FileRead* pFile,
                                  FX_BOOL bOwnFile = FALSE);
  static CFDF_Document* ParseMemory(const uint8_t* pData, FX_DWORD size);
  ~CFDF_Document();

  FX_BOOL WriteBuf(CFX_ByteTextBuf& buf) const;
  CPDF_Dictionary* GetRoot() const { return m_pRootDict; }

 protected:
  CFDF_Document();
  void ParseStream(IFX_FileRead* pFile, FX_BOOL bOwnFile);

  CPDF_Dictionary* m_pRootDict;
  IFX_FileRead* m_pFile;
  FX_BOOL m_bOwnFile;
};

#endif  // CORE_INCLUDE_FPDFAPI_CFDF_DOCUMENT_H_
