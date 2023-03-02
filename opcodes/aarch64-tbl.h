/* aarch64-tbl.h -- AArch64 opcode description table and instruction
   operand description table.
   Copyright (C) 2012-2023 Free Software Foundation, Inc.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "aarch64-opc.h"

#ifndef VERIFIER
#error  VERIFIER must be defined.
#endif

/* Operand type.  */

#define OPND(x)	AARCH64_OPND_##x
#define OP0() {}
#define OP1(a) {OPND(a)}
#define OP2(a,b) {OPND(a), OPND(b)}
#define OP3(a,b,c) {OPND(a), OPND(b), OPND(c)}
#define OP4(a,b,c,d) {OPND(a), OPND(b), OPND(c), OPND(d)}
#define OP5(a,b,c,d,e) {OPND(a), OPND(b), OPND(c), OPND(d), OPND(e)}

#define QLF(x) AARCH64_OPND_QLF_##x
#define QLF1(a) {QLF(a)}
#define QLF2(a,b) {QLF(a), QLF(b)}
#define QLF3(a,b,c) {QLF(a), QLF(b), QLF(c)}
#define QLF4(a,b,c,d) {QLF(a), QLF(b), QLF(c), QLF(d)}
#define QLF5(a,b,c,d,e) {QLF(a), QLF(b), QLF(c), QLF(d), QLF(e)}

/* Qualifiers list.  */

/* e.g. MSR <systemreg>, <Xt>.  */
#define QL_SRC_X		\
{				\
  QLF2(NIL,X),			\
}

/* e.g. MRS <Xt>, <systemreg>.  */
#define QL_DST_X		\
{				\
  QLF2(X,NIL),			\
}

/* e.g. SYS #<op1>, <Cn>, <Cm>, #<op2>{, <Xt>}.  */
#define QL_SYS			\
{				\
  QLF5(NIL,CR,CR,NIL,X),	\
}

/* e.g. SYSL <Xt>, #<op1>, <Cn>, <Cm>, #<op2>.  */
#define QL_SYSL			\
{				\
  QLF5(X,NIL,CR,CR,NIL),	\
}

/* e.g. ADRP <Xd>, <label>.  */
#define QL_ADRP			\
{				\
  QLF2(X,NIL),			\
}

/* e.g. TCANCEL #<imm>.  */
#define QL_IMM_NIL		\
{				\
  QLF1(NIL),			\
}

/* e.g. B.<cond> <label>.  */
#define QL_PCREL_NIL		\
{				\
  QLF1(NIL),			\
}

/* e.g. TBZ <Xt>, #<imm>, <label>.  */
#define QL_PCREL_14		\
{				\
  QLF3(X,imm_0_63,NIL),		\
}

/* e.g. BL <label>.  */
#define QL_PCREL_26		\
{				\
  QLF1(NIL),			\
}

/* e.g. LDRSW <Xt>, <label>.  */
#define QL_X_PCREL		\
{				\
  QLF2(X,NIL),			\
}

/* e.g. LDR <Wt>, <label>.  */
#define QL_R_PCREL		\
{				\
  QLF2(X,NIL),			\
}

/* e.g. LDR <Dt>, <label>.  */
#define QL_FP_PCREL		\
{				\
  QLF2(S_S,NIL),		\
  QLF2(S_D,NIL),		\
  QLF2(S_Q,NIL),		\
}

/* e.g. PRFM <prfop>, <label>.  */
#define QL_PRFM_PCREL		\
{				\
  QLF2(NIL,NIL),		\
}

/* e.g. BR <Xn>.  */
#define QL_I1X			\
{				\
  QLF1(X),			\
}

/* e.g. STG <Xt|SP>, [<Xn|SP>, #<imm9>].  */
#define QL_LDST_AT		\
{				\
  QLF2(X, imm_tag),		\
  QLF2(SP, imm_tag),		\
}

/* e.g. RBIT <Wd>, <Wn>.  */
#define QL_I2SAME		\
{				\
  QLF2(X,X),			\
}

/* e.g. CMN <Wn|WSP>, <Wm>{, <extend> {#<amount>}}.  */
#define QL_I2_EXT		\
{				\
  QLF2(X,X),			\
}

/* e.g. MOV <Wd|WSP>, <Wn|WSP>, at least one SP.  */
#define QL_I2SP			\
{				\
  QLF2(SP,X),			\
  QLF2(X,SP),			\
}

/* e.g. REV <Wd>, <Wn>.  */
#define QL_I2SAMEW		\
{				\
}

/* e.g. REV32 <Xd>, <Xn>.  */
#define QL_I2SAMEX		\
{				\
  QLF2(X,X),			\
}

#define QL_I2SAMER		\
{				\
  QLF2(X,X),			\
}

/* e.g. CRC32B <Wd>, <Wn>, <Wm>.  */
#define QL_I3SAMEW		\
{				\
}

/* e.g. SMULH <Xd>, <Xn>, <Xm>.  */
#define QL_I3SAMEX		\
{				\
  QLF3(X,X,X),			\
}

/* e.g. CRC32X <Wd>, <Wn>, <Xm>.  */
#define QL_I3WWX		\
{				\
}

/* e.g. UDIV <Xd>, <Xn>, <Xm>.  */
#define QL_I3SAMER		\
{				\
  QLF3(X,X,X),			\
}

/* e.g. ADDS <Xd>, <Xn|SP>, <R><m>{, <extend> {#<amount>}}.  */
#define QL_I3_EXT		\
{				\
  QLF3(X,X,X),			\
}

/* e.g. MADD <Xd>, <Xn>, <Xm>, <Xa>.  */
#define QL_I4SAMER		\
{				\
  QLF4(X,X,X,X),		\
}

/* e.g. SMADDL <Xd>, <Wn>, <Wm>, <Xa>.  */
#define QL_I3SAMEL		\
{				\
}

/* e.g. SMADDL <Xd>, <Wn>, <Wm>, <Xa>.  */
#define QL_I4SAMEL		\
{				\
}

/* e.g. CSINC <Xd>, <Xn>, <Xm>, <cond>.  */
#define QL_CSEL			\
{				\
  QLF4(X, X, X, NIL),		\
}

/* e.g. CSET <Wd>, <cond>.  */
#define QL_DST_R			\
{				\
  QLF2(X, NIL),			\
}

/* e.g. BFM <Wd>, <Wn>, #<immr>, #<imms>.  */
#define QL_BF			\
{				\
  QLF4(X,X,imm_0_63,imm_0_63),	\
}

/* e.g. ADDG <Xd>, <Xn>, #<uimm10>, #<uimm4>.  */
#define QL_ADDG			\
{				\
  QLF4(X,X,NIL,imm_0_15),	\
}				\

/* e.g. BFC <Wd>, #<immr>, #<imms>.  */
#define QL_BF1					\
{						\
  QLF3 (W, imm_0_31, imm_1_32),			\
  QLF3 (X, imm_0_63, imm_1_64),			\
}

/* e.g. UBFIZ <Wd>, <Wn>, #<lsb>, #<width>.  */
#define QL_BF2			\
{				\
  QLF4(X,X,imm_0_63,imm_1_64),	\
}

/* e.g. SCVTF <Sd>, <Xn>, #<fbits>.  */
#define QL_FIX2FP		\
{				\
  QLF3(S_D,X,imm_1_64),		\
  QLF3(S_S,X,imm_1_64),		\
}

/* e.g. SCVTF <Hd>, <Xn>, #<fbits>.  */
#define QL_FIX2FP_H			\
{					\
  QLF3 (S_H, W, imm_1_32),		\
  QLF3 (S_H, X, imm_1_64),		\
}

/* e.g. FCVTZS <Wd>, <Dn>, #<fbits>.  */
#define QL_FP2FIX		\
{				\
  QLF3(X,S_D,imm_1_64),		\
  QLF3(X,S_S,imm_1_64),		\
}

/* e.g. FCVTZS <Wd>, <Hn>, #<fbits>.  */
#define QL_FP2FIX_H			\
{					\
  QLF3 (W, S_H, imm_1_32),		\
  QLF3 (X, S_H, imm_1_64),		\
}

/* e.g. SCVTF <Dd>, <Wn>.  */
#define QL_INT2FP		\
{				\
  QLF2(S_D,X),			\
  QLF2(S_S,X),			\
}

/* e.g. FMOV <Dd>, <Xn>.  */
#define QL_INT2FP_FMOV		\
{				\
  QLF2(S_D,X),			\
}

/* e.g. SCVTF <Hd>, <Wn>.  */
#define QL_INT2FP_H			\
{					\
  QLF2 (S_H, W),			\
  QLF2 (S_H, X),			\
}

/* e.g. FCVTNS <Xd>, <Dn>.  */
#define QL_FP2INT		\
{				\
  QLF2(X,S_D),			\
  QLF2(X,S_S),			\
}

/* e.g. FMOV <Xd>, <Dn>.  */
#define QL_FP2INT_FMOV		\
{				\
  QLF2(X,S_D),			\
}

/* e.g. FCVTNS <Hd>, <Wn>.  */
#define QL_FP2INT_H			\
{					\
  QLF2 (W, S_H),			\
  QLF2 (X, S_H),			\
}

/* e.g. FJCVTZS <Wd>, <Dn>.  */
#define QL_FP2INT_W_D			\
{					\
  QLF2 (W, S_D),			\
}

/* e.g. FMOV <Xd>, <Vn>.D[1].  */
#define QL_XVD1			\
{				\
  QLF2(X,S_D),			\
}

/* e.g. FMOV <Vd>.D[1], <Xn>.  */
#define QL_VD1X			\
{				\
  QLF2(S_D,X),			\
}

/* e.g. EXTR <Xd>, <Xn>, <Xm>, #<lsb>.  */
#define QL_EXTR			\
{				\
  QLF4(X,X,X,imm_0_63),		\
}

/* e.g. LSL <Wd>, <Wn>, #<uimm>.  */
#define QL_SHIFT		\
{				\
  QLF3(X,X,imm_0_63),		\
}

/* e.g. UXTH <Xd>, <Wn>.  */
#define QL_EXT			\
{				\
}

/* e.g. UXTW <Xd>, <Wn>.  */
#define QL_EXT_W		\
{				\
}

/* e.g. SQSHL <V><d>, <V><n>, #<shift>.  */
#define QL_SSHIFT		\
{				\
  QLF3(S_B , S_B , S_B ),	\
  QLF3(S_H , S_H , S_H ),	\
  QLF3(S_S , S_S , S_S ),	\
  QLF3(S_D , S_D , S_D )	\
}

/* e.g. SSHR <V><d>, <V><n>, #<shift>.  */
#define QL_SSHIFT_D		\
{				\
  QLF3(S_D , S_D , S_D )	\
}

/* e.g. UCVTF <Vd>.<T>, <Vn>.<T>, #<fbits>.  */
#define QL_SSHIFT_SD		\
{				\
  QLF3(S_S , S_S , S_S ),	\
  QLF3(S_D , S_D , S_D )	\
}

/* e.g. UCVTF <Vd>.<T>, <Vn>.<T>, #<fbits>.  */
#define QL_SSHIFT_H		\
{				\
  QLF3 (S_H, S_H, S_H)		\
}

/* e.g. SQSHRUN <Vb><d>, <Va><n>, #<shift>.  */
#define QL_SSHIFTN		\
{				\
  QLF3(S_B , S_H , S_B ),	\
  QLF3(S_H , S_S , S_H ),	\
  QLF3(S_S , S_D , S_S ),	\
}

/* e.g. SSHR <Vd>.<T>, <Vn>.<T>, #<shift>.
   The register operand variant qualifiers are deliberately used for the
   immediate operand to ease the operand encoding/decoding and qualifier
   sequence matching.  */
#define QL_VSHIFT		\
{				\
  QLF3(V_8B , V_8B , V_8B ),	\
  QLF3(V_16B, V_16B, V_16B),	\
  QLF3(V_4H , V_4H , V_4H ),	\
  QLF3(V_8H , V_8H , V_8H ),	\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
  QLF3(V_2D , V_2D , V_2D )	\
}

/* e.g. SCVTF <Vd>.<T>, <Vn>.<T>, #<fbits>.  */
#define QL_VSHIFT_SD		\
{				\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
  QLF3(V_2D , V_2D , V_2D )	\
}

/* e.g. SCVTF <Vd>.<T>, <Vn>.<T>, #<fbits>.  */
#define QL_VSHIFT_H		\
{				\
  QLF3 (V_4H, V_4H, V_4H),	\
  QLF3 (V_8H, V_8H, V_8H)	\
}

/* e.g. SHRN<Q> <Vd>.<Tb>, <Vn>.<Ta>, #<shift>.  */
#define QL_VSHIFTN		\
{				\
  QLF3(V_8B , V_8H , V_8B ),	\
  QLF3(V_4H , V_4S , V_4H ),	\
  QLF3(V_2S , V_2D , V_2S ),	\
}

/* e.g. SHRN<Q> <Vd>.<Tb>, <Vn>.<Ta>, #<shift>.  */
#define QL_VSHIFTN2		\
{				\
  QLF3(V_16B, V_8H, V_16B),	\
  QLF3(V_8H , V_4S , V_8H ),	\
  QLF3(V_4S , V_2D , V_4S ),	\
}

/* e.g. SSHLL<Q> <Vd>.<Ta>, <Vn>.<Tb>, #<shift>.
   the 3rd qualifier is used to help the encoding.  */
#define QL_VSHIFTL		\
{				\
  QLF3(V_8H , V_8B , V_8B ),	\
  QLF3(V_4S , V_4H , V_4H ),	\
  QLF3(V_2D , V_2S , V_2S ),	\
}

/* e.g. SSHLL<Q> <Vd>.<Ta>, <Vn>.<Tb>, #<shift>.  */
#define QL_VSHIFTL2		\
{				\
  QLF3(V_8H , V_16B, V_16B),	\
  QLF3(V_4S , V_8H , V_8H ),	\
  QLF3(V_2D , V_4S , V_4S ),	\
}

/* e.g. TBL.  */
#define QL_TABLE		\
{				\
  QLF3(V_8B , V_16B, V_8B ),	\
  QLF3(V_16B, V_16B, V_16B),	\
}

/* e.g. SHA1H.  */
#define QL_2SAMES		\
{				\
  QLF2(S_S, S_S),		\
}

/* e.g. ABS <V><d>, <V><n>.  */
#define QL_2SAMED		\
{				\
  QLF2(S_D, S_D),		\
}

/* e.g. CMGT <V><d>, <V><n>, #0.  */
#define QL_SISD_CMP_0		\
{				\
  QLF3(S_D, S_D, NIL),		\
}

/* e.g. FCMEQ <V><d>, <V><n>, #0.  */
#define QL_SISD_FCMP_0		\
{				\
  QLF3(S_S, S_S, NIL),		\
  QLF3(S_D, S_D, NIL),		\
}

/* e.g. FCMEQ <V><d>, <V><n>, #0.  */
#define QL_SISD_FCMP_H_0	\
{				\
  QLF3 (S_H, S_H, NIL),		\
}

/* e.g. FMAXNMP <V><d>, <Vn>.<T>.  */
#define QL_SISD_PAIR		\
{				\
  QLF2(S_S, V_2S),		\
  QLF2(S_D, V_2D),		\
}

/* e.g. FMAXNMP <V><d>, <Vn>.<T>.  */
#define QL_SISD_PAIR_H		\
{				\
  QLF2 (S_H, V_2H),		\
}

/* e.g. ADDP <V><d>, <Vn>.<T>.  */
#define QL_SISD_PAIR_D		\
{				\
  QLF2(S_D, V_2D),		\
}

/* e.g. DUP <V><d>, <Vn>.<T>[<index>].  */
#define QL_S_2SAME		\
{				\
  QLF2(S_B, S_B),		\
  QLF2(S_H, S_H),		\
  QLF2(S_S, S_S),		\
  QLF2(S_D, S_D),		\
}

/* e.g. FCVTNS <V><d>, <V><n>.  */
#define QL_S_2SAMESD		\
{				\
  QLF2(S_S, S_S),		\
  QLF2(S_D, S_D),		\
}

/* e.g. FCVTNS <V><d>, <V><n>.  */
#define QL_S_2SAMEH		\
{				\
  QLF2 (S_H, S_H),		\
}

/* e.g. SQXTN <Vb><d>, <Va><n>.  */
#define QL_SISD_NARROW		\
{				\
  QLF2(S_B, S_H),		\
  QLF2(S_H, S_S),		\
  QLF2(S_S, S_D),		\
}

/* e.g. FCVTXN <Vb><d>, <Va><n>.  */
#define QL_SISD_NARROW_S	\
{				\
  QLF2(S_S, S_D),		\
}

/* e.g. FCVT.  */
#define QL_FCVT			\
{				\
  QLF2(S_S, S_H),		\
  QLF2(S_S, S_D),		\
  QLF2(S_D, S_H),		\
  QLF2(S_D, S_S),		\
  QLF2(S_H, S_S),		\
  QLF2(S_H, S_D),		\
}

/* FMOV <Dd>, <Dn>.  */
#define QL_FP2			\
{				\
  QLF2(S_S, S_S),		\
  QLF2(S_D, S_D),		\
}

/* FMOV <Hd>, <Hn>.  */
#define QL_FP2_H		\
{				\
  QLF2 (S_H, S_H),		\
}

/* e.g. SQADD <V><d>, <V><n>, <V><m>.  */
#define QL_S_3SAME		\
{				\
  QLF3(S_B, S_B, S_B),		\
  QLF3(S_H, S_H, S_H),		\
  QLF3(S_S, S_S, S_S),		\
  QLF3(S_D, S_D, S_D),		\
}

/* e.g. CMGE <V><d>, <V><n>, <V><m>.  */
#define QL_S_3SAMED		\
{				\
  QLF3(S_D, S_D, S_D),		\
}

/* e.g. SQDMULH <V><d>, <V><n>, <V><m>.  */
#define QL_SISD_HS		\
{				\
  QLF3(S_H, S_H, S_H),		\
  QLF3(S_S, S_S, S_S),		\
}

/* e.g. SQDMLAL <Va><d>, <Vb><n>, <Vb><m>.  */
#define QL_SISDL_HS		\
{				\
  QLF3(S_S, S_H, S_H),		\
  QLF3(S_D, S_S, S_S),		\
}

/* FMUL <Sd>, <Sn>, <Sm>.  */
#define QL_FP3			\
{				\
  QLF3(S_S, S_S, S_S),		\
  QLF3(S_D, S_D, S_D),		\
}

/* FMUL <Hd>, <Hn>, <Hm>.  */
#define QL_FP3_H		\
{				\
  QLF3 (S_H, S_H, S_H),		\
}

/* FMADD <Dd>, <Dn>, <Dm>, <Da>.  */
#define QL_FP4			\
{				\
  QLF4(S_S, S_S, S_S, S_S),	\
  QLF4(S_D, S_D, S_D, S_D),	\
}

/* FMADD <Hd>, <Hn>, <Hm>, <Ha>.  */
#define QL_FP4_H		\
{				\
  QLF4 (S_H, S_H, S_H, S_H),	\
}

/* e.g. FCMP <Dn>, #0.0.  */
#define QL_DST_SD			\
{				\
  QLF2(S_S, NIL),		\
  QLF2(S_D, NIL),		\
}

/* e.g. FCMP <Hn>, #0.0.  */
#define QL_DST_H		\
{				\
  QLF2 (S_H, NIL),		\
}

/* FCSEL <Sd>, <Sn>, <Sm>, <cond>.  */
#define QL_FP_COND		\
{				\
  QLF4(S_S, S_S, S_S, NIL),	\
  QLF4(S_D, S_D, S_D, NIL),	\
}

/* FCSEL <Hd>, <Hn>, <Hm>, <cond>.  */
#define QL_FP_COND_H		\
{				\
  QLF4 (S_H, S_H, S_H, NIL),	\
}

/* e.g. CCMN <Xn>, <Xm>, #<nzcv>, <cond>.  */
#define QL_CCMP			\
{				\
  QLF4(X, X, NIL, NIL),		\
}

/* e.g. CCMN <Xn>, #<imm>, #<nzcv>, <cond>,  */
#define QL_CCMP_IMM		\
{				\
  QLF4(X, NIL, NIL, NIL),	\
}

/* e.g. FCCMP <Sn>, <Sm>, #<nzcv>, <cond>.  */
#define QL_FCCMP		\
{				\
  QLF4(S_S, S_S, NIL, NIL),	\
  QLF4(S_D, S_D, NIL, NIL),	\
}

/* e.g. FCCMP <Sn>, <Sm>, #<nzcv>, <cond>.  */
#define QL_FCCMP_H		\
{				\
  QLF4 (S_H, S_H, NIL, NIL),	\
}

/* e.g. DUP <Vd>.<T>, <Vn>.<Ts>[<index>].  */
#define QL_DUP_VX		\
{				\
  QLF2(V_8B , S_B ),		\
  QLF2(V_16B, S_B ),		\
  QLF2(V_4H , S_H ),		\
  QLF2(V_8H , S_H ),		\
  QLF2(V_2S , S_S ),		\
  QLF2(V_4S , S_S ),		\
  QLF2(V_2D , S_D ),		\
}

/* e.g. DUP <Vd>.<T>, <Wn>.  */
#define QL_DUP_VR		\
{				\
  QLF2(V_2D , X ),		\
}

/* e.g. INS <Vd>.<Ts>[<index>], <Wn>.  */
#define QL_INS_XR		\
{				\
  QLF2(S_D , X ),		\
}

/* e.g. SMOV <Wd>, <Vn>.<Ts>[<index>].  */
#define QL_SMOV			\
{				\
  QLF2(X , S_H),		\
  QLF2(X , S_S),		\
  QLF2(X , S_B),		\
}

/* e.g. UMOV <Wd>, <Vn>.<Ts>[<index>].  */
#define QL_UMOV			\
{				\
  QLF2(X , S_D),		\
}

/* e.g. MOV <Wd>, <Vn>.<Ts>[<index>].  */
#define QL_MOV			\
{				\
  QLF2(X , S_D),		\
}

/* e.g. SUQADD <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAME		\
{				\
  QLF2(V_8B , V_8B ),		\
  QLF2(V_16B, V_16B),		\
  QLF2(V_4H , V_4H ),		\
  QLF2(V_8H , V_8H ),		\
  QLF2(V_2S , V_2S ),		\
  QLF2(V_4S , V_4S ),		\
  QLF2(V_2D , V_2D ),		\
}

/* e.g. URSQRTE <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAMES		\
{				\
  QLF2(V_2S , V_2S ),		\
  QLF2(V_4S , V_4S ),		\
}

/* e.g. REV32 <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAMEBH		\
{				\
  QLF2(V_8B , V_8B ),		\
  QLF2(V_16B, V_16B),		\
  QLF2(V_4H , V_4H ),		\
  QLF2(V_8H , V_8H ),		\
}

/* e.g. FRINTN <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAMESD		\
{				\
  QLF2(V_2S , V_2S ),		\
  QLF2(V_4S , V_4S ),		\
  QLF2(V_2D , V_2D ),		\
}

/* e.g. REV64 <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAMEBHS		\
{				\
  QLF2(V_8B , V_8B ),		\
  QLF2(V_16B, V_16B),		\
  QLF2(V_4H , V_4H ),		\
  QLF2(V_8H , V_8H ),		\
  QLF2(V_2S , V_2S ),		\
  QLF2(V_4S , V_4S ),		\
}

/* e.g. FCMGT <Vd>.<T>, <Vd>.<T>>, #0.0.  */
#define QL_V2SAMEH		\
{				\
  QLF2 (V_4H, V_4H),		\
  QLF2 (V_8H, V_8H),		\
}

/* e.g. REV16 <Vd>.<T>, <Vn>.<T>.  */
#define QL_V2SAMEB		\
{				\
  QLF2(V_8B , V_8B ),		\
  QLF2(V_16B, V_16B),		\
}

/* e.g. SADDLP <Vd>.<Ta>, <Vn>.<Tb>.  */
#define QL_V2PAIRWISELONGBHS		\
{				\
  QLF2(V_4H , V_8B ),		\
  QLF2(V_8H , V_16B),		\
  QLF2(V_2S , V_4H ),		\
  QLF2(V_4S , V_8H ),		\
  QLF2(V_1D , V_2S ),		\
  QLF2(V_2D , V_4S ),		\
}

/* e.g. SHLL<Q> <Vd>.<Ta>, <Vn>.<Tb>, #<shift>.  */
#define QL_V2LONGBHS		\
{				\
  QLF2(V_8H , V_8B ),		\
  QLF2(V_4S , V_4H ),		\
  QLF2(V_2D , V_2S ),		\
}

/* e.g. SHLL<Q> <Vd>.<Ta>, <Vn>.<Tb>, #<shift>.  */
#define QL_V2LONGBHS2		\
{				\
  QLF2(V_8H , V_16B),		\
  QLF2(V_4S , V_8H ),		\
  QLF2(V_2D , V_4S ),		\
}

/* */
#define QL_V3SAME		\
{				\
  QLF3(V_8B , V_8B , V_8B ),	\
  QLF3(V_16B, V_16B, V_16B),	\
  QLF3(V_4H , V_4H , V_4H ),	\
  QLF3(V_8H , V_8H , V_8H ),	\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
  QLF3(V_2D , V_2D , V_2D )	\
}

/* e.g. SHADD.  */
#define QL_V3SAMEBHS		\
{				\
  QLF3(V_8B , V_8B , V_8B ),	\
  QLF3(V_16B, V_16B, V_16B),	\
  QLF3(V_4H , V_4H , V_4H ),	\
  QLF3(V_8H , V_8H , V_8H ),	\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
}

/* e.g. FCVTXN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRS		\
{				\
  QLF2(V_2S , V_2D ),		\
}

/* e.g. FCVTXN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRS2		\
{				\
  QLF2(V_4S , V_2D ),		\
}

/* e.g. FCVTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRHS		\
{				\
  QLF2(V_4H , V_4S ),		\
  QLF2(V_2S , V_2D ),		\
}

/* e.g. FCVTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRHS2		\
{				\
  QLF2(V_8H , V_4S ),		\
  QLF2(V_4S , V_2D ),		\
}

/* e.g. FCVTL<Q> <Vd>.<Ta>, <Vn>.<Tb>.  */
#define QL_V2LONGHS		\
{				\
  QLF2(V_4S , V_4H ),		\
  QLF2(V_2D , V_2S ),		\
}

/* e.g. FCVTL<Q> <Vd>.<Ta>, <Vn>.<Tb>.  */
#define QL_V2LONGHS2		\
{				\
  QLF2(V_4S , V_8H ),		\
  QLF2(V_2D , V_4S ),		\
}

/* e.g. XTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRBHS		\
{				\
  QLF2(V_8B , V_8H ),		\
  QLF2(V_4H , V_4S ),		\
  QLF2(V_2S , V_2D ),		\
}

/* e.g. XTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
#define QL_V2NARRBHS2		\
{				\
  QLF2(V_16B, V_8H ),		\
  QLF2(V_8H , V_4S ),		\
  QLF2(V_4S , V_2D ),		\
}

/* e.g. ORR.  */
#define QL_V2SAMEB		\
{				\
  QLF2(V_8B , V_8B ),		\
  QLF2(V_16B, V_16B),		\
}

/* e.g. AESE.  */
#define QL_V2SAME16B		\
{				\
  QLF2(V_16B, V_16B),		\
}

/* e.g. SHA1SU1.  */
#define QL_V2SAME4S		\
{				\
  QLF2(V_4S, V_4S),		\
}

/* e.g. SHA1SU0.  */
#define QL_V3SAME4S		\
{				\
  QLF3(V_4S, V_4S, V_4S),	\
}

/* e.g. SHADD.  */
#define QL_V3SAMEB		\
{				\
  QLF3(V_8B , V_8B , V_8B ),	\
  QLF3(V_16B, V_16B, V_16B),	\
}

/* e.g. EXT <Vd>.<T>, <Vn>.<T>, <Vm>.<T>, #<index>.  */
#define QL_VEXT			\
{					\
  QLF4(V_8B , V_8B , V_8B , imm_0_7),	\
  QLF4(V_16B, V_16B, V_16B, imm_0_15),	\
}

/* e.g. .  */
#define QL_V3SAMEHS		\
{				\
  QLF3(V_4H , V_4H , V_4H ),	\
  QLF3(V_8H , V_8H , V_8H ),	\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
}

/* */
#define QL_V3SAMESD		\
{				\
  QLF3(V_2S , V_2S , V_2S ),	\
  QLF3(V_4S , V_4S , V_4S ),	\
  QLF3(V_2D , V_2D , V_2D )	\
}

/* e.g. FCMLA <Vd>.<T>, <Vn>.<T>, <Vm>.<T>, #<rotate>.  */
#define QL_V3SAMEHSD_ROT	\
{				\
  QLF4 (V_4H, V_4H, V_4H, NIL),	\
  QLF4 (V_8H, V_8H, V_8H, NIL),	\
  QLF4 (V_2S, V_2S, V_2S, NIL),	\
  QLF4 (V_4S, V_4S, V_4S, NIL),	\
  QLF4 (V_2D, V_2D, V_2D, NIL),	\
}

/* e.g. FMAXNM <Vd>.<T>, <Vn>.<T>, <Vm>.<T>.  */
#define QL_V3SAMEH		\
{				\
  QLF3 (V_4H , V_4H , V_4H ),	\
  QLF3 (V_8H , V_8H , V_8H ),	\
}

/* e.g. SQDMLAL<Q> <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb>.  */
#define QL_V3LONGHS		\
{				\
  QLF3(V_4S , V_4H , V_4H ),	\
  QLF3(V_2D , V_2S , V_2S ),	\
}

/* e.g. SQDMLAL<Q> <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb>.  */
#define QL_V3LONGHS2		\
{				\
  QLF3(V_4S , V_8H , V_8H ),	\
  QLF3(V_2D , V_4S , V_4S ),	\
}

/* e.g. SADDL<Q> <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb>.  */
#define QL_V3LONGBHS		\
{				\
  QLF3(V_8H , V_8B , V_8B ),	\
  QLF3(V_4S , V_4H , V_4H ),	\
  QLF3(V_2D , V_2S , V_2S ),	\
}

/* e.g. SADDL<Q> <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb>.  */
#define QL_V3LONGBHS2		\
{				\
  QLF3(V_8H , V_16B , V_16B ),	\
  QLF3(V_4S , V_8H , V_8H ),	\
  QLF3(V_2D , V_4S , V_4S ),	\
}

/* e.g. SADDW<Q> <Vd>.<Ta>, <Vn>.<Ta>, <Vm>.<Tb>.  */
#define QL_V3WIDEBHS		\
{				\
  QLF3(V_8H , V_8H , V_8B ),	\
  QLF3(V_4S , V_4S , V_4H ),	\
  QLF3(V_2D , V_2D , V_2S ),	\
}

/* e.g. SADDW<Q> <Vd>.<Ta>, <Vn>.<Ta>, <Vm>.<Tb>.  */
#define QL_V3WIDEBHS2		\
{				\
  QLF3(V_8H , V_8H , V_16B ),	\
  QLF3(V_4S , V_4S , V_8H ),	\
  QLF3(V_2D , V_2D , V_4S ),	\
}

/* e.g. ADDHN<Q> <Vd>.<Tb>, <Vn>.<Ta>, <Vm>.<Ta>.  */
#define QL_V3NARRBHS		\
{				\
  QLF3(V_8B , V_8H , V_8H ),	\
  QLF3(V_4H , V_4S , V_4S ),	\
  QLF3(V_2S , V_2D , V_2D ),	\
}

/* e.g. ADDHN<Q> <Vd>.<Tb>, <Vn>.<Ta>, <Vm>.<Ta>.  */
#define QL_V3NARRBHS2		\
{				\
  QLF3(V_16B , V_8H , V_8H ),	\
  QLF3(V_8H , V_4S , V_4S ),	\
  QLF3(V_4S , V_2D , V_2D ),	\
}

/* e.g. PMULL.  */
#define QL_V3LONGB		\
{				\
  QLF3(V_8H , V_8B , V_8B ),	\
}

/* e.g. PMULL crypto.  */
#define QL_V3LONGD		\
{				\
  QLF3(V_1Q , V_1D , V_1D ),	\
}

/* e.g. PMULL2.  */
#define QL_V3LONGB2		\
{				\
  QLF3(V_8H , V_16B, V_16B),	\
}

/* e.g. PMULL2 crypto.  */
#define QL_V3LONGD2		\
{				\
  QLF3(V_1Q , V_2D , V_2D ),	\
}

/* e.g. SHA1C.  */
#define QL_SHAUPT		\
{				\
  QLF3(S_Q, S_S, V_4S),		\
}

/* e.g. SHA256H2.  */
#define QL_SHA256UPT		\
{				\
  QLF3(S_Q, S_Q, V_4S),		\
}

/* e.g. LDXRB <Wt>, [<Xn|SP>{,#0}].  */
#define QL_W1_LDST_EXC		\
{				\
}

/* e.g. LDXR <Xt>, [<Xn|SP>{,#0}].  */
#define QL_R1NIL		\
{				\
  QLF2(X, NIL),			\
}

/* e.g. STXRB <Ws>, <Wt>, [<Xn|SP>{,#0}].  */
#define QL_W2_LDST_EXC		\
{				\
}

/* e.g. STXR <Ws>, <Xt>, [<Xn|SP>{,#0}].  */
#define QL_R2_LDST_EXC		\
{				\
}

/* e.g. ST64B <Xs>, <Xt>, [<Xn|SP>].  */
#define QL_X2NIL		\
{				\
  QLF3(X, X, NIL),			\
}

/* e.g. LDRAA <Xt>, [<Xn|SP>{,#imm}].  */
#define QL_X1NIL		\
{				\
  QLF2(X, NIL),			\
}

/* e.g. LDXP <Xt1>, <Xt2>, [<Xn|SP>{,#0}].  */
#define QL_R2NIL		\
{				\
  QLF3(X, X, NIL),		\
}

/* e.g. CASP <Xt1>, <Xt1+1>, <Xt2>, <Xt2+1>, [<Xn|SP>{,#0}].  */
#define QL_R4NIL		\
{				\
  QLF5(X, X, X, X, NIL),	\
}

/* e.g. STXP <Ws>, <Xt1>, <Xt2>, [<Xn|SP>{,#0}].  */
#define QL_R3_LDST_EXC		\
{				\
}

/* e.g. STR <Qt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_FP		\
{				\
  QLF2(S_B, S_B),		\
  QLF2(S_H, S_H),		\
  QLF2(S_S, S_S),		\
  QLF2(S_D, S_D),		\
  QLF2(S_Q, S_Q),		\
}

/* e.g. STR <Xt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_R		\
{				\
  QLF2(X, S_D),			\
}

/* e.g. STRB <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_W8		\
{				\
}

/* e.g. LDRSB <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_R8		\
{				\
  QLF2(X, S_B),			\
}

/* e.g. STRH <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_W16		\
{				\
}

/* e.g. LDRSW <Xt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_X32		\
{				\
  QLF2(X, S_S),			\
}

/* e.g. LDRSH <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_R16		\
{				\
  QLF2(X, S_H),			\
}

/* e.g. PRFM <prfop>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
#define QL_LDST_PRFM		\
{				\
  QLF2(NIL, S_D),		\
}

/* e.g. LDG <Xt>, [<Xn|SP>{, #<simm>}].  */
#define QL_LDG			\
{				\
  QLF2(X, imm_tag),		\
}

/* e.g. LDPSW <Xt1>, <Xt2>, [<Xn|SP>{, #<imm>}].  */
#define QL_LDST_PAIR_X32	\
{				\
  QLF3(X, X, S_S),		\
}

/* e.g. STGP <Xt1>, <Xt2>, [<Xn|SP>{, #<imm>}].  */
#define QL_STGP			\
{				\
  QLF3(X, X, imm_tag),		\
}

/* e.g. STP <Wt1>, <Wt2>, [<Xn|SP>, #<imm>]!.  */
#define QL_LDST_PAIR_R		\
{				\
  QLF3(X, X, S_D),		\
}

/* e.g. STNP <Qt1>, <Qt2>, [<Xn|SP>{, #<imm>}].  */
#define QL_LDST_PAIR_FP		\
{				\
  QLF3(S_S, S_S, S_S),		\
  QLF3(S_D, S_D, S_D),		\
  QLF3(S_Q, S_Q, S_Q),		\
}

/* e.g. LD3 {<Vt>.<T>, <Vt2>.<T>, <Vt3>.<T>}, [<Xn|SP>].  */
#define QL_SIMD_LDST		\
{				\
  QLF2(V_8B, NIL),		\
  QLF2(V_16B, NIL),		\
  QLF2(V_4H, NIL),		\
  QLF2(V_8H, NIL),		\
  QLF2(V_2S, NIL),		\
  QLF2(V_4S, NIL),		\
  QLF2(V_2D, NIL),		\
}

/* e.g. LD1 {<Vt>.<T>, <Vt2>.<T>, <Vt3>.<T>}, [<Xn|SP>].  */
#define QL_SIMD_LDST_ANY	\
{				\
  QLF2(V_8B, NIL),		\
  QLF2(V_16B, NIL),		\
  QLF2(V_4H, NIL),		\
  QLF2(V_8H, NIL),		\
  QLF2(V_2S, NIL),		\
  QLF2(V_4S, NIL),		\
  QLF2(V_1D, NIL),		\
  QLF2(V_2D, NIL),		\
}

/* e.g. LD4 {<Vt>.<T>, <Vt2a>.<T>, <Vt3a>.<T>, <Vt4a>.<T>}[<index>], [<Xn|SP>].  */
#define QL_SIMD_LDSTONE		\
{				\
  QLF2(S_B, NIL),		\
  QLF2(S_H, NIL),		\
  QLF2(S_S, NIL),		\
  QLF2(S_D, NIL),		\
}

/* e.g. ADDV <V><d>, <Vn>.<T>.  */
#define QL_XLANES		\
{				\
  QLF2(S_B, V_8B),		\
  QLF2(S_B, V_16B),		\
  QLF2(S_H, V_4H),		\
  QLF2(S_H, V_8H),		\
  QLF2(S_S, V_4S),		\
}

/* e.g. FMINV <V><d>, <Vn>.<T>.  */
#define QL_XLANES_FP		\
{				\
  QLF2(S_S, V_4S),		\
}

/* e.g. FMINV <V><d>, <Vn>.<T>.  */
#define QL_XLANES_FP_H		\
{				\
  QLF2 (S_H, V_4H),		\
  QLF2 (S_H, V_8H),		\
}

/* e.g. SADDLV <V><d>, <Vn>.<T>.  */
#define QL_XLANES_L		\
{				\
  QLF2(S_H, V_8B),		\
  QLF2(S_H, V_16B),		\
  QLF2(S_S, V_4H),		\
  QLF2(S_S, V_8H),		\
  QLF2(S_D, V_4S),		\
}

/* e.g. MUL <Vd>.<T>, <Vn>.<T>, <Vm>.<Ts>[<index>].  */
#define QL_ELEMENT		\
{				\
  QLF3(V_4H, V_4H, S_H),	\
  QLF3(V_8H, V_8H, S_H),	\
  QLF3(V_2S, V_2S, S_S),	\
  QLF3(V_4S, V_4S, S_S),	\
}

/* e.g. SMLAL <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Ts>[<index>].  */
#define QL_ELEMENT_L		\
{				\
  QLF3(V_4S, V_4H, S_H),	\
  QLF3(V_2D, V_2S, S_S),	\
}

/* e.g. SMLAL2 <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Ts>[<index>].  */
#define QL_ELEMENT_L2		\
{				\
  QLF3(V_4S, V_8H, S_H),	\
  QLF3(V_2D, V_4S, S_S),	\
}

/* e.g. FMLA <V><d>, <V><n>, <Vm>.<Ts>[<index>].  */
#define QL_ELEMENT_FP		\
{				\
  QLF3(V_2S, V_2S, S_S),	\
  QLF3(V_4S, V_4S, S_S),	\
  QLF3(V_2D, V_2D, S_D),	\
}

/* e.g. FMLA <V><d>, <V><n>, <Vm>.<Ts>[<index>].  */
#define QL_ELEMENT_FP_H		\
{				\
  QLF3 (V_4H, V_4H, S_H),	\
  QLF3 (V_8H, V_8H, S_H),	\
}

/* e.g. FCMLA <Vd>.<T>, <Vn>.<T>, <Vm>.<Ts>[<index>], #<rotate>.  */
#define QL_ELEMENT_ROT		\
{				\
  QLF4 (V_4H, V_4H, S_H, NIL),	\
  QLF4 (V_8H, V_8H, S_H, NIL),	\
  QLF4 (V_4S, V_4S, S_S, NIL),	\
}

/* e.g. MOVI <Vd>.4S, #<imm8> {, LSL #<amount>}.  */
#define QL_SIMD_IMM_S0W		\
{				\
  QLF2(V_2S, LSL),		\
  QLF2(V_4S, LSL),		\
}

/* e.g. MOVI <Vd>.4S, #<imm8>, MSL #<amount>.  */
#define QL_SIMD_IMM_S1W		\
{				\
  QLF2(V_2S, MSL),		\
  QLF2(V_4S, MSL),		\
}

/* e.g. MOVI <Vd>.4H, #<imm8> {, LSL #<amount>}.  */
#define QL_SIMD_IMM_S0H		\
{				\
  QLF2(V_4H, LSL),		\
  QLF2(V_8H, LSL),		\
}

/* e.g. FMOV <Vd>.<T>, #<imm>.  */
#define QL_SIMD_IMM_S		\
{				\
  QLF2(V_2S, NIL),		\
  QLF2(V_4S, NIL),		\
}

/* e.g. MOVI <Vd>.8B, #<imm8> {, LSL #<amount>}.  */
#define QL_SIMD_IMM_B		\
{				\
  QLF2(V_8B, LSL),		\
  QLF2(V_16B, LSL),		\
}
/* e.g. MOVI <Dd>, #<imm>.  */
#define QL_SIMD_IMM_D		\
{				\
  QLF2(S_D, NIL),		\
}

/* e.g. FMOV <Vd>.<T>, #<imm>.  */
#define QL_SIMD_IMM_H		\
{				\
  QLF2 (V_4H, NIL),		\
  QLF2 (V_8H, NIL),		\
}

/* e.g. MOVI <Vd>.2D, #<imm>.  */
#define QL_SIMD_IMM_V2D		\
{				\
  QLF2(V_2D, NIL),		\
}

/* The naming convention for SVE macros is:

   OP_SVE_<operands>[_<sizes>]*

   <operands> contains one character per operand, using the following scheme:

   - U: the operand is unqualified (NIL).

   - [BHSD]: the operand has a S_[BHSD] qualifier and the choice of
     qualifier is the same for all variants.  This is used for both
     .[BHSD] suffixes on an SVE predicate or vector register and
     scalar FPRs of the form [BHSD]<number>.

   - [WX]: the operand has a [WX] qualifier and the choice of qualifier
     is the same for all variants.

   - [ZM]: the operand has a /[ZM] suffix and the choice of suffix
     is the same for all variants.

   - V: the operand has a S_[BHSD] qualifier and the choice of qualifier
     is not the same for all variants.

   - R: the operand has a [WX] qualifier and the choice of qualifier is
     not the same for all variants.

   - P: the operand has a /[ZM] suffix and the choice of suffix is not
     the same for all variants.

   The _<sizes>, if present, give the subset of [BHSD] that are accepted
   by the V entries in <operands>.  */
#define OP_SVE_B                                        \
{                                                       \
  QLF1(S_B),                                            \
}
#define OP_SVE_BB                                       \
{                                                       \
  QLF2(S_B,S_B),                                        \
}
#define OP_SVE_BBU                                      \
{                                                       \
  QLF3(S_B,S_B,NIL),                                \
}
#define OP_SVE_BBB                                      \
{                                                       \
  QLF3(S_B,S_B,S_B),                                \
}
#define OP_SVE_BBBU                                     \
{                                                       \
  QLF4(S_B,S_B,S_B,NIL),                                \
}
#define OP_SVE_BMB                                      \
{                                                       \
  QLF3(S_B,P_M,S_B),                                    \
}
#define OP_SVE_BPB                                      \
{                                                       \
  QLF3(S_B,P_Z,S_B),                                    \
  QLF3(S_B,P_M,S_B),                                    \
}
#define OP_SVE_BUB                                      \
{                                                       \
  QLF3(S_B,NIL,S_B),                                    \
}
#define OP_SVE_BUBB                                     \
{                                                       \
  QLF4(S_B,NIL,S_B,S_B),                                \
}
#define OP_SVE_BUU                                      \
{                                                       \
  QLF3(S_B,NIL,NIL),                                    \
}
#define OP_SVE_BZ                                       \
{                                                       \
  QLF2(S_B,P_Z),                                        \
}
#define OP_SVE_BZB                                      \
{                                                       \
  QLF3(S_B,P_Z,S_B),                                    \
}
#define OP_SVE_NN_BHSD                                  \
{                                                       \
  QLF3(NIL,NIL,S_B),                                    \
  QLF3(NIL,NIL,S_H),                                    \
  QLF3(NIL,NIL,S_S),                                    \
  QLF3(NIL,NIL,S_D)                                     \
}
#define OP_SVE_BZBB                                     \
{                                                       \
  QLF4(S_B,P_Z,S_B,S_B),                                \
}
#define OP_SVE_BZU                                      \
{                                                       \
  QLF3(S_B,P_Z,NIL),                                    \
}
#define OP_SVE_DD                                       \
{                                                       \
  QLF2(S_D,S_D),                                        \
}
#define OP_SVE_DDD                                      \
{                                                       \
  QLF3(S_D,S_D,S_D),                                    \
}
#define OP_SVE_QQQ                                      \
{                                                       \
  QLF3(S_Q,S_Q,S_Q),                                    \
}
#define OP_SVE_DDDD                                     \
{                                                       \
  QLF4(S_D,S_D,S_D,S_D),                                \
}
#define OP_SVE_DMD                                      \
{                                                       \
  QLF3(S_D,P_M,S_D),                                    \
}
#define OP_SVE_QMQ                                      \
{                                                       \
  QLF3(S_Q,P_M,S_Q),                                    \
}
#define OP_SVE_DMH                                      \
{                                                       \
  QLF3(S_D,P_M,S_H),                                    \
}
#define OP_SVE_DMS                                      \
{                                                       \
  QLF3(S_D,P_M,S_S),                                    \
}
#define OP_SVE_DU                                       \
{                                                       \
  QLF2(S_D,NIL),                                        \
}
#define OP_SVE_DUD                                      \
{                                                       \
  QLF3(S_D,NIL,S_D),                                    \
}
#define OP_SVE_DUU                                      \
{                                                       \
  QLF3(S_D,NIL,NIL),                                    \
}
#define OP_SVE_QUU                                      \
{                                                       \
  QLF3(S_Q,NIL,NIL),                                    \
}
#define OP_SVE_DUV_BHS                                  \
{                                                       \
  QLF3(S_D,NIL,S_B),                                    \
  QLF3(S_D,NIL,S_H),                                    \
  QLF3(S_D,NIL,S_S),                                    \
}
#define OP_SVE_DUV_BHSD                                 \
{                                                       \
  QLF3(S_D,NIL,S_B),                                    \
  QLF3(S_D,NIL,S_H),                                    \
  QLF3(S_D,NIL,S_S),                                    \
  QLF3(S_D,NIL,S_D),                                    \
}
#define OP_SVE_DZD                                      \
{                                                       \
  QLF3(S_D,P_Z,S_D),                                    \
}
#define OP_SVE_DZU                                      \
{                                                       \
  QLF3(S_D,P_Z,NIL),                                    \
}
#define OP_SVE_QZU                                      \
{                                                       \
  QLF3(S_Q,P_Z,NIL),                                    \
}
#define OP_SVE_HB                                       \
{                                                       \
  QLF2(S_H,S_B),                                        \
}
#define OP_SVE_HHH                                      \
{                                                       \
  QLF3(S_H,S_H,S_H),                                    \
}
#define OP_SVE_HHHU                                     \
{                                                       \
  QLF4(S_H,S_H,S_H,NIL),                                \
}
#define OP_SVE_HMH                                      \
{                                                       \
  QLF3(S_H,P_M,S_H),                                    \
}
#define OP_SVE_HMD                                      \
{                                                       \
  QLF3(S_H,P_M,S_D),                                    \
}
#define OP_SVE_HMS                                      \
{                                                       \
  QLF3(S_H,P_M,S_S),                                    \
}
#define OP_SVE_HU                                       \
{                                                       \
  QLF2(S_H,NIL),                                        \
}
#define OP_SVE_HUU                                      \
{                                                       \
  QLF3(S_H,NIL,NIL),                                    \
}
#define OP_SVE_HZU                                      \
{                                                       \
  QLF3(S_H,P_Z,NIL),                                    \
}
#define OP_SVE_RR                                       \
{                                                       \
  QLF2(W,W),                                            \
  QLF2(X,X),                                            \
}
#define OP_SVE_RURV_BHSD                                \
{                                                       \
  QLF4(W,NIL,W,S_B),                                    \
  QLF4(W,NIL,W,S_H),                                    \
  QLF4(W,NIL,W,S_S),                                    \
  QLF4(X,NIL,X,S_D),                                    \
}
#define OP_SVE_RUV_BHSD                                 \
{                                                       \
  QLF3(W,NIL,S_B),                                      \
  QLF3(W,NIL,S_H),                                      \
  QLF3(W,NIL,S_S),                                      \
  QLF3(X,NIL,S_D),                                      \
}
#define OP_SVE_SMD                                      \
{                                                       \
  QLF3(S_S,P_M,S_D),                                    \
}
#define OP_SVE_SSS                                      \
{                                                       \
  QLF3(S_S,S_S,S_S),                                    \
}
#define OP_SVE_SSSU                                     \
{                                                       \
  QLF4(S_S,S_S,S_S,NIL),                                \
}
#define OP_SVE_SMH                                      \
{                                                       \
  QLF3(S_S,P_M,S_H),                                    \
}
#define OP_SVE_SHH                                      \
{                                                       \
  QLF3(S_S,S_H,S_H),                                    \
}
#define OP_SVE_SMS                                      \
{                                                       \
  QLF3(S_S,P_M,S_S),                                    \
}
#define OP_SVE_SU                                       \
{                                                       \
  QLF2(S_S,NIL),                                        \
}
#define OP_SVE_SUS                                      \
{                                                       \
  QLF3(S_S,NIL,S_S),                                    \
}
#define OP_SVE_SUU                                      \
{                                                       \
  QLF3(S_S,NIL,NIL),                                    \
}
#define OP_SVE_SZS                                      \
{                                                       \
  QLF3(S_S,P_Z,S_S),                                    \
}
#define OP_SVE_SBB                                      \
{                                                       \
  QLF3(S_S,S_B,S_B),                                    \
}
#define OP_SVE_SBBU                                     \
{                                                       \
  QLF4(S_S,S_B,S_B,NIL),                                \
}
#define OP_SVE_DSS                                      \
{                                                       \
  QLF3(S_D,S_S,S_S),                                    \
}
#define OP_SVE_DHHU                                     \
{                                                       \
  QLF4(S_D,S_H,S_H,NIL),                                \
}
#define OP_SVE_SZU                                      \
{                                                       \
  QLF3(S_S,P_Z,NIL),                                    \
}
#define OP_SVE_UB                                       \
{                                                       \
  QLF2(NIL,S_B),                                        \
}
#define OP_SVE_UUD                                      \
{                                                       \
  QLF3(NIL,NIL,S_D),                                    \
}
#define OP_SVE_UUS                                      \
{                                                       \
  QLF3(NIL,NIL,S_S),                                    \
}
#define OP_SVE_VMR_BHSD                                 \
{                                                       \
  QLF3(S_B,P_M,W),                                      \
  QLF3(S_H,P_M,W),                                      \
  QLF3(S_S,P_M,W),                                      \
  QLF3(S_D,P_M,X),                                      \
}
#define OP_SVE_VMU_HSD                                  \
{                                                       \
  QLF3(S_H,P_M,NIL),                                    \
  QLF3(S_S,P_M,NIL),                                    \
  QLF3(S_D,P_M,NIL),                                    \
}
#define OP_SVE_VMVD_BHS                                 \
{                                                       \
  QLF4(S_B,P_M,S_B,S_D),                                \
  QLF4(S_H,P_M,S_H,S_D),                                \
  QLF4(S_S,P_M,S_S,S_D),                                \
}
#define OP_SVE_VMVU_BHSD                                \
{                                                       \
  QLF4(S_B,P_M,S_B,NIL),                                \
  QLF4(S_H,P_M,S_H,NIL),                                \
  QLF4(S_S,P_M,S_S,NIL),                                \
  QLF4(S_D,P_M,S_D,NIL),                                \
}
#define OP_SVE_VMVU_HSD                                 \
{                                                       \
  QLF4(S_H,P_M,S_H,NIL),                                \
  QLF4(S_S,P_M,S_S,NIL),                                \
  QLF4(S_D,P_M,S_D,NIL),                                \
}
#define OP_SVE_VMVV_BHSD                                \
{                                                       \
  QLF4(S_B,P_M,S_B,S_B),                                \
  QLF4(S_H,P_M,S_H,S_H),                                \
  QLF4(S_S,P_M,S_S,S_S),                                \
  QLF4(S_D,P_M,S_D,S_D),                                \
}
#define OP_SVE_VMVV_HSD                                 \
{                                                       \
  QLF4(S_H,P_M,S_H,S_H),                                \
  QLF4(S_S,P_M,S_S,S_S),                                \
  QLF4(S_D,P_M,S_D,S_D),                                \
}
#define OP_SVE_VMVV_SD                                  \
{                                                       \
  QLF4(S_S,P_M,S_S,S_S),                                \
  QLF4(S_D,P_M,S_D,S_D),                                \
}
#define OP_SVE_VMVVU_HSD                                \
{                                                       \
  QLF5(S_H,P_M,S_H,S_H,NIL),                            \
  QLF5(S_S,P_M,S_S,S_S,NIL),                            \
  QLF5(S_D,P_M,S_D,S_D,NIL),                            \
}
#define OP_SVE_VMV_BHSD                                 \
{                                                       \
  QLF3(S_B,P_M,S_B),                                    \
  QLF3(S_H,P_M,S_H),                                    \
  QLF3(S_S,P_M,S_S),                                    \
  QLF3(S_D,P_M,S_D),                                    \
}
#define OP_SVE_VMV_HSD                                  \
{                                                       \
  QLF3(S_H,P_M,S_H),                                    \
  QLF3(S_S,P_M,S_S),                                    \
  QLF3(S_D,P_M,S_D),                                    \
}
#define OP_SVE_VMV_HSD_BHS                              \
{                                                       \
  QLF3(S_H,P_M,S_B),                                    \
  QLF3(S_S,P_M,S_H),                                    \
  QLF3(S_D,P_M,S_S),                                    \
}
#define OP_SVE_VVU_HSD_BHS                              \
{                                                       \
  QLF3(S_H,S_B,NIL),                                    \
  QLF3(S_S,S_H,NIL),                                    \
  QLF3(S_D,S_S,NIL),                                    \
}
#define OP_SVE_VMV_SD                                   \
{                                                       \
  QLF3(S_S,P_M,S_S),                                    \
  QLF3(S_D,P_M,S_D),                                    \
}
#define OP_SVE_VM_HSD                                   \
{                                                       \
  QLF2(S_H,P_M),                                        \
  QLF2(S_S,P_M),                                        \
  QLF2(S_D,P_M),                                        \
}
#define OP_SVE_VPU_BHSD                                 \
{                                                       \
  QLF3(S_B,P_Z,NIL),                                    \
  QLF3(S_B,P_M,NIL),                                    \
  QLF3(S_H,P_Z,NIL),                                    \
  QLF3(S_H,P_M,NIL),                                    \
  QLF3(S_S,P_Z,NIL),                                    \
  QLF3(S_S,P_M,NIL),                                    \
  QLF3(S_D,P_Z,NIL),                                    \
  QLF3(S_D,P_M,NIL),                                    \
}
#define OP_SVE_VPV_BHSD                                 \
{                                                       \
  QLF3(S_B,P_Z,S_B),                                    \
  QLF3(S_B,P_M,S_B),                                    \
  QLF3(S_H,P_Z,S_H),                                    \
  QLF3(S_H,P_M,S_H),                                    \
  QLF3(S_S,P_Z,S_S),                                    \
  QLF3(S_S,P_M,S_S),                                    \
  QLF3(S_D,P_Z,S_D),                                    \
  QLF3(S_D,P_M,S_D),                                    \
}
#define OP_SVE_VRR_BHSD                                 \
{                                                       \
  QLF3(S_B,W,W),                                        \
  QLF3(S_H,W,W),                                        \
  QLF3(S_S,W,W),                                        \
  QLF3(S_D,X,X),                                        \
}
#define OP_SVE_VRU_BHSD                                 \
{                                                       \
  QLF3(S_B,W,NIL),                                      \
  QLF3(S_H,W,NIL),                                      \
  QLF3(S_S,W,NIL),                                      \
  QLF3(S_D,X,NIL),                                      \
}
#define OP_SVE_VR_BHSD                                  \
{                                                       \
  QLF2(S_B,W),                                          \
  QLF2(S_H,W),                                          \
  QLF2(S_S,W),                                          \
  QLF2(S_D,X),                                          \
}
#define OP_SVE_VUR_BHSD                                 \
{                                                       \
  QLF3(S_B,NIL,W),                                      \
  QLF3(S_H,NIL,W),                                      \
  QLF3(S_S,NIL,W),                                      \
  QLF3(S_D,NIL,X),                                      \
}
#define OP_SVE_VUU_BHSD                                 \
{                                                       \
  QLF3(S_B,NIL,NIL),                                    \
  QLF3(S_H,NIL,NIL),                                    \
  QLF3(S_S,NIL,NIL),                                    \
  QLF3(S_D,NIL,NIL),                                    \
}
#define OP_SVE_VUVV_BHSD                                \
{                                                       \
  QLF4(S_B,NIL,S_B,S_B),                                \
  QLF4(S_H,NIL,S_H,S_H),                                \
  QLF4(S_S,NIL,S_S,S_S),                                \
  QLF4(S_D,NIL,S_D,S_D),                                \
}
#define OP_SVE_VUVV_HSD                                 \
{                                                       \
  QLF4(S_H,NIL,S_H,S_H),                                \
  QLF4(S_S,NIL,S_S,S_S),                                \
  QLF4(S_D,NIL,S_D,S_D),                                \
}
#define OP_SVE_VUV_BHSD                                 \
{                                                       \
  QLF3(S_B,NIL,S_B),                                    \
  QLF3(S_H,NIL,S_H),                                    \
  QLF3(S_S,NIL,S_S),                                    \
  QLF3(S_D,NIL,S_D),                                    \
}
#define OP_SVE_VUV_HSD                                  \
{                                                       \
  QLF3(S_H,NIL,S_H),                                    \
  QLF3(S_S,NIL,S_S),                                    \
  QLF3(S_D,NIL,S_D),                                    \
}
#define OP_SVE_VUV_SD                                   \
{                                                       \
  QLF3(S_S,NIL,S_S),                                    \
  QLF3(S_D,NIL,S_D),                                    \
}
#define OP_SVE_VU_BHSD                                  \
{                                                       \
  QLF2(S_B,NIL),                                        \
  QLF2(S_H,NIL),                                        \
  QLF2(S_S,NIL),                                        \
  QLF2(S_D,NIL),                                        \
}
#define OP_SVE_VU_HSD                                   \
{                                                       \
  QLF2(S_H,NIL),                                        \
  QLF2(S_S,NIL),                                        \
  QLF2(S_D,NIL),                                        \
}
#define OP_SVE_VU_HSD                                   \
{                                                       \
  QLF2(S_H,NIL),                                        \
  QLF2(S_S,NIL),                                        \
  QLF2(S_D,NIL),                                        \
}
#define OP_SVE_Vv_HSD                                   \
{                                                       \
  QLF2(S_H,S_H),                                        \
  QLF2(S_S,S_S),                                        \
  QLF2(S_D,S_D),                                        \
  QLF2(S_H,NIL),                                        \
  QLF2(S_S,NIL),                                        \
  QLF2(S_D,NIL),                                        \
}
#define OP_SVE_VVD_BHS                                  \
{                                                       \
  QLF3(S_B,S_B,S_D),                                    \
  QLF3(S_H,S_H,S_D),                                    \
  QLF3(S_S,S_S,S_D),                                    \
}
#define OP_SVE_VVU_BHSD                                 \
{                                                       \
  QLF3(S_B,S_B,NIL),                                    \
  QLF3(S_H,S_H,NIL),                                    \
  QLF3(S_S,S_S,NIL),                                    \
  QLF3(S_D,S_D,NIL),                                    \
}
#define OP_SVE_VVVU_H                                   \
{                                                       \
  QLF4(S_H,S_H,S_H,NIL),                                \
}
#define OP_SVE_VVVU_S                                   \
{                                                       \
  QLF4(S_S,S_S,S_S,NIL),                                \
}
#define OP_SVE_VVVU_SD_BH                               \
{                                                       \
  QLF4(S_S,S_B,S_B,NIL),                                \
  QLF4(S_D,S_H,S_H,NIL),                                \
}
#define OP_SVE_VVVU_HSD                                 \
{                                                       \
  QLF4(S_H,S_H,S_H,NIL),                                \
  QLF4(S_S,S_S,S_S,NIL),                                \
  QLF4(S_D,S_D,S_D,NIL),                                \
}
#define OP_SVE_VVVU_BHSD                                \
{                                                       \
  QLF4(S_B,S_B,S_B,NIL),                                \
  QLF4(S_H,S_H,S_H,NIL),                                \
  QLF4(S_S,S_S,S_S,NIL),                                \
  QLF4(S_D,S_D,S_D,NIL),                                \
}
#define OP_SVE_VVV_BHSD                                 \
{                                                       \
  QLF3(S_B,S_B,S_B),                                    \
  QLF3(S_H,S_H,S_H),                                    \
  QLF3(S_S,S_S,S_S),                                    \
  QLF3(S_D,S_D,S_D),                                    \
}
#define OP_SVE_VVV_D                                    \
{                                                       \
  QLF3(S_D,S_D,S_D),                                    \
}
#define OP_SVE_VVV_D_H                                  \
{                                                       \
  QLF3(S_D,S_H,S_H),                                    \
}
#define OP_SVE_VVV_H                                    \
{                                                       \
  QLF3(S_H,S_H,S_H),                                    \
}
#define OP_SVE_VVV_HSD                                  \
{                                                       \
  QLF3(S_H,S_H,S_H),                                    \
  QLF3(S_S,S_S,S_S),                                    \
  QLF3(S_D,S_D,S_D),                                    \
}
#define OP_SVE_VVV_S                                    \
{                                                       \
  QLF3(S_S,S_S,S_S),                                    \
}
#define OP_SVE_VVV_HD_BS				\
{                                                       \
  QLF3(S_H,S_B,S_B),                                    \
  QLF3(S_D,S_S,S_S),                                    \
}
#define OP_SVE_VVV_S_B                                  \
{                                                       \
  QLF3(S_S,S_B,S_B),                                    \
}
#define OP_SVE_VVV_Q_D					\
{                                                       \
  QLF3(S_Q,S_D,S_D),                                    \
}
#define OP_SVE_VVV_HSD_BHS                              \
{                                                       \
  QLF3(S_H,S_B,S_B),                                    \
  QLF3(S_S,S_H,S_H),                                    \
  QLF3(S_D,S_S,S_S),                                    \
}
#define OP_SVE_VVV_HSD_BHS2                             \
{                                                       \
  QLF3(S_H,S_H,S_B),                                    \
  QLF3(S_S,S_S,S_H),                                    \
  QLF3(S_D,S_D,S_S),                                    \
}
#define OP_SVE_VVV_BHS_HSD                              \
{                                                       \
  QLF3(S_B,S_H,S_H),                                    \
  QLF3(S_H,S_S,S_S),                                    \
  QLF3(S_S,S_D,S_D),                                    \
}
#define OP_SVE_VV_BHS_HSD                               \
{                                                       \
  QLF2(S_B,S_H),                                        \
  QLF2(S_H,S_S),                                        \
  QLF2(S_S,S_D),                                        \
}
#define OP_SVE_VVV_SD_BH                                \
{                                                       \
  QLF3(S_S,S_B,S_B),                                    \
  QLF3(S_D,S_H,S_H),                                    \
}
#define OP_SVE_VVV_SD                                   \
{                                                       \
  QLF3(S_S,S_S,S_S),                                    \
  QLF3(S_D,S_D,S_D),                                    \
}
#define OP_SVE_VV_BHSD                                  \
{                                                       \
  QLF2(S_B,S_B),                                        \
  QLF2(S_H,S_H),                                        \
  QLF2(S_S,S_S),                                        \
  QLF2(S_D,S_D),                                        \
}
#define OP_SVE_VV_BHSDQ                                 \
{                                                       \
  QLF2(S_B,S_B),                                        \
  QLF2(S_H,S_H),                                        \
  QLF2(S_S,S_S),                                        \
  QLF2(S_D,S_D),                                        \
  QLF2(S_Q,S_Q),                                        \
}
#define OP_SVE_VV_HSD                                   \
{                                                       \
  QLF2(S_H,S_H),                                        \
  QLF2(S_S,S_S),                                        \
  QLF2(S_D,S_D),                                        \
}
#define OP_SVE_VVU_BHS_HSD                               \
{                                                       \
  QLF3(S_B,S_H,NIL),                                        \
  QLF3(S_H,S_S,NIL),                                        \
  QLF3(S_S,S_D,NIL),                                        \
}
#define OP_SVE_VV_HSD_BHS                               \
{                                                       \
  QLF2(S_H,S_B),                                        \
  QLF2(S_S,S_H),                                        \
  QLF2(S_D,S_S),                                        \
}
#define OP_SVE_VV_SD                                    \
{                                                       \
  QLF2(S_S,S_S),                                        \
  QLF2(S_D,S_D),                                        \
}
#define OP_SVE_VWW_BHSD                                 \
{                                                       \
  QLF3(S_B,W,W),                                        \
  QLF3(S_H,W,W),                                        \
  QLF3(S_S,W,W),                                        \
  QLF3(S_D,W,W),                                        \
}
#define OP_SVE_VXX_BHSD                                 \
{                                                       \
  QLF3(S_B,X,X),                                        \
  QLF3(S_H,X,X),                                        \
  QLF3(S_S,X,X),                                        \
  QLF3(S_D,X,X),                                        \
}
#define OP_SVE_VZVD_BHS                                 \
{                                                       \
  QLF4(S_B,P_Z,S_B,S_D),                                \
  QLF4(S_H,P_Z,S_H,S_D),                                \
  QLF4(S_S,P_Z,S_S,S_D),                                \
}
#define OP_SVE_VZVU_BHSD                                \
{                                                       \
  QLF4(S_B,P_Z,S_B,NIL),                                \
  QLF4(S_H,P_Z,S_H,NIL),                                \
  QLF4(S_S,P_Z,S_S,NIL),                                \
  QLF4(S_D,P_Z,S_D,NIL),                                \
}
#define OP_SVE_VZVV_BHSD                                \
{                                                       \
  QLF4(S_B,P_Z,S_B,S_B),                                \
  QLF4(S_H,P_Z,S_H,S_H),                                \
  QLF4(S_S,P_Z,S_S,S_S),                                \
  QLF4(S_D,P_Z,S_D,S_D),                                \
}
#define OP_SVE_VZVV_HSD                                 \
{                                                       \
  QLF4(S_H,P_Z,S_H,S_H),                                \
  QLF4(S_S,P_Z,S_S,S_S),                                \
  QLF4(S_D,P_Z,S_D,S_D),                                \
}
#define OP_SVE_VZVV_SD                                 \
{                                                       \
  QLF4(S_S,P_Z,S_S,S_S),                                \
  QLF4(S_D,P_Z,S_D,S_D),                                \
}
#define OP_SVE_VZVV_BH                                 \
{                                                       \
  QLF4(S_B,P_Z,S_B,S_B),                                \
  QLF4(S_H,P_Z,S_H,S_H),                                \
}
#define OP_SVE_VZV_SD                                   \
{                                                       \
  QLF3(S_S,P_Z,S_S),                                    \
  QLF3(S_D,P_Z,S_D),                                    \
}
#define OP_SVE_VZV_HSD                                  \
{                                                       \
  QLF3(S_H,P_Z,S_H),                                    \
  QLF3(S_S,P_Z,S_S),                                    \
  QLF3(S_D,P_Z,S_D),                                    \
}
#define OP_SVE_V_HSD                                    \
{                                                       \
  QLF1(S_H),                                            \
  QLF1(S_S),                                            \
  QLF1(S_D),                                            \
}
#define OP_SVE_WU                                       \
{                                                       \
  QLF2(W,NIL),                                          \
}
#define OP_SVE_WV_BHSD                                  \
{                                                       \
  QLF2(W,S_B),                                          \
  QLF2(W,S_H),                                          \
  QLF2(W,S_S),                                          \
  QLF2(W,S_D),                                          \
}
#define OP_SVE_XU                                       \
{                                                       \
  QLF2(X,NIL),                                          \
}
#define OP_SVE_XUV_BHSD                                 \
{                                                       \
  QLF3(X,NIL,S_B),                                      \
  QLF3(X,NIL,S_H),                                      \
  QLF3(X,NIL,S_S),                                      \
  QLF3(X,NIL,S_D),                                      \
}
#define OP_SVE_XVW_BHSD                                 \
{                                                       \
  QLF3(X,S_B,W),                                        \
  QLF3(X,S_H,W),                                        \
  QLF3(X,S_S,W),                                        \
  QLF3(X,S_D,W),                                        \
}
#define OP_SVE_XV_BHSD                                  \
{                                                       \
  QLF2(X,S_B),                                          \
  QLF2(X,S_H),                                          \
  QLF2(X,S_S),                                          \
  QLF2(X,S_D),                                          \
}
#define OP_SVE_XWU                                      \
{                                                       \
  QLF3(X,W,NIL),                                        \
}
#define OP_SVE_XXU                                      \
{                                                       \
  QLF3(X,X,NIL),                                        \
}
/* e.g. ADDVA <ZAda>.S, <Pn>/M, <Pm>/M, <Zn>.S  */
#define OP_SME_ZADA_PN_PM_ZN_S                          \
{                                                       \
  QLF4(S_S,P_M,P_M,S_S),                                \
}
/* e.g. ADDVA <ZAda>.D, <Pn>/M, <Pm>/M, <Zn>.D  */
#define OP_SME_ZADA_PN_PM_ZN_D                          \
{                                                       \
  QLF4(S_D,P_M,P_M,S_D),                                \
}
/* e.g. BFMOPA <ZAda>.S, <Pn>/M, <Pm>/M, <Zn>.H, <Zm>.H  */
#define OP_SME_ZADA_PN_PM_ZN_ZM                         \
{                                                       \
  QLF5(S_S,P_M,P_M,S_H,S_H),                            \
}
#define OP_SME_ZADA_S_PM_PM_S_S                         \
{                                                       \
  QLF5(S_S,P_M,P_M,S_S,S_S)                             \
}
#define OP_SME_ZADA_D_PM_PM_D_D                         \
{                                                       \
  QLF5(S_D,P_M,P_M,S_D,S_D)                             \
}
#define OP_SME_ZADA_S_PM_PM_H_H                         \
{                                                       \
  QLF5(S_S,P_M,P_M,S_H,S_H)                             \
}
#define OP_SME_ZADA_S_PM_PM_B_B                         \
{                                                       \
  QLF5(S_S,P_M,P_M,S_B,S_B)                             \
}
#define OP_SME_ZADA_D_PM_PM_H_H                         \
{                                                       \
  QLF5(S_D,P_M,P_M,S_H,S_H)                             \
}
#define OP_SME_BHSDQ_PM_BHSDQ                           \
{                                                       \
  QLF3(S_B,P_M,S_B),                                    \
  QLF3(S_H,P_M,S_H),                                    \
  QLF3(S_S,P_M,S_S),                                    \
  QLF3(S_D,P_M,S_D),                                    \
  QLF3(S_Q,P_M,S_Q)                                     \
}

/* e.g. UDOT <Vd>.2S, <Vn>.8B, <Vm>.8B.  */
#define QL_V3DOT	   \
{			   \
  QLF3(V_2S, V_8B,  V_8B), \
  QLF3(V_4S, V_16B, V_16B),\
}

/* e.g. UDOT <Vd>.2S, <Vn>.8B, <Vm>.4B[<index>].  */
#define QL_V2DOT	 \
{			 \
  QLF3(V_2S, V_8B,  S_4B),\
  QLF3(V_4S, V_16B, S_4B),\
}

/* e.g. SHA512H <Qd>, <Qn>, <Vm>.2D.  */
#define QL_SHA512UPT			\
{				\
  QLF3(S_Q, S_Q, V_2D),		\
}

/* e.g. SHA512SU0 <Vd.2D>, <Vn>.2D.  */
#define QL_V2SAME2D		\
{				\
  QLF2(V_2D, V_2D),		\
}

/* e.g. SHA512SU1 <Vd>.2D, <Vn>.2D, <Vm>.2D>.  */
#define QL_V3SAME2D		\
{				\
  QLF3(V_2D, V_2D, V_2D),	\
}

/* e.g. EOR3 <Vd>.16B, <Vn>.16B, <Vm>.16B, <Va>.16B.  */
#define QL_V4SAME16B			\
{					\
  QLF4(V_16B, V_16B, V_16B, V_16B),	\
}

/* e.g. SM3SS1 <Vd>.4S, <Vn>.4S, <Vm>.4S, <Va>.4S.  */
#define QL_V4SAME4S			\
{					\
  QLF4(V_4S, V_4S, V_4S, V_4S),		\
}

/* e.g. XAR <Vd>.2D, <Vn>.2D, <Vm>.2D, #<imm6>.  */
#define QL_XAR			\
{				\
  QLF4(V_2D, V_2D, V_2D, imm_0_63),	\
}

/* e.g. SM3TT1A <Vd>.4S, <Vn>.4S, <Vm>.S[<imm2>].  */
#define QL_SM3TT	\
{			\
  QLF3(V_4S, V_4S, S_S),\
}

/* e.g. FMLAL  <Vd>.2S, <Vn>.2H, <Vm>.2H.  */
#define QL_V3FML2S \
{		   \
  QLF3(V_2S, V_2H, V_2H),\
}

/* e.g. FMLAL  <Vd>.4S, <Vn>.4H, <Vm>.4H.  */
#define QL_V3FML4S \
{		   \
  QLF3(V_4S, V_4H, V_4H),\
}

/* e.g. FMLAL  <Vd>.2S, <Vn>.2H, <Vm>.H[<index>].  */
#define QL_V2FML2S \
{		   \
  QLF3(V_2S, V_2H, S_H),\
}

/* e.g. FMLAL  <Vd>.4S, <Vn>.4H, <Vm>.H[<index>].  */
#define QL_V2FML4S \
{		   \
  QLF3(V_4S, V_4H, S_H),\
}

/* e.g. RMIF <Xn>, #<shift>, #<mask>.  */
#define QL_RMIF  \
{		  \
  QLF3(X, imm_0_63, imm_0_15),\
}

/* e.g. SETF8 <Wn>.  */
#define QL_SETF \
{		\
  QLF1(W),	\
}

/* e.g. STLURB <Wt>, [<Xn|SP>{,#<simm>}].  */
#define QL_STLW \
{		\
  QLF2(W, NIL),	\
}

/* e.g. STLURB <Xt>, [<Xn|SP>{,#<simm>}].  */
#define QL_STLX \
{		\
  QLF2(X, NIL),	\
}

/* e.g. BFDOT <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb> */
#define QL_BFDOT64    \
{		      \
  QLF3(V_2S, V_4H, V_4H),\
  QLF3(V_4S, V_8H, V_8H),\
}

/* e.g. BFDOT <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.2H[<index>] */
#define QL_BFDOT64I    \
{		      \
  QLF3(V_2S, V_4H, S_2H),\
  QLF3(V_4S, V_8H, S_2H),\
}

/* e.g. SMMLA <Vd>.4S, <Vn>.16B, <Vm>.16B */
#define QL_MMLA64      \
{		      \
  QLF3(V_4S, V_16B, V_16B),\
}

/* e.g. BFMMLA <Vd>.4s, <Vn>.8h, <Vm>.8h */
#define QL_BFMMLA    \
{		      \
  QLF3(V_4S, V_8H, V_8H),\
}

/* e.g. BFCVT <Hd>, <Sn> */
#define QL_BFCVT64      \
{		      \
  QLF2(S_H,S_S),  \
}

/* e.g. BFCVT <Hd>, <Sn> */
#define QL_BFCVTN64      \
{		      \
  QLF2(V_4H,V_4S),  \
}

/* e.g. BFCVT <Hd>, <Sn> */
#define QL_BFCVTN2_64      \
{		      \
  QLF2(V_8H,V_4S),  \
}

/* e.g. BFMLAL2 <Vd>.4s, <Vn>.8h, <Vm>.H[<index>] */
#define QL_V3BFML4S      \
{		      \
  QLF3(V_4S, V_8H, S_H),	\
}

/* Opcode table.  */

static const aarch64_feature_set aarch64_feature_v8 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8, 0);
static const aarch64_feature_set aarch64_feature_fp =
  AARCH64_FEATURE (AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_simd =
  AARCH64_FEATURE (AARCH64_FEATURE_SIMD, 0);
static const aarch64_feature_set aarch64_feature_crc =
  AARCH64_FEATURE (AARCH64_FEATURE_CRC, 0);
static const aarch64_feature_set aarch64_feature_lse =
  AARCH64_FEATURE (AARCH64_FEATURE_LSE, 0);
static const aarch64_feature_set aarch64_feature_lor =
  AARCH64_FEATURE (AARCH64_FEATURE_LOR, 0);
static const aarch64_feature_set aarch64_feature_rdma =
  AARCH64_FEATURE (AARCH64_FEATURE_RDMA, 0);
static const aarch64_feature_set aarch64_feature_v8_2 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2, 0);
static const aarch64_feature_set aarch64_feature_fp_f16 =
  AARCH64_FEATURE (AARCH64_FEATURE_F16 | AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_simd_f16 =
  AARCH64_FEATURE (AARCH64_FEATURE_F16 | AARCH64_FEATURE_SIMD, 0);
static const aarch64_feature_set aarch64_feature_sve =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE, 0);
static const aarch64_feature_set aarch64_feature_v8_3 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_3, 0);
static const aarch64_feature_set aarch64_feature_fp_v8_3 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_3 | AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_pac =
  AARCH64_FEATURE (AARCH64_FEATURE_PAC, 0);
static const aarch64_feature_set aarch64_feature_compnum =
  AARCH64_FEATURE (AARCH64_FEATURE_COMPNUM, 0);
static const aarch64_feature_set aarch64_feature_rcpc =
  AARCH64_FEATURE (AARCH64_FEATURE_RCPC, 0);
static const aarch64_feature_set aarch64_feature_dotprod =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_DOTPROD, 0);
static const aarch64_feature_set aarch64_feature_sha2 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8 | AARCH64_FEATURE_SHA2, 0);
static const aarch64_feature_set aarch64_feature_aes =
  AARCH64_FEATURE (AARCH64_FEATURE_V8 | AARCH64_FEATURE_AES, 0);
static const aarch64_feature_set aarch64_feature_v8_4 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_4, 0);
static const aarch64_feature_set aarch64_feature_sm4 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_SM4
		   | AARCH64_FEATURE_SIMD | AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_sha3 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_SHA2
		   | AARCH64_FEATURE_SHA3 | AARCH64_FEATURE_SIMD | AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_fp_16_v8_2 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_F16_FML
		   | AARCH64_FEATURE_F16 | AARCH64_FEATURE_FP, 0);
static const aarch64_feature_set aarch64_feature_v8_5 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_5, 0);
static const aarch64_feature_set aarch64_feature_flagmanip =
  AARCH64_FEATURE (AARCH64_FEATURE_FLAGMANIP, 0);
static const aarch64_feature_set aarch64_feature_frintts =
  AARCH64_FEATURE (AARCH64_FEATURE_FRINTTS, 0);
static const aarch64_feature_set aarch64_feature_sb =
  AARCH64_FEATURE (AARCH64_FEATURE_SB, 0);
static const aarch64_feature_set aarch64_feature_predres =
  AARCH64_FEATURE (AARCH64_FEATURE_PREDRES, 0);
static const aarch64_feature_set aarch64_feature_memtag =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_5 | AARCH64_FEATURE_MEMTAG, 0);
static const aarch64_feature_set aarch64_feature_bfloat16 =
  AARCH64_FEATURE (AARCH64_FEATURE_BFLOAT16, 0);
static const aarch64_feature_set aarch64_feature_bfloat16_sve =
  AARCH64_FEATURE (AARCH64_FEATURE_BFLOAT16 | AARCH64_FEATURE_SVE, 0);
static const aarch64_feature_set aarch64_feature_tme =
  AARCH64_FEATURE (AARCH64_FEATURE_TME, 0);
static const aarch64_feature_set aarch64_feature_sve2 =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2, 0);
static const aarch64_feature_set aarch64_feature_sve2aes =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SVE2_AES, 0);
static const aarch64_feature_set aarch64_feature_sve2sha3 =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SVE2_SHA3, 0);
static const aarch64_feature_set aarch64_feature_sve2sm4 =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SVE2_SM4, 0);
static const aarch64_feature_set aarch64_feature_sve2bitperm =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SVE2_BITPERM, 0);
static const aarch64_feature_set aarch64_feature_sme =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SME, 0);
static const aarch64_feature_set aarch64_feature_sme_f64 =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SME
       | AARCH64_FEATURE_SME_F64, 0);
static const aarch64_feature_set aarch64_feature_sme_i64 =
  AARCH64_FEATURE (AARCH64_FEATURE_SVE2 | AARCH64_FEATURE_SME
       | AARCH64_FEATURE_SME_I64, 0);
static const aarch64_feature_set aarch64_feature_v8_6 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_6, 0);
static const aarch64_feature_set aarch64_feature_v8_7 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_7, 0);
static const aarch64_feature_set aarch64_feature_i8mm =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_I8MM, 0);
static const aarch64_feature_set aarch64_feature_i8mm_sve =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_I8MM
       | AARCH64_FEATURE_SVE, 0);
static const aarch64_feature_set aarch64_feature_f32mm_sve =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_F32MM
       | AARCH64_FEATURE_SVE, 0);
static const aarch64_feature_set aarch64_feature_f64mm_sve =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_2 | AARCH64_FEATURE_F64MM
       | AARCH64_FEATURE_SVE, 0);
static const aarch64_feature_set aarch64_feature_v8_r =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_R, 0);
static const aarch64_feature_set aarch64_feature_ls64 =
  AARCH64_FEATURE (AARCH64_FEATURE_V8_6 | AARCH64_FEATURE_LS64, 0);
static const aarch64_feature_set aarch64_feature_flagm =
  AARCH64_FEATURE (AARCH64_FEATURE_FLAGM, 0);
static const aarch64_feature_set aarch64_feature_mops =
  AARCH64_FEATURE (AARCH64_FEATURE_MOPS, 0);
static const aarch64_feature_set aarch64_feature_mops_memtag =
  AARCH64_FEATURE (AARCH64_FEATURE_MOPS | AARCH64_FEATURE_MEMTAG, 0);
static const aarch64_feature_set aarch64_feature_hbc =
  AARCH64_FEATURE (AARCH64_FEATURE_HBC, 0);
static const aarch64_feature_set aarch64_feature_cssc =
  AARCH64_FEATURE (AARCH64_FEATURE_CSSC, 0);

#define CORE		&aarch64_feature_v8
#define FP		&aarch64_feature_fp
#define SIMD		&aarch64_feature_simd
#define CRC		&aarch64_feature_crc
#define LSE		&aarch64_feature_lse
#define LOR		&aarch64_feature_lor
#define RDMA		&aarch64_feature_rdma
#define FP_F16		&aarch64_feature_fp_f16
#define SIMD_F16	&aarch64_feature_simd_f16
#define ARMV8_2		&aarch64_feature_v8_2
#define SVE		&aarch64_feature_sve
#define ARMV8_3		&aarch64_feature_v8_3
#define FP_V8_3		&aarch64_feature_fp_v8_3
#define PAC		&aarch64_feature_pac
#define COMPNUM		&aarch64_feature_compnum
#define RCPC		&aarch64_feature_rcpc
#define SHA2		&aarch64_feature_sha2
#define AES		&aarch64_feature_aes
#define ARMV8_4		&aarch64_feature_v8_4
#define SHA3		&aarch64_feature_sha3
#define SM4		&aarch64_feature_sm4
#define FP_F16_V8_2	&aarch64_feature_fp_16_v8_2
#define DOTPROD		&aarch64_feature_dotprod
#define ARMV8_5		&aarch64_feature_v8_5
#define FLAGMANIP	&aarch64_feature_flagmanip
#define FRINTTS		&aarch64_feature_frintts
#define SB		&aarch64_feature_sb
#define PREDRES		&aarch64_feature_predres
#define MEMTAG		&aarch64_feature_memtag
#define TME		&aarch64_feature_tme
#define SVE2		&aarch64_feature_sve2
#define SVE2_AES		&aarch64_feature_sve2aes
#define SVE2_SHA3	&aarch64_feature_sve2sha3
#define SVE2_SM4		&aarch64_feature_sve2sm4
#define SVE2_BITPERM	&aarch64_feature_sve2bitperm
#define SME		&aarch64_feature_sme
#define SME_F64		&aarch64_feature_sme_f64
#define SME_I64		&aarch64_feature_sme_i64
#define ARMV8_6		&aarch64_feature_v8_6
#define ARMV8_6_SVE		&aarch64_feature_v8_6
#define BFLOAT16_SVE	&aarch64_feature_bfloat16_sve
#define BFLOAT16	&aarch64_feature_bfloat16
#define I8MM_SVE      &aarch64_feature_i8mm_sve
#define F32MM_SVE     &aarch64_feature_f32mm_sve
#define F64MM_SVE     &aarch64_feature_f64mm_sve
#define I8MM      &aarch64_feature_i8mm
#define ARMV8_R	  &aarch64_feature_v8_r
#define ARMV8_7	  &aarch64_feature_v8_7
#define LS64	  &aarch64_feature_ls64
#define FLAGM	  &aarch64_feature_flagm
#define MOPS	  &aarch64_feature_mops
#define MOPS_MEMTAG &aarch64_feature_mops_memtag
#define HBC	  &aarch64_feature_hbc
#define CSSC	  &aarch64_feature_cssc

#define CORE_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, CORE, OPS, QUALS, FLAGS, 0, 0, NULL }
#define __FP_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, FP, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SIMD_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, SIMD, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _SIMD_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,VERIFIER) \
  { NAME, OPCODE, MASK, CLASS, OP, SIMD, OPS, QUALS, FLAGS, 0, 0, VERIFIER }
#define _CRC_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, CRC, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _LSE_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, LSE, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _LOR_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, LOR, OPS, QUALS, FLAGS, 0, 0, NULL }
#define RDMA_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, RDMA, OPS, QUALS, FLAGS, 0, 0, NULL }
#define FF16_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, FP_F16, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SF16_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS)		\
  { NAME, OPCODE, MASK, CLASS, 0, SIMD_F16, OPS, QUALS, FLAGS, 0, 0, NULL }
#define V8_2_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, ARMV8_2, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _SVE_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define _SVE_INSNC(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,CONSTRAINTS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE, OPS, QUALS, \
    FLAGS | F_STRICT, CONSTRAINTS, TIED, NULL }
#define V8_3_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_3, OPS, QUALS, FLAGS, 0, 0, NULL }
#define PAC_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, PAC, OPS, QUALS, FLAGS, 0, 0, NULL }
#define CNUM_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, COMPNUM, OPS, QUALS, FLAGS, 0, 0, NULL }
#define RCPC_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, RCPC, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SHA2_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, SHA2, OPS, QUALS, FLAGS, 0, 0, NULL }
#define AES_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, AES, OPS, QUALS, FLAGS, 0, 0, NULL }
#define V8_4_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_4, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SHA3_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, SHA3, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SM4_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, SM4, OPS, QUALS, FLAGS, 0, 0, NULL }
#define FP16_V8_2_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, FP_F16_V8_2, OPS, QUALS, FLAGS, 0, 0, NULL }
#define DOT_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, DOTPROD, OPS, QUALS, FLAGS, 0, 0, NULL }
#define V8_5_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_5, OPS, QUALS, FLAGS, 0, 0, NULL }
#define FLAGMANIP_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, FLAGMANIP, OPS, QUALS, FLAGS, 0, 0, NULL }
#define FRINTTS_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, FRINTTS, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SB_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, SB, OPS, QUALS, FLAGS, 0, 0, NULL }
#define PREDRES_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, PREDRES, OPS, QUALS, FLAGS, 0, 0, NULL }
#define MEMTAG_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, MEMTAG, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _TME_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, OP, TME, OPS, QUALS, FLAGS, 0, 0, NULL }
#define SVE2_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define SVE2_INSNC(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,CONSTRAINTS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2, OPS, QUALS, \
    FLAGS | F_STRICT, CONSTRAINTS, TIED, NULL }
#define SVE2AES_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2_AES, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define SVE2SHA3_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2_SHA3, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define SVE2SM4_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2_SM4, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define SVE2SM4_INSNC(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,CONSTRAINTS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2_SM4, OPS, QUALS, \
    FLAGS | F_STRICT, CONSTRAINTS, TIED, NULL }
#define SME_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SME, OPS, QUALS, \
    FLAGS, 0, TIED, NULL }
#define SME_F64_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SME_F64, OPS, QUALS, \
    FLAGS, 0, TIED, NULL }
#define SME_I64_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SME_I64, OPS, QUALS, \
    FLAGS, 0, TIED, NULL }
#define SME_INSNC(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,CONSTRAINTS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SME, OPS, QUALS, \
    FLAGS, CONSTRAINTS, TIED, NULL }
#define SVE2BITPERM_INSN(NAME,OPCODE,MASK,CLASS,OP,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, OP, SVE2_BITPERM, OPS, QUALS, \
    FLAGS | F_STRICT, 0, TIED, NULL }
#define V8_6_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_6, OPS, QUALS, FLAGS, 0, 0, NULL }
#define BFLOAT16_SVE_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, BFLOAT16_SVE, OPS, QUALS, FLAGS, 0, 0, NULL }
#define BFLOAT16_SVE_INSNC(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS, CONSTRAINTS, TIED) \
  { NAME, OPCODE, MASK, CLASS, 0, BFLOAT16_SVE, OPS, QUALS, FLAGS | F_STRICT, \
    CONSTRAINTS, TIED, NULL }
#define BFLOAT16_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, BFLOAT16, OPS, QUALS, FLAGS, 0, 0, NULL }
#define INT8MATMUL_SVE_INSNC(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS, CONSTRAINTS, TIED) \
  { NAME, OPCODE, MASK, CLASS, 0, I8MM_SVE, OPS, QUALS, FLAGS, CONSTRAINTS, TIED, NULL }
#define INT8MATMUL_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, I8MM, OPS, QUALS, FLAGS, 0, 0, NULL }
#define F64MATMUL_SVE_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS,TIED) \
  { NAME, OPCODE, MASK, CLASS, 0, F64MM_SVE, OPS, QUALS, FLAGS, 0, TIED, NULL }
#define F64MATMUL_SVE_INSNC(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS, CONSTRAINTS, TIED) \
  { NAME, OPCODE, MASK, CLASS, 0, F64MM_SVE, OPS, QUALS, FLAGS, CONSTRAINTS, TIED, NULL }
#define F32MATMUL_SVE_INSNC(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS, CONSTRAINTS, TIED) \
  { NAME, OPCODE, MASK, CLASS, 0, F32MM_SVE, OPS, QUALS, FLAGS, CONSTRAINTS, TIED, NULL }
#define V8_R_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_R, OPS, QUALS, FLAGS, 0, 0, NULL }
#define V8_7_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, ARMV8_7, OPS, QUALS, FLAGS, 0, 0, NULL }
#define _LS64_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, LS64, OPS, QUALS, FLAGS, 0, 0, NULL }
#define FLAGM_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, FLAGM, OPS, QUALS, FLAGS, 0, 0, NULL }
#define MOPS_INSN(NAME, OPCODE, MASK, CLASS, OPS, QUALS, FLAGS, CONSTRAINTS, VERIFIER) \
  { NAME, OPCODE, MASK, CLASS, 0, MOPS, OPS, QUALS, FLAGS, CONSTRAINTS, \
    0, VERIFIER }
#define MOPS_MEMTAG_INSN(NAME, OPCODE, MASK, CLASS, OPS, QUALS, FLAGS, CONSTRAINTS, VERIFIER) \
  { NAME, OPCODE, MASK, CLASS, 0, MOPS_MEMTAG, OPS, QUALS, FLAGS, \
    CONSTRAINTS, 0, VERIFIER }
#define HBC_INSN(NAME,OPCODE,MASK,CLASS,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, CLASS, 0, HBC, OPS, QUALS, FLAGS, 0, 0, NULL }
#define CSSC_INSN(NAME,OPCODE,MASK,OPS,QUALS,FLAGS) \
  { NAME, OPCODE, MASK, cssc, 0, CSSC, OPS, QUALS, FLAGS, 0, 0, NULL }

#define MOPS_CPY_OP1_OP2_PME_INSN(NAME, OPCODE, MASK, FLAGS, CONSTRAINTS) \
  MOPS_INSN (NAME, OPCODE, MASK, 0, \
	     OP3 (MOPS_ADDR_Rd, MOPS_ADDR_Rs, MOPS_WB_Rn), QL_I3SAMEX, \
	     FLAGS, CONSTRAINTS, VERIFIER (three_different_regs))

/* These instructions must remain consecutive, since we rely on the order
   when detecting invalid sequences.  */
#define MOPS_CPY_OP1_OP2_INSN(NAME, SUFFIX, OPCODE, MASK) \
  MOPS_CPY_OP1_OP2_PME_INSN (NAME "p" SUFFIX, OPCODE, MASK, F_SCAN, \
			     C_SCAN_MOPS_P), \
  MOPS_CPY_OP1_OP2_PME_INSN (NAME "m" SUFFIX, OPCODE | 0x400000, MASK, \
			     0, C_SCAN_MOPS_M), \
  MOPS_CPY_OP1_OP2_PME_INSN (NAME "e" SUFFIX, OPCODE | 0x800000, MASK, \
			     0, C_SCAN_MOPS_E)

#define MOPS_CPY_OP1_INSN(NAME, SUFFIX, OPCODE, MASK) \
  MOPS_CPY_OP1_OP2_INSN (NAME, SUFFIX, OPCODE, MASK), \
  MOPS_CPY_OP1_OP2_INSN (NAME, SUFFIX "wn", OPCODE | 0x4000, MASK), \
  MOPS_CPY_OP1_OP2_INSN (NAME, SUFFIX "rn", OPCODE | 0x8000, MASK), \
  MOPS_CPY_OP1_OP2_INSN (NAME, SUFFIX "n", OPCODE | 0xc000, MASK)

#define MOPS_CPY_INSN(NAME, OPCODE, MASK) \
  MOPS_CPY_OP1_INSN (NAME, "", OPCODE, MASK), \
  MOPS_CPY_OP1_INSN (NAME, "wt", OPCODE | 0x1000, MASK), \
  MOPS_CPY_OP1_INSN (NAME, "rt", OPCODE | 0x2000, MASK), \
  MOPS_CPY_OP1_INSN (NAME, "t", OPCODE | 0x3000, MASK)

#define MOPS_SET_OP1_OP2_PME_INSN(NAME, OPCODE, MASK, FLAGS, CONSTRAINTS, ISA) \
  ISA (NAME, OPCODE, MASK, 0, \
       OP3 (MOPS_ADDR_Rd, MOPS_WB_Rn, Rm), QL_I3SAMEX, FLAGS, \
       CONSTRAINTS, VERIFIER (three_different_regs))

/* These instructions must remain consecutive, since we rely on the order
   when detecting invalid sequences.  */
#define MOPS_SET_OP1_OP2_INSN(NAME, SUFFIX, OPCODE, MASK, ISA) \
  MOPS_SET_OP1_OP2_PME_INSN (NAME "p" SUFFIX, OPCODE, MASK, \
			     F_SCAN, C_SCAN_MOPS_P, ISA), \
  MOPS_SET_OP1_OP2_PME_INSN (NAME "m" SUFFIX, OPCODE | 0x4000, MASK, \
			     0, C_SCAN_MOPS_M, ISA), \
  MOPS_SET_OP1_OP2_PME_INSN (NAME "e" SUFFIX, OPCODE | 0x8000, MASK, \
			     0, C_SCAN_MOPS_E, ISA)

#define MOPS_SET_INSN(NAME, OPCODE, MASK, ISA) \
  MOPS_SET_OP1_OP2_INSN (NAME, "", OPCODE, MASK, ISA), \
  MOPS_SET_OP1_OP2_INSN (NAME, "t", OPCODE | 0x1000, MASK, ISA), \
  MOPS_SET_OP1_OP2_INSN (NAME, "n", OPCODE | 0x2000, MASK, ISA), \
  MOPS_SET_OP1_OP2_INSN (NAME, "tn", OPCODE | 0x3000, MASK, ISA)

const struct aarch64_opcode aarch64_opcode_table[] =
{
  CORE_INSN ("adds", 0x2b200000, 0x7fe00000, addsub_ext, 0, OP3 (Rd, Rn_SP, Rm_EXT),    QL_I3_EXT, F_HAS_ALIAS | F_SF),
  CORE_INSN ("subs", 0x6b200000, 0x7fe00000, addsub_ext, 0, OP3 (Rd, Rn_SP, Rm_EXT),    QL_I3_EXT, F_HAS_ALIAS | F_SF),
  CORE_INSN ("cmp",  0x6b20001f, 0x7fe0001f, addsub_ext, 0, OP2 (Rn_SP, Rm_EXT),        QL_I2_EXT, F_ALIAS | F_SF),
  CORE_INSN ("adds", 0x31000000, 0x7f000000, addsub_imm, 0, OP3 (Rd, Rn_SP, AIMM),    QL_R2NIL, F_HAS_ALIAS | F_SF),
  CORE_INSN ("subs", 0x71000000, 0x7f000000, addsub_imm, 0, OP3 (Rd, Rn_SP, AIMM),    QL_R2NIL, F_HAS_ALIAS | F_SF),
  CORE_INSN ("cmp",  0x7100001f, 0x7f00001f, addsub_imm, 0, OP2 (Rn_SP, AIMM),        QL_R1NIL, F_ALIAS | F_SF),
  CORE_INSN ("adds", 0x2b000000, 0x7f200000, addsub_shift, 0, OP3 (Rd, Rn, Rm_SFT), QL_I3SAMER, F_HAS_ALIAS | F_SF),
  CORE_INSN ("subs", 0x6b000000, 0x7f200000, addsub_shift, 0, OP3 (Rd, Rn, Rm_SFT), QL_I3SAMER, F_HAS_ALIAS | F_SF),
  CORE_INSN ("cmp",  0x6b00001f, 0x7f20001f, addsub_shift, 0, OP2 (Rn, Rm_SFT),     QL_I2SAME,  F_ALIAS | F_SF | F_P1),
  CORE_INSN ("asr", 0x13000000, 0x7f800000, bitfield, OP_ASR_IMM, OP3 (Rd, Rn, IMM), QL_SHIFT, F_ALIAS | F_P2 | F_CONV),
  CORE_INSN ("lsl", 0x53000000, 0x7f800000, bitfield, OP_LSL_IMM, OP3 (Rd, Rn, IMM), QL_SHIFT, F_ALIAS | F_P2 | F_CONV),
  CORE_INSN ("lsr", 0x53000000, 0x7f800000, bitfield, OP_LSR_IMM, OP3 (Rd, Rn, IMM), QL_SHIFT, F_ALIAS | F_P2 | F_CONV),
  CORE_INSN ("b", 0x14000000, 0xfc000000, branch_imm, OP_B, OP1 (ADDR_PCREL26), QL_PCREL_26, 0),
  CORE_INSN ("bl", 0x94000000, 0xfc000000, branch_imm, OP_BL, OP1 (ADDR_PCREL26), QL_PCREL_26, 0),
  CORE_INSN ("ret", 0xd65f0000, 0xfffffc1f, branch_reg, 0, OP1 (Rn), QL_I1X, F_OPD0_OPT | F_DEFAULT (30)),
  CORE_INSN ("b.c", 0x54000000, 0xff000010, condbranch, 0, OP1 (ADDR_PCREL19), QL_PCREL_NIL, F_COND),
  CORE_INSN ("lsl",   0x1ac02000, 0x7fe0fc00, dp_2src, 0, OP3 (Rd, Rn, Rm), QL_I3SAMER, F_SF | F_ALIAS),
  CORE_INSN ("lsr",   0x1ac02400, 0x7fe0fc00, dp_2src, 0, OP3 (Rd, Rn, Rm), QL_I3SAMER, F_SF | F_ALIAS),
  CORE_INSN ("asr",   0x1ac02800, 0x7fe0fc00, dp_2src, 0, OP3 (Rd, Rn, Rm), QL_I3SAMER, F_SF | F_ALIAS),
  CORE_INSN ("stur", 0x3c000000, 0x3f600c00, ldst_unscaled, OP_STURV, OP2 (Ft, ADDR_SIMM9), QL_LDST_FP, 0),
  CORE_INSN ("ldur", 0x3c400000, 0x3f600c00, ldst_unscaled, OP_LDURV, OP2 (Ft, ADDR_SIMM9), QL_LDST_FP, 0),
  CORE_INSN ("stur", 0xb8000000, 0xbfe00c00, ldst_unscaled, OP_STUR, OP2 (Rt, ADDR_SIMM9), QL_LDST_R, F_GPRSIZE_IN_Q),
  CORE_INSN ("ldur", 0xb8400000, 0xbfe00c00, ldst_unscaled, OP_LDUR, OP2 (Rt, ADDR_SIMM9), QL_LDST_R, F_GPRSIZE_IN_Q),
  CORE_INSN ("orr", 0x32000000, 0x7f800000, log_imm, 0, OP3 (Rd_SP, Rn, LIMM), QL_R2NIL, F_HAS_ALIAS | F_SF),
  CORE_INSN ("eor", 0x52000000, 0x7f800000, log_imm, 0, OP3 (Rd_SP, Rn, LIMM), QL_R2NIL, F_SF),
  CORE_INSN ("ands", 0x72000000, 0x7f800000, log_imm, 0, OP3 (Rd, Rn, LIMM), QL_R2NIL, F_HAS_ALIAS | F_SF),
  CORE_INSN ("tst", 0x7200001f, 0x7f80001f, log_imm, 0, OP2 (Rn, LIMM), QL_R1NIL, F_ALIAS | F_SF),
  CORE_INSN ("orr", 0x2a000000, 0x7f200000, log_shift, 0, OP3 (Rd, Rn, Rm_SFT), QL_I3SAMER, F_HAS_ALIAS | F_SF),
  CORE_INSN ("mvn", 0x2a2003e0, 0x7f2003e0, log_shift, 0, OP2 (Rd, Rm_SFT), QL_I2SAMER, F_ALIAS | F_SF),
  CORE_INSN ("eor", 0x4a000000, 0x7f200000, log_shift, 0, OP3 (Rd, Rn, Rm_SFT), QL_I3SAMER, F_SF),
  CORE_INSN ("ands", 0x6a000000, 0x7f200000, log_shift, 0, OP3 (Rd, Rn, Rm_SFT), QL_I3SAMER, F_HAS_ALIAS | F_SF),
  CORE_INSN ("tst", 0x6a00001f, 0x7f20001f, log_shift, 0, OP2 (Rn, Rm_SFT), QL_I2SAMER, F_ALIAS | F_SF),
  CORE_INSN ("movz", 0x52800000, 0x7f800000, movewide, OP_MOVZ, OP2 (Rd, HALF), QL_DST_R, F_SF | F_HAS_ALIAS),
  CORE_INSN ("movk", 0x72800000, 0x7f800000, movewide, OP_MOVK, OP2 (Rd, HALF), QL_DST_R, F_SF),
  CORE_INSN ("adrp", 0x90000000, 0x9f000000, pcreladdr, 0, OP2 (Rd, ADDR_ADRP), QL_ADRP, 0),
  CORE_INSN ("nop", 0xd503201f, 0xffffffff, ic_system, 0, OP0 (), {}, F_ALIAS),

  {0, 0, 0, 0, 0, 0, {}, {}, 0, 0, 0, NULL},
};

#ifdef AARCH64_OPERANDS
#undef AARCH64_OPERANDS
#endif

/* Macro-based operand decription; this will be fed into aarch64-gen for it
   to generate the structure aarch64_operands and the function
   aarch64_insert_operand and aarch64_extract_operand.

   These inserters and extracters in the description execute the conversion
   between the aarch64_opnd_info and value in the operand-related instruction
   field(s).  */

/* Y expects arguments (left to right) to be operand class, inserter/extractor
   name suffix, operand name, flags, related bitfield(s) and description.
   X only differs from Y by having the operand inserter and extractor names
   listed separately.  */

#define AARCH64_OPERANDS						\
    Y(INT_REG, regno, "Rd", 0, F(FLD_Rd), "an integer register")	\
    Y(INT_REG, regno, "Rn", 0, F(FLD_Rn), "an integer register")	\
    Y(INT_REG, regno, "Rm", 0, F(FLD_Rm), "an integer register")	\
    Y(INT_REG, regno, "Rt", 0, F(FLD_Rt), "an integer register")	\
    Y(INT_REG, regno, "Rt2", 0, F(FLD_Rt2), "an integer register")	\
    Y(INT_REG, regno, "Rt_LS64", 0, F(FLD_Rt), "an integer register")	\
    Y(INT_REG, regno, "Rt_SP", OPD_F_MAYBE_SP, F(FLD_Rt),		\
      "an integer or stack pointer register")				\
    Y(INT_REG, regno, "Rs", 0, F(FLD_Rs), "an integer register")	\
    Y(INT_REG, regno, "Ra", 0, F(FLD_Ra), "an integer register")	\
    X(INT_REG, ins_regno, ext_regrt_sysins, "Rt_SYS", 0, F(FLD_Rt),	\
      "an integer register")						\
    Y(INT_REG, regno, "Rd_SP", OPD_F_MAYBE_SP, F(FLD_Rd),		\
      "an integer or stack pointer register")				\
    Y(INT_REG, regno, "Rn_SP", OPD_F_MAYBE_SP, F(FLD_Rn),		\
      "an integer or stack pointer register")				\
    Y(INT_REG, regno, "Rm_SP", OPD_F_MAYBE_SP, F(FLD_Rm),		\
      "an integer or stack pointer register")				\
    X(INT_REG, 0, ext_regno_pair, "PAIRREG", 0, F(),			\
      "the second reg of a pair")					\
    Y(MODIFIED_REG, reg_extended, "Rm_EXT", 0, F(),			\
      "an integer register with optional extension")			\
    Y(MODIFIED_REG, reg_shifted, "Rm_SFT", 0, F(),			\
      "an integer register with optional shift")			\
    Y(FP_REG, regno, "Fd", 0, F(FLD_Rd), "a floating-point register")	\
    Y(FP_REG, regno, "Fn", 0, F(FLD_Rn), "a floating-point register")	\
    Y(FP_REG, regno, "Fm", 0, F(FLD_Rm), "a floating-point register")	\
    Y(FP_REG, regno, "Fa", 0, F(FLD_Ra), "a floating-point register")	\
    Y(FP_REG, ft, "Ft", 0, F(FLD_Rt), "a floating-point register")	\
    Y(FP_REG, regno, "Ft2", 0, F(FLD_Rt2), "a floating-point register")	\
    Y(SISD_REG, regno, "Sd", 0, F(FLD_Rd), "a SIMD scalar register")	\
    Y(SISD_REG, regno, "Sn", 0, F(FLD_Rn), "a SIMD scalar register")	\
    Y(SISD_REG, regno, "Sm", 0, F(FLD_Rm), "a SIMD scalar register")	\
    Y(SIMD_REG, regno, "Va", 0, F(FLD_Ra), "a SIMD vector register")	\
    Y(SIMD_REG, regno, "Vd", 0, F(FLD_Rd), "a SIMD vector register")	\
    Y(SIMD_REG, regno, "Vn", 0, F(FLD_Rn), "a SIMD vector register")	\
    Y(SIMD_REG, regno, "Vm", 0, F(FLD_Rm), "a SIMD vector register")	\
    Y(FP_REG, regno, "VdD1", 0, F(FLD_Rd),				\
      "the top half of a 128-bit FP/SIMD register")			\
    Y(FP_REG, regno, "VnD1", 0, F(FLD_Rn),				\
      "the top half of a 128-bit FP/SIMD register")			\
    Y(SIMD_ELEMENT, reglane, "Ed", 0, F(FLD_Rd),			\
      "a SIMD vector element")						\
    Y(SIMD_ELEMENT, reglane, "En", 0, F(FLD_Rn),			\
      "a SIMD vector element")						\
    Y(SIMD_ELEMENT, reglane, "Em", 0, F(FLD_Rm),			\
      "a SIMD vector element")						\
    Y(SIMD_ELEMENT, reglane, "Em16", 0, F(FLD_Rm),			\
      "a SIMD vector element limited to V0-V15")			\
    Y(SIMD_REGLIST, reglist, "LVn", 0, F(FLD_Rn),			\
      "a SIMD vector register list")					\
    Y(SIMD_REGLIST, ldst_reglist, "LVt", 0, F(),			\
      "a SIMD vector register list")					\
    Y(SIMD_REGLIST, ldst_reglist_r, "LVt_AL", 0, F(),			\
      "a SIMD vector register list")					\
    Y(SIMD_REGLIST, ldst_elemlist, "LEt", 0, F(),			\
      "a SIMD vector element list")					\
    Y(IMMEDIATE, imm, "CRn", 0, F(FLD_CRn),				\
      "a 4-bit opcode field named for historical reasons C0 - C15")	\
    Y(IMMEDIATE, imm, "CRm", 0, F(FLD_CRm),				\
      "a 4-bit opcode field named for historical reasons C0 - C15")	\
    Y(IMMEDIATE, imm, "IDX", 0, F(FLD_imm4),				\
      "an immediate as the index of the least significant byte")	\
    Y(IMMEDIATE, imm, "MASK", 0, F(FLD_imm4_2),				\
      "an immediate as the index of the least significant byte")	\
    Y(IMMEDIATE, advsimd_imm_shift, "IMM_VLSL", 0, F(),			\
      "a left shift amount for an AdvSIMD register")			\
    Y(IMMEDIATE, advsimd_imm_shift, "IMM_VLSR", 0, F(),			\
      "a right shift amount for an AdvSIMD register")			\
    Y(IMMEDIATE, advsimd_imm_modified, "SIMD_IMM", 0, F(),		\
      "an immediate")							\
    Y(IMMEDIATE, advsimd_imm_modified, "SIMD_IMM_SFT", 0, F(),		\
      "an 8-bit unsigned immediate with optional shift")		\
    Y(IMMEDIATE, advsimd_imm_modified, "SIMD_FPIMM", 0, F(),		\
      "an 8-bit floating-point constant")				\
    X(IMMEDIATE, 0, ext_shll_imm, "SHLL_IMM", 0, F(),			\
      "an immediate shift amount of 8, 16 or 32")			\
    X(IMMEDIATE, 0, 0, "IMM0", 0, F(), "0")				\
    X(IMMEDIATE, 0, 0, "FPIMM0", 0, F(), "0.0")				\
    Y(IMMEDIATE, fpimm, "FPIMM", 0, F(FLD_imm8),			\
      "an 8-bit floating-point constant")				\
    Y(IMMEDIATE, imm, "IMMR", 0, F(FLD_immr),				\
      "the right rotate amount")					\
    Y(IMMEDIATE, imm, "IMMS", 0, F(FLD_imm6),				\
      "the leftmost bit number to be moved from the source")		\
    Y(IMMEDIATE, imm, "WIDTH", 0, F(FLD_imm6),				\
      "the width of the bit-field")					\
    Y(IMMEDIATE, imm, "IMM", 0, F(FLD_imm6), "an immediate")            \
    Y(IMMEDIATE, imm, "IMM_2", 0, F(FLD_imm6_2), "an immediate")        \
    Y(IMMEDIATE, imm, "UIMM3_OP1", 0, F(FLD_op1),			\
      "a 3-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "UIMM3_OP2", 0, F(FLD_op2),			\
      "a 3-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "UIMM4", 0, F(FLD_CRm),				\
      "a 4-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "UIMM4_ADDG", 0, F(FLD_imm4_3),			\
      "a 4-bit unsigned Logical Address Tag modifier")			\
    Y(IMMEDIATE, imm, "UIMM7", 0, F(FLD_CRm, FLD_op2),			\
      "a 7-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "UIMM10", OPD_F_SHIFT_BY_4, F(FLD_immr),		\
      "a 10-bit unsigned multiple of 16")				\
    Y(IMMEDIATE, imm, "BIT_NUM", 0, F(FLD_b5, FLD_b40),			\
      "the bit number to be tested")					\
    Y(IMMEDIATE, imm, "EXCEPTION", 0, F(FLD_imm16),			\
      "a 16-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "UNDEFINED", 0, F(FLD_imm16_2),			\
      "a 16-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "CCMP_IMM", 0, F(FLD_imm5),			\
      "a 5-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "SIMM5", OPD_F_SEXT, F(FLD_imm5),			\
      "a 5-bit signed immediate")					\
    Y(IMMEDIATE, imm, "NZCV", 0, F(FLD_nzcv),				\
      "a flag bit specifier giving an alternative value for each flag")	\
    Y(IMMEDIATE, limm, "LIMM", 0, F(FLD_N,FLD_immr,FLD_imms),		\
      "Logical immediate")						\
    Y(IMMEDIATE, aimm, "AIMM", 0, F(FLD_shift,FLD_imm12),		\
      "a 12-bit unsigned immediate with optional left shift of 12 bits")\
    Y(IMMEDIATE, imm_half, "HALF", 0, F(FLD_imm16),			\
      "a 16-bit immediate with optional left shift")			\
    Y(IMMEDIATE, fbits, "FBITS", 0, F(FLD_scale),			\
      "the number of bits after the binary point in the fixed-point value")\
    X(IMMEDIATE, 0, 0, "IMM_MOV", 0, F(), "an immediate")		\
    Y(IMMEDIATE, imm_rotate2, "IMM_ROT1", 0, F(FLD_rotate1),		\
      "a 2-bit rotation specifier for complex arithmetic operations")	\
    Y(IMMEDIATE, imm_rotate2, "IMM_ROT2", 0, F(FLD_rotate2),		\
      "a 2-bit rotation specifier for complex arithmetic operations")	\
    Y(IMMEDIATE, imm_rotate1, "IMM_ROT3", 0, F(FLD_rotate3),		\
      "a 1-bit rotation specifier for complex arithmetic operations")	\
    Y(COND, cond, "COND", 0, F(), "a condition")			\
    Y(COND, cond, "COND1", 0, F(),					\
      "one of the standard conditions, excluding AL and NV.")		\
    X(ADDRESS, 0, ext_imm, "ADDR_ADRP", OPD_F_SEXT, F(FLD_immhi, FLD_immlo),\
      "21-bit PC-relative address of a 4KB page")			\
    Y(ADDRESS, imm, "ADDR_PCREL14", OPD_F_SEXT | OPD_F_SHIFT_BY_2,	\
      F(FLD_imm14), "14-bit PC-relative address")			\
    Y(ADDRESS, imm, "ADDR_PCREL19", OPD_F_SEXT | OPD_F_SHIFT_BY_2,	\
      F(FLD_imm19), "19-bit PC-relative address")			\
    Y(ADDRESS, imm, "ADDR_PCREL21", OPD_F_SEXT, F(FLD_immhi,FLD_immlo),	\
      "21-bit PC-relative address")					\
    Y(ADDRESS, imm, "ADDR_PCREL26", OPD_F_SEXT | OPD_F_SHIFT_BY_2,	\
      F(FLD_imm26), "26-bit PC-relative address")			\
    Y(ADDRESS, addr_simple, "ADDR_SIMPLE", 0, F(),			\
      "an address with base register (no offset)")			\
    Y(ADDRESS, addr_regoff, "ADDR_REGOFF", 0, F(),			\
      "an address with register offset")				\
    Y(ADDRESS, addr_simm, "ADDR_SIMM7", 0, F(FLD_imm7,FLD_index2),	\
      "an address with 7-bit signed immediate offset")			\
    Y(ADDRESS, addr_simm, "ADDR_SIMM9", 0, F(FLD_imm9,FLD_index),	\
      "an address with 9-bit signed immediate offset")			\
    Y(ADDRESS, addr_simm, "ADDR_SIMM9_2", 0, F(FLD_imm9,FLD_index),	\
      "an address with 9-bit negative or unaligned immediate offset")	\
    Y(ADDRESS, addr_simm10, "ADDR_SIMM10", 0, F(FLD_Rn,FLD_S_imm10,FLD_imm9,FLD_index),\
      "an address with an optional 10-bit scaled, signed immediate offset")		\
    Y(ADDRESS, addr_simm, "ADDR_SIMM11", 0, F(FLD_imm7,FLD_index2),\
      "an address with 11-bit signed immediate (multiple of 16) offset")\
    Y(ADDRESS, addr_uimm12, "ADDR_UIMM12", 0, F(FLD_Rn,FLD_imm12),	\
      "an address with scaled, unsigned immediate offset")		\
    Y(ADDRESS, addr_simm, "ADDR_SIMM13", 0, F(FLD_imm9,FLD_index),\
      "an address with 13-bit signed immediate (multiple of 16) offset")\
    Y(ADDRESS, addr_simple, "SIMD_ADDR_SIMPLE", 0, F(),			\
      "an address with base register (no offset)")			\
    Y(ADDRESS, addr_offset, "ADDR_OFFSET", 0, F(FLD_Rn,FLD_imm9,FLD_index),\
      "an address with an optional 8-bit signed immediate offset")	\
    Y(ADDRESS, simd_addr_post, "SIMD_ADDR_POST", 0, F(),		\
      "a post-indexed address with immediate or register increment")	\
    Y(SYSTEM, sysreg, "SYSREG", 0, F(), "a system register")		\
    Y(SYSTEM, pstatefield, "PSTATEFIELD", 0, F(),			\
      "a PSTATE field name")						\
    Y(SYSTEM, sysins_op, "SYSREG_AT", 0, F(),				\
      "an address translation operation specifier")			\
    Y(SYSTEM, sysins_op, "SYSREG_DC", 0, F(),				\
      "a data cache maintenance operation specifier")			\
    Y(SYSTEM, sysins_op, "SYSREG_IC", 0, F(),				\
      "an instruction cache maintenance operation specifier")		\
    Y(SYSTEM, sysins_op, "SYSREG_TLBI", 0, F(),				\
      "a TBL invalidation operation specifier")				\
    Y(SYSTEM, sysins_op, "SYSREG_SR", 0, F(),				\
      "a Speculation Restriction option name (RCTX)")			\
    Y(SYSTEM, barrier, "BARRIER", 0, F(),				\
      "a barrier option name")						\
    Y(SYSTEM, barrier_dsb_nxs, "BARRIER_DSB_NXS", 0, F(),				\
      "the DSB nXS option qualifier name SY, ISH, NSH, OSH or an optional 5-bit unsigned immediate")	\
    Y(SYSTEM, barrier, "BARRIER_ISB", 0, F(),				\
      "the ISB option name SY or an optional 4-bit unsigned immediate")	\
    Y(SYSTEM, prfop, "PRFOP", 0, F(),					\
      "a prefetch operation specifier")					\
    Y(SYSTEM, none, "BARRIER_PSB", 0, F (),				\
      "the PSB/TSB option name CSYNC")					\
    Y(SYSTEM, hint, "BTI", 0, F (),					\
      "BTI targets j/c/jc")						\
    Y(ADDRESS, sve_addr_ri_s4, "SVE_ADDR_RI_S4x16",			\
      4 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by 16")	\
    Y(ADDRESS, sve_addr_ri_s4, "SVE_ADDR_RI_S4x32",			\
      5 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by 32")	\
    Y(ADDRESS, sve_addr_ri_s4xvl, "SVE_ADDR_RI_S4xVL",			\
      0 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by VL")	\
    Y(ADDRESS, sve_addr_ri_s4xvl, "SVE_ADDR_RI_S4x2xVL",		\
      1 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by 2*VL")	\
    Y(ADDRESS, sve_addr_ri_s4xvl, "SVE_ADDR_RI_S4x3xVL",		\
      2 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by 3*VL")	\
    Y(ADDRESS, sve_addr_ri_s4xvl, "SVE_ADDR_RI_S4x4xVL",		\
      3 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 4-bit signed offset, multiplied by 4*VL")	\
    Y(ADDRESS, sve_addr_ri_s6xvl, "SVE_ADDR_RI_S6xVL",			\
      0 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 6-bit signed offset, multiplied by VL")	\
    Y(ADDRESS, sve_addr_ri_s9xvl, "SVE_ADDR_RI_S9xVL",			\
      0 << OPD_F_OD_LSB, F(FLD_Rn),					\
      "an address with a 9-bit signed offset, multiplied by VL")	\
    Y(ADDRESS, sve_addr_ri_u6, "SVE_ADDR_RI_U6", 0 << OPD_F_OD_LSB,	\
      F(FLD_Rn), "an address with a 6-bit unsigned offset")		\
    Y(ADDRESS, sve_addr_ri_u6, "SVE_ADDR_RI_U6x2", 1 << OPD_F_OD_LSB,	\
      F(FLD_Rn),							\
      "an address with a 6-bit unsigned offset, multiplied by 2")	\
    Y(ADDRESS, sve_addr_ri_u6, "SVE_ADDR_RI_U6x4", 2 << OPD_F_OD_LSB,	\
      F(FLD_Rn),							\
      "an address with a 6-bit unsigned offset, multiplied by 4")	\
    Y(ADDRESS, sve_addr_ri_u6, "SVE_ADDR_RI_U6x8", 3 << OPD_F_OD_LSB,	\
      F(FLD_Rn),							\
      "an address with a 6-bit unsigned offset, multiplied by 8")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_R", 0 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with an optional scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RR", 0 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with a scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RR_LSL1", 1 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with a scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RR_LSL2", 2 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with a scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RR_LSL3", 3 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with a scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RR_LSL4", 4 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_Rm), "an address with a scalar register offset")	\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RX",				\
      (0 << OPD_F_OD_LSB) | OPD_F_NO_ZR, F(FLD_Rn,FLD_Rm),		\
      "an address with a scalar register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RX_LSL1",			\
      (1 << OPD_F_OD_LSB) | OPD_F_NO_ZR, F(FLD_Rn,FLD_Rm),		\
      "an address with a scalar register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RX_LSL2",			\
      (2 << OPD_F_OD_LSB) | OPD_F_NO_ZR, F(FLD_Rn,FLD_Rm),		\
      "an address with a scalar register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RX_LSL3",			\
      (3 << OPD_F_OD_LSB) | OPD_F_NO_ZR, F(FLD_Rn,FLD_Rm),		\
      "an address with a scalar register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_ZX",				\
      0 << OPD_F_OD_LSB , F(FLD_SVE_Zn,FLD_Rm),				\
      "vector of address with a scalar register offset")		\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RZ", 0 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_SVE_Zm_16),						\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RZ_LSL1", 1 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_SVE_Zm_16),						\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RZ_LSL2", 2 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_SVE_Zm_16),						\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rr_lsl, "SVE_ADDR_RZ_LSL3", 3 << OPD_F_OD_LSB,	\
      F(FLD_Rn,FLD_SVE_Zm_16),						\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW_14",			\
      0 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_14),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW_22",			\
      0 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_22),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW1_14",			\
      1 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_14),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW1_22",			\
      1 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_22),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW2_14",			\
      2 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_14),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW2_22",			\
      2 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_22),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW3_14",			\
      3 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_14),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_rz_xtw, "SVE_ADDR_RZ_XTW3_22",			\
      3 << OPD_F_OD_LSB, F(FLD_Rn,FLD_SVE_Zm_16,FLD_SVE_xs_22),		\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_zi_u5, "SVE_ADDR_ZI_U5", 0 << OPD_F_OD_LSB,	\
      F(FLD_SVE_Zn), "an address with a 5-bit unsigned offset")		\
    Y(ADDRESS, sve_addr_zi_u5, "SVE_ADDR_ZI_U5x2", 1 << OPD_F_OD_LSB,	\
      F(FLD_SVE_Zn),							\
      "an address with a 5-bit unsigned offset, multiplied by 2")	\
    Y(ADDRESS, sve_addr_zi_u5, "SVE_ADDR_ZI_U5x4", 2 << OPD_F_OD_LSB,	\
      F(FLD_SVE_Zn),							\
      "an address with a 5-bit unsigned offset, multiplied by 4")	\
    Y(ADDRESS, sve_addr_zi_u5, "SVE_ADDR_ZI_U5x8", 3 << OPD_F_OD_LSB,	\
      F(FLD_SVE_Zn),							\
      "an address with a 5-bit unsigned offset, multiplied by 8")	\
    Y(ADDRESS, sve_addr_zz_lsl, "SVE_ADDR_ZZ_LSL", 0,			\
      F(FLD_SVE_Zn,FLD_SVE_Zm_16),					\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_zz_sxtw, "SVE_ADDR_ZZ_SXTW", 0,			\
      F(FLD_SVE_Zn,FLD_SVE_Zm_16),					\
      "an address with a vector register offset")			\
    Y(ADDRESS, sve_addr_zz_uxtw, "SVE_ADDR_ZZ_UXTW", 0,			\
      F(FLD_SVE_Zn,FLD_SVE_Zm_16),					\
      "an address with a vector register offset")			\
    Y(IMMEDIATE, sve_aimm, "SVE_AIMM", 0, F(FLD_SVE_imm9),		\
      "a 9-bit unsigned arithmetic operand")				\
    Y(IMMEDIATE, sve_asimm, "SVE_ASIMM", 0, F(FLD_SVE_imm9),		\
      "a 9-bit signed arithmetic operand")				\
    Y(IMMEDIATE, fpimm, "SVE_FPIMM8", 0, F(FLD_SVE_imm8),		\
      "an 8-bit floating-point immediate")				\
    Y(IMMEDIATE, sve_float_half_one, "SVE_I1_HALF_ONE", 0,		\
      F(FLD_SVE_i1), "either 0.5 or 1.0")				\
    Y(IMMEDIATE, sve_float_half_two, "SVE_I1_HALF_TWO", 0,		\
      F(FLD_SVE_i1), "either 0.5 or 2.0")				\
    Y(IMMEDIATE, sve_float_zero_one, "SVE_I1_ZERO_ONE", 0,		\
      F(FLD_SVE_i1), "either 0.0 or 1.0")				\
    Y(IMMEDIATE, imm_rotate1, "SVE_IMM_ROT1", 0, F(FLD_SVE_rot1),	\
      "a 1-bit rotation specifier for complex arithmetic operations")	\
    Y(IMMEDIATE, imm_rotate2, "SVE_IMM_ROT2", 0, F(FLD_SVE_rot2),	\
      "a 2-bit rotation specifier for complex arithmetic operations")	\
    Y(IMMEDIATE, imm_rotate1, "SVE_IMM_ROT3", 0, F(FLD_SVE_rot3),	\
      "a 1-bit rotation specifier for complex arithmetic operations")	\
    Y(IMMEDIATE, inv_limm, "SVE_INV_LIMM", 0,				\
      F(FLD_SVE_N,FLD_SVE_immr,FLD_SVE_imms),				\
      "an inverted 13-bit logical immediate")				\
    Y(IMMEDIATE, limm, "SVE_LIMM", 0,					\
      F(FLD_SVE_N,FLD_SVE_immr,FLD_SVE_imms),				\
      "a 13-bit logical immediate")					\
    Y(IMMEDIATE, sve_limm_mov, "SVE_LIMM_MOV", 0,			\
      F(FLD_SVE_N,FLD_SVE_immr,FLD_SVE_imms),				\
      "a 13-bit logical move immediate")				\
    Y(IMMEDIATE, imm, "SVE_PATTERN", 0, F(FLD_SVE_pattern),		\
      "an enumeration value such as POW2")				\
    Y(IMMEDIATE, sve_scale, "SVE_PATTERN_SCALED", 0,			\
      F(FLD_SVE_pattern), "an enumeration value such as POW2")		\
    Y(IMMEDIATE, imm, "SVE_PRFOP", 0, F(FLD_SVE_prfop),			\
      "an enumeration value such as PLDL1KEEP")				\
    Y(PRED_REG, regno, "SVE_Pd", 0, F(FLD_SVE_Pd),			\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pg3", 0, F(FLD_SVE_Pg3),			\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pg4_5", 0, F(FLD_SVE_Pg4_5),		\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pg4_10", 0, F(FLD_SVE_Pg4_10),		\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pg4_16", 0, F(FLD_SVE_Pg4_16),		\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pm", 0, F(FLD_SVE_Pm),			\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pn", 0, F(FLD_SVE_Pn),			\
      "an SVE predicate register")					\
    Y(PRED_REG, regno, "SVE_Pt", 0, F(FLD_SVE_Pt),			\
      "an SVE predicate register")					\
    Y(INT_REG, regno, "SVE_Rm", 0, F(FLD_SVE_Rm),			\
      "an integer register or zero")					\
    Y(INT_REG, regno, "SVE_Rn_SP", OPD_F_MAYBE_SP, F(FLD_SVE_Rn),	\
      "an integer register or SP")					\
    Y(IMMEDIATE, sve_shlimm, "SVE_SHLIMM_PRED", 0,			\
      F(FLD_SVE_tszh,FLD_SVE_imm5), "a shift-left immediate operand")	\
    Y(IMMEDIATE, sve_shlimm, "SVE_SHLIMM_UNPRED", 0,			\
      F(FLD_SVE_tszh,FLD_imm5), "a shift-left immediate operand")	\
    Y(IMMEDIATE, sve_shlimm, "SVE_SHLIMM_UNPRED_22", 0,			\
      F(FLD_SVE_sz, FLD_SVE_tszl_19, FLD_SVE_imm3),			\
      "a shift-left immediate operand")					\
    Y(IMMEDIATE, sve_shrimm, "SVE_SHRIMM_PRED", 1 << OPD_F_OD_LSB,	\
      F(FLD_SVE_tszh,FLD_SVE_imm5), "a shift-right immediate operand")	\
    Y(IMMEDIATE, sve_shrimm, "SVE_SHRIMM_UNPRED", 1 << OPD_F_OD_LSB,	\
      F(FLD_SVE_tszh,FLD_imm5), "a shift-right immediate operand")	\
    Y(IMMEDIATE, sve_shrimm, "SVE_SHRIMM_UNPRED_22", 2 << OPD_F_OD_LSB,	\
      F(FLD_SVE_sz, FLD_SVE_tszl_19, FLD_SVE_imm3),			\
      "a shift-right immediate operand")				\
    Y(IMMEDIATE, imm, "SVE_SIMM5", OPD_F_SEXT, F(FLD_SVE_imm5),		\
      "a 5-bit signed immediate")					\
    Y(IMMEDIATE, imm, "SVE_SIMM5B", OPD_F_SEXT, F(FLD_SVE_imm5b),	\
      "a 5-bit signed immediate")					\
    Y(IMMEDIATE, imm, "SVE_SIMM6", OPD_F_SEXT, F(FLD_SVE_imms),		\
      "a 6-bit signed immediate")					\
    Y(IMMEDIATE, imm, "SVE_SIMM8", OPD_F_SEXT, F(FLD_SVE_imm8),		\
      "an 8-bit signed immediate")					\
    Y(IMMEDIATE, imm, "SVE_UIMM3", 0, F(FLD_SVE_imm3),			\
      "a 3-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "SVE_UIMM7", 0, F(FLD_SVE_imm7),			\
      "a 7-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "SVE_UIMM8", 0, F(FLD_SVE_imm8),			\
      "an 8-bit unsigned immediate")					\
    Y(IMMEDIATE, imm, "SVE_UIMM8_53", 0, F(FLD_imm5,FLD_imm3),		\
      "an 8-bit unsigned immediate")					\
    Y(SIMD_REG, regno, "SVE_VZn", 0, F(FLD_SVE_Zn), "a SIMD register")	\
    Y(SIMD_REG, regno, "SVE_Vd", 0, F(FLD_SVE_Vd), "a SIMD register")	\
    Y(SIMD_REG, regno, "SVE_Vm", 0, F(FLD_SVE_Vm), "a SIMD register")	\
    Y(SIMD_REG, regno, "SVE_Vn", 0, F(FLD_SVE_Vn), "a SIMD register")	\
    Y(SVE_REG, regno, "SVE_Za_5", 0, F(FLD_SVE_Za_5),			\
      "an SVE vector register")						\
    Y(SVE_REG, regno, "SVE_Za_16", 0, F(FLD_SVE_Za_16),			\
      "an SVE vector register")						\
    Y(SVE_REG, regno, "SVE_Zd", 0, F(FLD_SVE_Zd),			\
      "an SVE vector register")						\
    Y(SVE_REG, regno, "SVE_Zm_5", 0, F(FLD_SVE_Zm_5),			\
      "an SVE vector register")						\
    Y(SVE_REG, regno, "SVE_Zm_16", 0, F(FLD_SVE_Zm_16),			\
      "an SVE vector register")						\
    Y(SVE_REG, sve_quad_index, "SVE_Zm3_INDEX",				\
      3 << OPD_F_OD_LSB, F(FLD_SVE_Zm_16),				\
      "an indexed SVE vector register")					\
    Y(SVE_REG, sve_quad_index, "SVE_Zm3_22_INDEX", 			\
      3 << OPD_F_OD_LSB, F(FLD_SVE_i3h, FLD_SVE_Zm_16),			\
      "an indexed SVE vector register")					\
    Y(SVE_REG, sve_quad_index, "SVE_Zm3_11_INDEX", 			\
      3 << OPD_F_OD_LSB, F(FLD_SVE_i3h2, FLD_SVE_i3l, FLD_SVE_imm3),    \
      "an indexed SVE vector register")					\
    Y(SVE_REG, sve_quad_index, "SVE_Zm4_11_INDEX", 			\
      4 << OPD_F_OD_LSB, F(FLD_SVE_i2h, FLD_SVE_i3l, FLD_SVE_imm4),     \
      "an indexed SVE vector register")					\
    Y(SVE_REG, sve_quad_index, "SVE_Zm4_INDEX", 			\
      4 << OPD_F_OD_LSB, F(FLD_SVE_Zm_16),				\
      "an indexed SVE vector register")					\
    Y(SVE_REG, regno, "SVE_Zn", 0, F(FLD_SVE_Zn),			\
      "an SVE vector register")						\
    Y(SVE_REG, sve_index, "SVE_Zn_INDEX", 0, F(FLD_SVE_Zn),		\
      "an indexed SVE vector register")					\
    Y(SVE_REG, sve_reglist, "SVE_ZnxN", 0, F(FLD_SVE_Zn),		\
      "a list of SVE vector registers")					\
    Y(SVE_REG, regno, "SVE_Zt", 0, F(FLD_SVE_Zt),			\
      "an SVE vector register")						\
    Y(SVE_REG, sve_reglist, "SVE_ZtxN", 0, F(FLD_SVE_Zt),		\
      "a list of SVE vector registers")					\
    Y(SVE_REG, regno, "SME_ZAda_2b", 0, F(FLD_SME_ZAda_2b),		\
      "an SME ZA tile ZA0-ZA3")					\
    Y(SVE_REG, regno, "SME_ZAda_3b", 0, F(FLD_SME_ZAda_3b),		\
      "an SME ZA tile ZA0-ZA7")					\
    Y(SVE_REG, sme_za_hv_tiles, "SME_ZA_HV_idx_src", 0,				\
      F(FLD_SME_size_10,FLD_SME_Q,FLD_SME_V,FLD_SME_Rv,FLD_imm4_5),\
      "an SME horizontal or vertical vector access register")	\
    Y(SVE_REG, sme_za_hv_tiles, "SME_ZA_HV_idx_dest", 0,				\
      F(FLD_SME_size_10,FLD_SME_Q,FLD_SME_V,FLD_SME_Rv,FLD_imm4_2),\
      "an SME horizontal or vertical vector access register")	\
    Y(PRED_REG, regno, "SME_Pm", 0, F(FLD_SME_Pm),			\
      "an SVE predicate register")					\
    Y(SVE_REG, imm, "SME_list_of_64bit_tiles", 0,	\
      F(FLD_SME_zero_mask), "list of 64-bit ZA element tiles")					\
    Y(SVE_REG, sme_za_hv_tiles, "SME_ZA_HV_idx_ldstr", 0,				\
      F(FLD_SME_size_10,FLD_index2,FLD_SME_V,FLD_SME_Rv,FLD_imm4_2),	\
      "an SME horizontal or vertical vector access register")	\
    Y(SVE_REG, sme_za_array, "SME_ZA_array", 0,				\
      F(FLD_SME_Rv,FLD_imm4_2),	\
      "ZA array")	\
    Y(ADDRESS, sme_addr_ri_u4xvl, "SME_ADDR_RI_U4xVL", 0 << OPD_F_OD_LSB, \
      F(FLD_Rn,FLD_imm4_2),					\
      "memory offset")	\
    Y(ADDRESS, sme_sm_za, "SME_SM_ZA", 0, \
      F(FLD_CRm),					\
      "streaming mode")	\
    Y(SVE_REG, sme_pred_reg_with_index, "SME_PnT_Wm_imm", 0,			\
      F(FLD_SME_Rm,FLD_SVE_Pn,FLD_SME_i1,FLD_SME_tszh,FLD_SME_tszl),	\
      "Source scalable predicate register with index ")	\
    Y(IMMEDIATE, imm, "TME_UIMM16", 0, F(FLD_imm16),			\
      "a 16-bit unsigned immediate for TME tcancel")			\
    Y(SIMD_ELEMENT, reglane, "SM3_IMM2", 0, F(FLD_SM3_imm2),		\
      "an indexed SM3 vector immediate")				\
    /* These next two are really register fields; the [...] notation	\
       is just syntactic sugar.  */					\
    Y(INT_REG, x0_to_x30, "MOPS_ADDR_Rd", 0, F(FLD_Rd),			\
      "a register destination address with writeback")			\
    Y(INT_REG, x0_to_x30, "MOPS_ADDR_Rs", 0, F(FLD_Rs),			\
      "a register source address with writeback")			\
    Y(INT_REG, x0_to_x30, "MOPS_WB_Rd", 0, F(FLD_Rn),			\
      "an integer register with writeback")				\
    Y(IMMEDIATE, imm, "CSSC_SIMM8", OPD_F_SEXT, F(FLD_CSSC_imm8),	\
      "an 8-bit signed immediate")					\
    Y(IMMEDIATE, imm, "CSSC_UIMM8", 0, F(FLD_CSSC_imm8),		\
      "an 8-bit unsigned immediate")
