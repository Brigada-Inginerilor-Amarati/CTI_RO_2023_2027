package Laborator.Daria.Laborator_11.command;

public class TurnTVOffCommand implements Command {
    private TV tv;

    public TurnTVOffCommand(TV tv) {
        this.tv = tv;
    }

    @Override
    public void execute() {
        tv.turnTVOff();
    }
}
