package Laborator.Daria.Laborator_11.command;

public class TurnMediaPlayerOffCommand implements Command {
    private MediaPlayer mediaPlayer;

    public TurnMediaPlayerOffCommand(MediaPlayer mediaPlayer) {
        this.mediaPlayer = mediaPlayer;
    }

    @Override
    public void execute() {
        mediaPlayer.turnOff();
    }
}
