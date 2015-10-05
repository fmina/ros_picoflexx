/****************************************************************************\
* Copyright (C) 2015 pmdtechnologies gmbh
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <cstdint>
#include <royale/Status.hpp>
#include <royale/IPlaybackStopListener.hpp>

namespace royale
{
    class IReplay
    {
    public :

        virtual ~IReplay() = default;

        /**
        * Seek to a different frame inside the recording.
        * @param frameNumber frame which will be read next
        */
        virtual CameraStatus seek (const uint32_t frameNumber) = 0;

        /**
        * Enable/Disable looping of the playback.
        * @param restart Enable/Disable looping
        */
        virtual void loop (const bool restart) = 0;

        /**
        * If enabled, the playback will respect the timestamps and will pause accordingly.
        * @param timestampsUsed Use timestamps
        */
        virtual void useTimestamps (const bool timestampsUsed) = 0;

        /**
        *  Once registering the playback stop listener it will be called when the playback is stopped.
        *
        *  \param listener interface which needs to implement the callback method
        */
        virtual void registerStopListener (IPlaybackStopListener *listener) = 0;

        /**
        *  Unregisters the playback stop listener
        */
        virtual void unregisterStopListener() = 0;

    };

}