/************************************************************************************************************************************\
|*                                                                                                                                    *|
|*     Copyright � 2017 NVIDIA Corporation.  All rights reserved.                                                                     *|
|*                                                                                                                                    *|
|*  NOTICE TO USER:                                                                                                                   *|
|*                                                                                                                                    *|
|*  This software is subject to NVIDIA ownership rights under U.S. and international Copyright laws.                                  *|
|*                                                                                                                                    *|
|*  This software and the information contained herein are PROPRIETARY and CONFIDENTIAL to NVIDIA                                     *|
|*  and are being provided solely under the terms and conditions of an NVIDIA software license agreement                              *|
|*  and / or non-disclosure agreement.  Otherwise, you have no rights to use or access this software in any manner.                   *|
|*                                                                                                                                    *|
|*  If not covered by the applicable NVIDIA software license agreement:                                                               *|
|*  NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOFTWARE FOR ANY PURPOSE.                                            *|
|*  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.                                                           *|
|*  NVIDIA DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,                                                                     *|
|*  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.                       *|
|*  IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,                               *|
|*  OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT,                         *|
|*  NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.            *|
|*                                                                                                                                    *|
|*  U.S. Government End Users.                                                                                                        *|
|*  This software is a "commercial item" as that term is defined at 48 C.F.R. 2.101 (OCT 1995),                                       *|
|*  consisting  of "commercial computer  software"  and "commercial computer software documentation"                                  *|
|*  as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995) and is provided to the U.S. Government only as a commercial end item.     *|
|*  Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 227.7202-4 (JUNE 1995),                                          *|
|*  all U.S. Government End Users acquire the software with only those rights set forth herein.                                       *|
|*                                                                                                                                    *|
|*  Any use of this software in individual and commercial software must include,                                                      *|
|*  in the user documentation and internal comments to the code,                                                                      *|
|*  the above Disclaimer (as applicable) and U.S. Government End Users Notice.                                                        *|
|*                                                                                                                                    *|
 \************************************************************************************************************************************/
#pragma once
#ifdef FALCOR_DXR
#include "RtProgram/RtProgramVersion.h"

namespace Falcor
{
    class RtStateObject : public std::enable_shared_from_this<RtStateObject>
    {
    public:
        using SharedPtr = std::shared_ptr<RtStateObject>;
        using SharedConstPtr = std::shared_ptr<const RtStateObject>;
        using ApiHandle = ID3D12StateObjectPrototypePtr;

        using ProgramList = std::vector<RtProgramVersion::SharedConstPtr>;

        class Desc
        {
        public:
            Desc& setProgramList(const ProgramList& list) { mProgList = list; return *this; }
            Desc& setMaxTraceRecursionDepth(uint32_t maxDepth) { mMaxTraceRecursionDepth = maxDepth; return *this; }
            bool operator==(const Desc& other) const;

        private:
            ProgramList mProgList;
            uint32_t mMaxTraceRecursionDepth = 1;
            friend RtStateObject;
        };

        static SharedPtr create(const Desc& desc);
        ApiHandle getApiHandle() const { return mApiHandle; }

        const ProgramList& getProgramList() const { return mDesc.mProgList; }
        uint32_t getMaxTraceRecursionDepth() const { return mDesc.mMaxTraceRecursionDepth; }

        const Desc& getDesc() const { return mDesc; }
    private:
        RtStateObject(const Desc& d) : mDesc(d) {}
        ApiHandle mApiHandle;
        Desc mDesc;
    };
}
#endif