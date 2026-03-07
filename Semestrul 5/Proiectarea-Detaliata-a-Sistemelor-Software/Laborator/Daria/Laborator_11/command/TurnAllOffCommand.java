package Laborator.Daria.Laborator_11.command;

public class TurnAllOffCommand implements Command {
    private TV tv;
    private MediaPlayer mediaPlayer;

    public TurnAllOffCommand(TV tv, MediaPlayer mediaPlayer) {
        this.tv = tv;
        this.mediaPlayer = mediaPlayer;
    }

    @Override
    public void execute() {
        mediaPlayer.turnOff();
        tv.turnTVOff();
    }
}
