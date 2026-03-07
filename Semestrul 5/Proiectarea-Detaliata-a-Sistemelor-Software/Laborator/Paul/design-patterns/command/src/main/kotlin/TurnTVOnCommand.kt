package org.paul

class TurnTVOnCommand(tv: TV) : Command {
    private val tv = tv

    override fun execute() {
        tv.on()
    }
}