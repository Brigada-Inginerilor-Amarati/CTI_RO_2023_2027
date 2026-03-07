package Laborator.Daria.Laborator_11.command;

public class TurnTVOnCommand implements Command {
    private TV tv;

    public TurnTVOnCommand(TV tv) {
        this.tv = tv;
    }

    @Override
    public void execute() {
        tv.turnTVOn();
    }
}
