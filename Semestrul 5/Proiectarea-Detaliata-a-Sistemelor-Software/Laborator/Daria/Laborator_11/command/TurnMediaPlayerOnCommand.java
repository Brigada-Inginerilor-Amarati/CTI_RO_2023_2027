package Laborator.Daria.Laborator_11.command;

public class TurnMediaPlayerOnCommand implements Command {
    private MediaPlayer mediaPlayer;

    public TurnMediaPlayerOnCommand(MediaPlayer mediaPlayer) {
        this.mediaPlayer = mediaPlayer;
    }

    @Override
    public void execute() {
        mediaPlayer.turnOn();
    }
}
