/* $NoKeywords:$ */
/**
 * @file
 *
 * Install of build option: Core Performance Boost
 *
 * Contains AMD AGESA install macros and test conditions. Output is the
 * defaults tables reflecting the User's build options selection.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Options
 * @e \$Revision: 46389 $   @e \$Date: 2011-01-31 20:22:49 -0700 (Mon, 31 Jan 2011) $
 */
/*****************************************************************************
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 ***************************************************************************/

#ifndef _OPTION_CPB_INSTALL_H_
#define _OPTION_CPB_INSTALL_H_

#include "cpuCpb.h"

/*  This option is designed to be included into the platform solution install
 *  file. The platform solution install file will define the options status.
 *  Check to validate the definition
 */
#define OPTION_CPB_FEAT
#define F10_CPB_SUPPORT
#define F12_CPB_SUPPORT
#define F14_ON_CPB_SUPPORT
#define F15_OR_CPB_SUPPORT

#if OPTION_CPB == TRUE
  #if (AGESA_ENTRY_INIT_EARLY == TRUE) || (AGESA_ENTRY_INIT_LATE == TRUE) || (AGESA_ENTRY_INIT_LATE_RESTORE == TRUE)
    // Family 10h
    #ifdef OPTION_FAMILY10H
      #if OPTION_FAMILY10H == TRUE
        #if OPTION_FAMILY10H_PH == TRUE
          extern CONST CPU_FEATURE_DESCRIPTOR ROMDATA CpuFeatureCpb;
          #undef OPTION_CPB_FEAT
          #define OPTION_CPB_FEAT &CpuFeatureCpb,
          extern CONST CPB_FAMILY_SERVICES ROMDATA F10CpbSupport;
          #undef F10_CPB_SUPPORT
          #define F10_CPB_SUPPORT {AMD_FAMILY_10_PH, &F10CpbSupport},
        #endif
      #endif
    #endif

    // Family 12h
    #ifdef OPTION_FAMILY12H
      #if OPTION_FAMILY12H == TRUE
        #if OPTION_FAMILY12H_LN == TRUE
          extern CONST CPU_FEATURE_DESCRIPTOR ROMDATA CpuFeatureCpb;
          #undef OPTION_CPB_FEAT
          #define OPTION_CPB_FEAT &CpuFeatureCpb,
          extern CONST CPB_FAMILY_SERVICES ROMDATA F12CpbSupport;
          #undef F12_CPB_SUPPORT
          #define F12_CPB_SUPPORT {AMD_FAMILY_12_LN, &F12CpbSupport},
          #if OPTION_EARLY_SAMPLES == TRUE
            #if (AGESA_ENTRY_INIT_EARLY == TRUE)
              extern F_F12_ES_CPB_INIT F12LnA1CpbHook;

              CONST F12_ES_CPB_SUPPORT ROMDATA F12EarlySampleCpbSupport =
              {
                F12LnA1CpbHook
              };
            #else
              CONST F12_ES_CPB_SUPPORT ROMDATA F12EarlySampleCpbSupport =
              {
                (PF_F12_ES_CPB_INIT) CommonVoid
              };
            #endif
          #else
            CONST F12_ES_CPB_SUPPORT ROMDATA F12EarlySampleCpbSupport =
            {
              (PF_F12_ES_CPB_INIT) CommonVoid
            };
          #endif
        #endif
      #endif
    #endif

    // Family 14h
    #ifdef OPTION_FAMILY14H
      #if OPTION_FAMILY14H == TRUE
        #if OPTION_FAMILY14H_ON == TRUE
          extern CONST CPU_FEATURE_DESCRIPTOR ROMDATA CpuFeatureCpb;
          #undef OPTION_CPB_FEAT
          #define OPTION_CPB_FEAT &CpuFeatureCpb,
          extern CONST CPB_FAMILY_SERVICES ROMDATA F14OnCpbSupport;
          #undef F14_ON_CPB_SUPPORT
          #define F14_ON_CPB_SUPPORT {AMD_FAMILY_14_ON, &F14OnCpbSupport},
        #endif
      #endif
    #endif

    // Family 15h
    #ifdef OPTION_FAMILY15H
      #if OPTION_FAMILY15H == TRUE
        #if (OPTION_FAMILY15H_OR == TRUE)
          extern CONST CPU_FEATURE_DESCRIPTOR ROMDATA CpuFeatureCpb;
          #undef OPTION_CPB_FEAT
          #define OPTION_CPB_FEAT &CpuFeatureCpb,
          extern CONST CPB_FAMILY_SERVICES ROMDATA F15OrCpbSupport;
          #undef F15_OR_CPB_SUPPORT
          #define F15_OR_CPB_SUPPORT {AMD_FAMILY_15_OR, &F15OrCpbSupport},

          #if OPTION_EARLY_SAMPLES == TRUE
            extern F_F15_OR_ES_IS_CPB_SUPPORTED F15OrIsCpbDisabledEarlySample;

            CONST F15_OR_ES_CPB_SUPPORT ROMDATA F15OrEarlySampleCpbSupport =
            {
              F15OrIsCpbDisabledEarlySample
            };
          #else
            CONST F15_OR_ES_CPB_SUPPORT ROMDATA F15OrEarlySampleCpbSupport =
            {
              (PF_F15_OR_ES_IS_CPB_SUPPORTED) CommonVoid
            };
          #endif
        #endif
      #endif
    #endif

  #endif
#endif

CONST CPU_SPECIFIC_SERVICES_XLAT ROMDATA CpbFamilyServiceArray[] =
{
  F10_CPB_SUPPORT
  F12_CPB_SUPPORT
  F14_ON_CPB_SUPPORT
  F15_OR_CPB_SUPPORT
  {0, NULL}
};

CONST CPU_FAMILY_SUPPORT_TABLE ROMDATA CpbFamilyServiceTable =
{
  (sizeof (CpbFamilyServiceArray) / sizeof (CPU_SPECIFIC_SERVICES_XLAT)),
  &CpbFamilyServiceArray[0]
};

#endif  // _OPTION_CPB_INSTALL_H_
