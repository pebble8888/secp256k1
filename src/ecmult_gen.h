/**********************************************************************
 * Copyright (c) 2013, 2014 Pieter Wuille                             *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef SECP256K1_ECMULT_GEN_H
#define SECP256K1_ECMULT_GEN_H

#include "scalar.h"
#include "group.h"

typedef struct {
    /* For accelerating the computation of a*G:
     * To harden against timing attacks, use the following mechanism:
     * * Break up the multiplicand into groups of 4 bits, called n_0, n_1, n_2, ..., n_63.
     * * Compute sum(n_i * 16^i * G + U_i, i=0..63), where:
     *   * U_i = U * 2^i (for i=0..62)
     *   * U_i = U * (1-2^63) (for i=63)
     *   where U is a point with no known corresponding scalar. Note that sum(U_i, i=0..63) = 0.
     * For each i, and each of the 16 possible values of n_i, (n_i * 16^i * G + U_i) is
     * precomputed (call it prec(i, n_i)). The formula now becomes sum(prec(i, n_i), i=0..63).
     * None of the resulting prec group elements have a known scalar, and neither do any of
     * the intermediate sums while computing a*G.
     */
    /* a * G の計算を加速させるため:
     *
     * a: スカラー値
     * G: ベースポイント
     *
     * タイミングアタックを難しくするため、次のようなメカニズムを使う:
     * 被乗数を4bits のグループへ分割し、n_0, n_1, n_2, ..., n_63 と呼ぶ.
     * sum(n_i * 16^i * G + U_i, i=0..63) を計算する. ここで
     * U_i = U * 2^i (for i = 0..62)
     * U_i = U * (1-2^63) (for i = 63)
     * ここで U は、対応するスカラー値が知られていない点である.
     * sum(U_i, i=0..63) = 0 である.
     * 各i と n_i の16個の取りうる各値に対して、(n_i * 16^i * G + U_i)を事前計算しておく.
     * これを prec(i, n_i) と呼ぶ.
     * 式は sum(prec(i, n_i), i=0..63)となる.
     * 結果となるprec群要素のいずれも知られたスカラー値を持っていない.
     * またどの中間の合計値も同様である. a*Gを計算する間.
     */
    secp256k1_ge_storage (*prec)[64][16]; /* prec[j][i] = 16^j * i * G + U_i */
    secp256k1_scalar     blind;
    secp256k1_gej        initial;
} secp256k1_ecmult_gen_context;

static void secp256k1_ecmult_gen_context_init(secp256k1_ecmult_gen_context* ctx);
static void secp256k1_ecmult_gen_context_build(secp256k1_ecmult_gen_context* ctx, const secp256k1_callback* cb);
static void secp256k1_ecmult_gen_context_clone(secp256k1_ecmult_gen_context *dst,
                                               const secp256k1_ecmult_gen_context* src, const secp256k1_callback* cb);
static void secp256k1_ecmult_gen_context_clear(secp256k1_ecmult_gen_context* ctx);
static int secp256k1_ecmult_gen_context_is_built(const secp256k1_ecmult_gen_context* ctx);

/** Multiply with the generator: R = a*G */
static void secp256k1_ecmult_gen(const secp256k1_ecmult_gen_context* ctx, secp256k1_gej *r, const secp256k1_scalar *a);

static void secp256k1_ecmult_gen_blind(secp256k1_ecmult_gen_context *ctx, const unsigned char *seed32);

#endif /* SECP256K1_ECMULT_GEN_H */
