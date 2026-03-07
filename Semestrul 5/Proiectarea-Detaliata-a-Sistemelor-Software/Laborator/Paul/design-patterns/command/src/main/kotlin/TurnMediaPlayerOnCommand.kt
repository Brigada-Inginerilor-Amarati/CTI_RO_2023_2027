package org.paul

class TurnMediaPlayerOnCommand(player: MediaPlayer) : Command {
    private val player = player

    override fun execute() {
        player.on()
    }
}