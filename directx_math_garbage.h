#pragma once

#include <stdint.h>

namespace DirectX {

typedef struct XMVECTOR {
  float m128_f32[4];
} XMVECTOR;

typedef struct XMMATRIX {
  XMVECTOR r[4];
} XMMATRIX;

} // namespace DirectX

static inline DirectX::XMMATRIX Matrix4x4Identity() {
  DirectX::XMMATRIX out;
  out.r[0].m128_f32[0] = 1.f; out.r[0].m128_f32[1] = 0.f; out.r[0].m128_f32[2] = 0.f; out.r[0].m128_f32[3] = 0.f;
  out.r[1].m128_f32[0] = 0.f; out.r[1].m128_f32[1] = 1.f; out.r[1].m128_f32[2] = 0.f; out.r[1].m128_f32[3] = 0.f;
  out.r[2].m128_f32[0] = 0.f; out.r[2].m128_f32[1] = 0.f; out.r[2].m128_f32[2] = 1.f; out.r[2].m128_f32[3] = 0.f;
  out.r[3].m128_f32[0] = 0.f; out.r[3].m128_f32[1] = 0.f; out.r[3].m128_f32[2] = 0.f; out.r[3].m128_f32[3] = 1.f;
  return out;
}

// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix/1148405#1148405
// https://stackoverflow.com/questions/17475929/access-floats-of-xmmatrix-operator-not-working/26453966#26453966
static inline DirectX::XMMATRIX Matrix4x4Invert(DirectX::XMMATRIX input) {
  double m[16] = {};
  for (int y = 0; y < 4; y += 1) {
    for (int x = 0; x < 4; x += 1) {
      m[y * 4 + x] = input.r[y].m128_f32[x];
    }
  }

  double inv[16] = {};
  double det = 0;

  inv[0] = m[5]  * m[10] * m[15] - 
           m[5]  * m[11] * m[14] - 
           m[9]  * m[6]  * m[15] + 
           m[9]  * m[7]  * m[14] +
           m[13] * m[6]  * m[11] - 
           m[13] * m[7]  * m[10];

  inv[4] = -m[4]  * m[10] * m[15] + 
            m[4]  * m[11] * m[14] + 
            m[8]  * m[6]  * m[15] - 
            m[8]  * m[7]  * m[14] - 
            m[12] * m[6]  * m[11] + 
            m[12] * m[7]  * m[10];

  inv[8] = m[4]  * m[9] * m[15] - 
           m[4]  * m[11] * m[13] - 
           m[8]  * m[5] * m[15] + 
           m[8]  * m[7] * m[13] + 
           m[12] * m[5] * m[11] - 
           m[12] * m[7] * m[9];

  inv[12] = -m[4]  * m[9] * m[14] + 
             m[4]  * m[10] * m[13] +
             m[8]  * m[5] * m[14] - 
             m[8]  * m[6] * m[13] - 
             m[12] * m[5] * m[10] + 
             m[12] * m[6] * m[9];

  inv[1] = -m[1]  * m[10] * m[15] + 
            m[1]  * m[11] * m[14] + 
            m[9]  * m[2] * m[15] - 
            m[9]  * m[3] * m[14] - 
            m[13] * m[2] * m[11] + 
            m[13] * m[3] * m[10];

  inv[5] = m[0]  * m[10] * m[15] - 
           m[0]  * m[11] * m[14] - 
           m[8]  * m[2] * m[15] + 
           m[8]  * m[3] * m[14] + 
           m[12] * m[2] * m[11] - 
           m[12] * m[3] * m[10];

  inv[9] = -m[0]  * m[9] * m[15] + 
            m[0]  * m[11] * m[13] + 
            m[8]  * m[1] * m[15] - 
            m[8]  * m[3] * m[13] - 
            m[12] * m[1] * m[11] + 
            m[12] * m[3] * m[9];

  inv[13] = m[0]  * m[9] * m[14] - 
            m[0]  * m[10] * m[13] - 
            m[8]  * m[1] * m[14] + 
            m[8]  * m[2] * m[13] + 
            m[12] * m[1] * m[10] - 
            m[12] * m[2] * m[9];

  inv[2] = m[1]  * m[6] * m[15] - 
           m[1]  * m[7] * m[14] - 
           m[5]  * m[2] * m[15] + 
           m[5]  * m[3] * m[14] + 
           m[13] * m[2] * m[7] - 
           m[13] * m[3] * m[6];

  inv[6] = -m[0]  * m[6] * m[15] + 
            m[0]  * m[7] * m[14] + 
            m[4]  * m[2] * m[15] - 
            m[4]  * m[3] * m[14] - 
            m[12] * m[2] * m[7] + 
            m[12] * m[3] * m[6];

  inv[10] = m[0]  * m[5] * m[15] - 
            m[0]  * m[7] * m[13] - 
            m[4]  * m[1] * m[15] + 
            m[4]  * m[3] * m[13] + 
            m[12] * m[1] * m[7] - 
            m[12] * m[3] * m[5];

  inv[14] = -m[0]  * m[5] * m[14] + 
             m[0]  * m[6] * m[13] + 
             m[4]  * m[1] * m[14] - 
             m[4]  * m[2] * m[13] - 
             m[12] * m[1] * m[6] + 
             m[12] * m[2] * m[5];

  inv[3] = -m[1] * m[6] * m[11] + 
            m[1] * m[7] * m[10] + 
            m[5] * m[2] * m[11] - 
            m[5] * m[3] * m[10] - 
            m[9] * m[2] * m[7] + 
            m[9] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] - 
            m[0] * m[7] * m[10] - 
            m[4] * m[2] * m[11] + 
            m[4] * m[3] * m[10] + 
            m[8] * m[2] * m[7] - 
            m[8] * m[3] * m[6];

  inv[11] = -m[0] * m[5] * m[11] + 
             m[0] * m[7] * m[9] + 
             m[4] * m[1] * m[11] - 
             m[4] * m[3] * m[9] - 
             m[8] * m[1] * m[7] + 
             m[8] * m[3] * m[5];

  inv[15] = m[0] * m[5] * m[10] - 
            m[0] * m[6] * m[9] - 
            m[4] * m[1] * m[10] + 
            m[4] * m[2] * m[9] + 
            m[8] * m[1] * m[6] - 
            m[8] * m[2] * m[5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (det != 0) {
    det = 1.0 / det;
  }

  double invOut[16] = {};
  for (int i = 0; i < 16; i += 1) {
    invOut[i] = inv[i] * det;
  }

  DirectX::XMMATRIX out;
  for (int y = 0; y < 4; y += 1) {
    for (int x = 0; x < 4; x += 1) {
      out.r[y].m128_f32[x] = invOut[y * 4 + x];
    }
  }

  return out;
}

// https://stackoverflow.com/questions/16737298/what-is-the-fastest-way-to-transpose-a-matrix-in-c/16743203#16743203
static inline DirectX::XMMATRIX Matrix4x4Transpose(DirectX::XMMATRIX input) {
  double m[16] = {};
  for (int n = 0; n < 4 * 4; n += 1) {
    int i = n / 4;
    int j = n % 4;
    m[n] = input.r[j].m128_f32[i];
  }

  DirectX::XMMATRIX out;
  for (int y = 0; y < 4; y += 1) {
    for (int x = 0; x < 4; x += 1) {
      out.r[y].m128_f32[x] = m[y * 4 + x];
    }
  }

  return out;
}
