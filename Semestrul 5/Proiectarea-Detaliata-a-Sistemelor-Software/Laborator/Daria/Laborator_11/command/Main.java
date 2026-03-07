package Laborator.Daria.Laborator_11.command;

public class Main {
    public static void main(String[] args) {
        // Receivers
        TV tv = new TV();
        MediaPlayer mediaPlayer = new MediaPlayer();

        // Invoker
        RemoteController remote = new RemoteController();

        // Commands
        Command tvOn = new TurnTVOnCommand(tv);
        Command tvOff = new TurnTVOffCommand(tv);

        Command mpOn = new TurnMediaPlayerOnCommand(mediaPlayer);
        Command mpOff = new TurnMediaPlayerOffCommand(mediaPlayer);

        Command allOn = new TurnAllOnCommand(tv, mediaPlayer);
        Command allOff = new TurnAllOffCommand(tv, mediaPlayer);

        // Configuration
        remote.setCommand(0, tvOn, tvOff);
        remote.setCommand(1, mpOn, mpOff);
        remote.setCommand(2, allOn, allOff);

        // Testing
        System.out.println("--- Slot 0 (TV) ---");
        remote.pushOnButton(0);
        remote.pushOffButton(0);

        System.out.println("\n--- Slot 1 (MediaPlayer) ---");
        remote.pushOnButton(1);
        remote.pushOffButton(1);

        System.out.println("\n--- Slot 2 (All) ---");
        remote.pushOnButton(2);
        remote.pushOffButton(2);
    }
}
