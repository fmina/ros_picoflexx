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

#include <cstdint>
#include <map>

namespace royale
{
    /**
    * Defines the interface used for the imager. This may be different to the external interface from the module,
    * for example a module may also include conversion hardware from this format to HDMI or USB.
    */
    enum class DataInterface
    {
        PIF,
        CSI2
    };

    /**
     * Defines the lens center which should be used for centering the imager ROI
     */
    struct LensCenterDesign
    {
        uint16_t column;
        uint16_t row;
    };

    /**
     * Defines the type of imager which is used for the camera module
     */
    enum class ImagerType
    {
        IRS1020C_A11,
        IRS1020C_A12,
        IRS1645C
    };

    /**
     * Defines the type of temperature sensor which is used for the camera module
     */
    enum class TemperatureSensor
    {
        MCP98x43,
        TMP102
    };

    /**
     * The CameraProperties can be used for creating custom camera modules. Customer
     * modules can only be created in access level L3 by using the CameraFactory. The
     * CameraProperties currently only supports USB-based modules and requires a correct
     * VID/PID.
    */
    struct CameraProperties
    {
        //!< Base configuration for the imager
        std::map<uint16_t, uint16_t>    baseConfig;

        //!< User configuration for the imager
        std::map<uint16_t, uint16_t>    userConfig;

        LensCenterDesign                lensCenterDesign;
        DataInterface                   dataInterface;

        uint32_t                        systemFrequency;

        //!< Denotes the module's maximal width
        uint16_t                        maxImageWidth;

        //!< Denotes the module's maximal height
        uint16_t                        maxImageHeight;

        //!< Denotes the module's maximal modulation frequency
        uint32_t                        maxModulationFrequency;

        //!< Denotes the vendor ID for the used USB chip
        uint16_t                        vendorId;

        //!< Denotes the product ID for the used USB chip
        uint16_t                        productId;

        ImagerType                      imagerType;
        TemperatureSensor               temperatureSensor;

        //!< Denotes the I2C address which is used talking to the temperature sensor
        uint8_t                         temperatureSensorAddress;
    };
}