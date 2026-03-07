package Laborator.Daria.Laborator_11.command;

public class TurnAllOnCommand implements Command {
    private TV tv;
    private MediaPlayer mediaPlayer;

    public TurnAllOnCommand(TV tv, MediaPlayer mediaPlayer) {
        this.tv = tv;
        this.mediaPlayer = mediaPlayer;
    }

    @Override
    public void execute() {
        mediaPlayer.turnOn();
        tv.turnTVOn();
    }
}
