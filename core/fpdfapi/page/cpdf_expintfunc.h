// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_PAGE_CPDF_EXPINTFUNC_H_
#define CORE_FPDFAPI_PAGE_CPDF_EXPINTFUNC_H_

#include <set>

#include "core/fpdfapi/page/cpdf_function.h"
#include "core/fxcrt/data_vector.h"

#if defined(_SKIA_SUPPORT_) || defined(_SKIA_SUPPORT_PATHS_)
#include "third_party/base/span.h"
#endif

class CPDF_ExpIntFunc final : public CPDF_Function {
 public:
  CPDF_ExpIntFunc();
  ~CPDF_ExpIntFunc() override;

  // CPDF_Function:
  bool v_Init(const CPDF_Object* pObj,
              std::set<const CPDF_Object*>* pVisited) override;
  bool v_Call(pdfium::span<const float> inputs,
              pdfium::span<float> results) const override;

  uint32_t GetOrigOutputs() const { return m_nOrigOutputs; }
  float GetExponent() const { return m_Exponent; }

#if defined(_SKIA_SUPPORT_) || defined(_SKIA_SUPPORT_PATHS_)
  pdfium::span<const float> GetBeginValues() const { return m_BeginValues; }
  pdfium::span<const float> GetEndValues() const { return m_EndValues; }
#endif

 private:
  uint32_t m_nOrigOutputs = 0;
  float m_Exponent = 0.0f;
  DataVector<float> m_BeginValues;
  DataVector<float> m_EndValues;
};

#endif  // CORE_FPDFAPI_PAGE_CPDF_EXPINTFUNC_H_
