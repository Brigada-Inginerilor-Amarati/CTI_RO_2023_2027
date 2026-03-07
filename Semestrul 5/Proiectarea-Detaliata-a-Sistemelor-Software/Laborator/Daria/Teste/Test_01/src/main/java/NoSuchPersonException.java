public class NoSuchPersonException extends RuntimeException {
    public NoSuchPersonException(String message) {
        super(message);
    }

    public NoSuchPersonException(String message, Throwable cause) {
        super(message, cause);
    }
}
