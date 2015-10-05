/****************************************************************************\
 * Copyright (C) 2015 Infineon Technologies
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <string>
#include <royale/IExtendedData.hpp>

namespace royale
{
    class DllExport IExtendedDataListener
    {
    public:
        virtual ~IExtendedDataListener() = default;

        /**
         *  Callback which is getting called by the ICameraDevice. If the data is required
         *  after this call, please copy away the data, the memory block will be reused.
         *
         *  \param data pointer to the underlying raw frames containing pointers to the raw frames
         */
        virtual void onNewData (const IExtendedData *data) = 0;
    };
}
