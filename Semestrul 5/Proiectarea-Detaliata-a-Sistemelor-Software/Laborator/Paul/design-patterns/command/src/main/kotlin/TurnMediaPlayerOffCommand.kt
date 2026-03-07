package org.paul

class TurnMediaPlayerOffCommand(player: MediaPlayer) : Command {
    private val player = player

    override fun execute() {
        player.off()
    }
}