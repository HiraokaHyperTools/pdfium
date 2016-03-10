// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FPDFAPI_CPDF_NUMBER_H_
#define CORE_INCLUDE_FPDFAPI_CPDF_NUMBER_H_

#include "core/include/fpdfapi/cpdf_object.h"
#include "core/include/fxcrt/fx_string.h"
#include "core/include/fxcrt/fx_system.h"

class CPDF_Number : public CPDF_Object {
 public:
  CPDF_Number();
  explicit CPDF_Number(int value);
  explicit CPDF_Number(FX_FLOAT value);
  explicit CPDF_Number(const CFX_ByteStringC& str);

  // CPDF_Object.
  Type GetType() const override;
  CPDF_Object* Clone(FX_BOOL bDirect = FALSE) const override;
  CFX_ByteString GetString() const override;
  FX_FLOAT GetNumber() const override;
  int GetInteger() const override;
  void SetString(const CFX_ByteString& str) override;
  bool IsNumber() const override;
  CPDF_Number* AsNumber() override;
  const CPDF_Number* AsNumber() const override;

  FX_BOOL IsInteger() { return m_bInteger; }

 protected:
  ~CPDF_Number() override;

  FX_BOOL m_bInteger;
  union {
    int m_Integer;
    FX_FLOAT m_Float;
  };
};

#endif  // CORE_INCLUDE_FPDFAPI_CPDF_NUMBER_H_
