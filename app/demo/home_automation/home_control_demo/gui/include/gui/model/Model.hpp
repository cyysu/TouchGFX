/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.5.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>
#include <gui/system/DateTime.hpp>
#include <gui/common/RoomSelector.hpp>
#include <gui/model/WashingMachine.hpp>
#include <gui/model/MusicPlayer.hpp>
#include <gui/model/Room.hpp>

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:

    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
        musicPlayer.bind(listener);
    }

    WashingMachine& getWashingMachine()
    {
        return washingMachine;
    }
    void setWashingMachineState(const WashingMachine::Program, uint16_t remainingTime);

    int16_t getRoomAirConTemp(Room room)
    {
        return airConTemp[room];
    }
    void setRoomAirConTemp(Room room, int16_t value)
    {
        airConTemp[room] = value;
    }

    int16_t getBlindsPercentage(Room room)
    {
        return blindsPercentage[room];
    }
    void setBlindsPercentage(Room room, int16_t value)
    {
        blindsPercentage[room] = value;
    }

    int16_t getRoomLighting(Room room)
    {
        return lightingPercentage[room];
    }
    void setRoomLighting(Room room, int16_t value)
    {
        lightingPercentage[room] = value;
    }

    bool getRoomSecurity(Room room) const
    {
        return securityActivation[room];
    }
    void setRoomSecurity(Room room, bool active);

    MusicPlayer& getMusicPlayer()
    {
        return musicPlayer;
    }
    AlbumManager* getAlbumManager()
    {
        return musicPlayer.getAlbumManager();
    }
    void setCurrentAlbum(uint8_t currentAlbum)
    {
        musicPlayer.setCurrentAlbum(currentAlbum);
    }
    void setPlaying()
    {
        musicPlayer.play();
    }
    void setSliderValue(int16_t sliderId, int16_t value)
    {
        sliderValues[sliderId] = value;
    }
    int16_t getSliderValue(int16_t sliderId)
    {
        return sliderValues[sliderId];
    }

    System::DateTime getCurrentDateTime()
    {
        return currentDateTime;
    }
    void setCurrentDateTime(const System::DateTime& dateTime);

    bool isInactivationNeeded()
    {
        return inactivationNeeded;
    }
    void setInactivationNeeded(bool value)
    {
        inactivationNeeded = value;
    }
    void setMenuPosition(int16_t param1);

    int16_t getMenuPosition()
    {
        return menuPositionX;
    }
protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

private:
    System::DateTime currentDateTime;
    bool inactivationNeeded;

    WashingMachine washingMachine;
    MusicPlayer musicPlayer;

    // AIR CONDITION
    int16_t airConTemp[Room::NUMBER_OF_ROOMS];

    // BLINDS
    int16_t blindsPercentage[Room::NUMBER_OF_ROOMS];

    // LIGHTING
    int16_t lightingPercentage[Room::NUMBER_OF_ROOMS];

    // SETTINGS
    int16_t sliderValues[4];

    // SECURITY
    bool securityActivation[Room::NUMBER_OF_ROOMS];

    // MENU
    int16_t menuPositionX;
};

#endif
