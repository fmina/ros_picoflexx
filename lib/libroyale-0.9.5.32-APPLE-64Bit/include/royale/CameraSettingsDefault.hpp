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

#include <royale/ICameraSettings.hpp>
#include <string>

namespace royale
{
    /**
     *  Default implementation for a standard camera module, please refer to `ICameraSettings` for documentation
     */
    class CameraSettingsDefault : public ICameraSettings
    {
    public:
        DllExport CameraSettingsDefault();
        DllExport CameraSettingsDefault (const std::string &calibrationFileName);

        DllExport bool getCalibrationFileName (std::string &fileName) const override;

    protected:
        std::string m_calibrationFileName;
    };
}
