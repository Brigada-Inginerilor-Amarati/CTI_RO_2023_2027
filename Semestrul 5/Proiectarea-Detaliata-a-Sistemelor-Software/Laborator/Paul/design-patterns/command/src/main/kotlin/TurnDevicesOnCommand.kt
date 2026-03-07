package org.paul

class TurnDevicesOnCommand(tv: TV, player: MediaPlayer) : Command {
    private val tv = tv
    private val player = player

    override fun execute() {
        tv.on()
        player.on()
    }
}