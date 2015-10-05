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

#include <royale/Definitions.hpp>
#include <memory>
#include <cstdint>
#include <vector>
#include <chrono>

namespace royale
{
    /**
     *  Encapsulates a 3D point in object space [m]. In addition to the X/Y/Z coordinate
     *  each point also includes a gray value, a noise standard deviation, and a depth confidence value.
     */
    struct DepthPoint
    {
        float x;                 //!< X coordinate [meters]
        float y;                 //!< Y coordinate [meters]
        float z;                 //!< Z coordinate [meters]
        float noise;             //!< noise value [meters]
        uint16_t grayValue;      //!< 16-bit gray value
        uint8_t depthConfidence; //!< value 0 = bad, 255 = good
    };

    /**
     *  This structure defines the depth data which is delivered through the callback.
     *  This data comprises a dense 3D point cloud with the size of the depth image (width, height).
     *  The points vector encodes an array (row-based) with the size of (width x height). Based
     *  on the `depthConfidence`, the user can decide to use the 3D point or not.
     */
    struct DepthData
    {
        int                       version;         //!< version number of the data format
        std::chrono::milliseconds timeStamp;       //!< timestamp in milliseconds precision (time since epoch 1970)
        uint16_t                  width;           //!< width of depth image
        uint16_t                  height;          //!< height of depth image
        std::vector<uint32_t>     exposureTimes;   //!< exposureTimes retrieved from CapturedUseCase
        std::vector<DepthPoint>   points;          //!< array of points
    };

}