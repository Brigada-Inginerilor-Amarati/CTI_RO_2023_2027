package org.paul

class TurnDevicesOffCommand(tv: TV, player: MediaPlayer) : Command {
    private val tv = tv
    private val player = player

    override fun execute() {
        tv.off()
        player.off()
    }
}