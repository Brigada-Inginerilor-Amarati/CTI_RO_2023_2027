package org.paul

/*
We have a remote controller that has three entries (positions) and each entry has two buttons: on and off.

We need to configure each button with some actions, as it follows:
Button 1 on/off - turn the TV on/off
Button 2 on/off - turn the media player on/off
Button 3 on/off - turn the media player and TV on/off

The class that models the TV has two methods providing the needed services named turnTVOn() and turnTVOff().

The class that models the media player has two methods providing the needed services named turnOn() and turnOff().

Name a design pattern that helps in order to build the configurable remote controller and present the involved
participants for the general case.

For the aforementioned example draw the uml diagram.
*/

fun main() {
    val rc = RemoteController()

    val tv = TV()
    val mediaPlayer = MediaPlayer()

    rc.setCommand(0, TurnTVOnCommand(tv), TurnTVOffCommand(tv))
    rc.setCommand(1, TurnMediaPlayerOnCommand(mediaPlayer), TurnMediaPlayerOffCommand(mediaPlayer))
    rc.setCommand(2, TurnDevicesOnCommand(tv, mediaPlayer), TurnDevicesOffCommand(tv, mediaPlayer))

    rc.pressOnButton(0)
    rc.pressOffButton(0)
    rc.pressOnButton(1)
    rc.pressOffButton(1)
    rc.pressOnButton(2)
    rc.pressOffButton(2)
}