package org.paul

class TurnTVOffCommand(tv:TV) : Command {
    private val tv = tv

    override fun execute() {
        tv.off()
    }
}