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

#include <utility>
#include <tuple>

namespace royale
{
    /**
     *  This container stores the lens parameters from the camera module
     */
    struct LensParameters
    {
        std::pair<float, float>         principalPoint;       //!< cx/cy
        std::pair<float, float>         focalLength;          //!< fx/fy
        std::pair<float, float>         distortionTangential; //!< p1/p2
        std::tuple<float, float, float> distortionRadial;     //!< k1/k2/k3
    };
}
