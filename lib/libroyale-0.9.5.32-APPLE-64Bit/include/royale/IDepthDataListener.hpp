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
#include <royale/DepthData.hpp>

namespace royale
{
    /*!
     * Provides the listener interface for consuming depth data from Royale. A listener needs
     * to implement this interface and register itself as a listener to the ICameraDevice.
     */
    class DllExport IDepthDataListener
    {
    public:
        virtual ~IDepthDataListener() {}

        /*!
         * Will be called on every frame update by the Royale framework
         */
        virtual void onNewData (const DepthData *data) = 0;
    };
}