package Laborator.Daria.Laborator_11.command;

public class RemoteController {
    private Command[] onCommands;
    private Command[] offCommands;

    public RemoteController() {
        onCommands = new Command[3];
        offCommands = new Command[3];
    }

    public void setCommand(int slot, Command onCommand, Command offCommand) {
        if (slot >= 0 && slot < 3) {
            onCommands[slot] = onCommand;
            offCommands[slot] = offCommand;
        } else {
            System.out.println("Invalid slot: " + slot);
        }
    }

    public void pushOnButton(int slot) {
        if (slot >= 0 && slot < 3 && onCommands[slot] != null) {
            onCommands[slot].execute();
        } else {
            System.out.println("No command assigned to ON button " + slot);
        }
    }

    public void pushOffButton(int slot) {
        if (slot >= 0 && slot < 3 && offCommands[slot] != null) {
            offCommands[slot].execute();
        } else {
            System.out.println("No command assigned to OFF button " + slot);
        }
    }
}
