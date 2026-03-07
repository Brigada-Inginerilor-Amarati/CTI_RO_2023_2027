package org.paul

class RemoteController {
    private val onCommands: MutableMap<Int, Command> = mutableMapOf()
    private val offCommands: MutableMap<Int, Command> = mutableMapOf()

    fun setCommand(slot: Int, onCommand: Command, offCommand: Command) {
        onCommands[slot] = onCommand
        offCommands[slot] = offCommand
    }

    fun pressOnButton(slot: Int) {
        onCommands[slot]?.execute()
    }

    fun pressOffButton(slot: Int) {
        offCommands[slot]?.execute()
    }
}